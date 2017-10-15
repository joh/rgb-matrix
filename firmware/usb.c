#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libopencmsis/core_cm3.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/otg_fs.h>

#include "usb.h"
#include "display.h"
#include "spi.h"
#include "utils.h"

static const struct usb_device_descriptor dev = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = USB_CLASS_VENDOR,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = 0xcafe,
    .idProduct = 0xbabe,
    .bcdDevice = 0x0200,
    .iManufacturer = 1, // Index of string descriptor describing manufacturer
    .iProduct = 2,
    .iSerialNumber = 3,
    .bNumConfigurations = 1,
};

static const struct usb_endpoint_descriptor data_endp[] = {{
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = USB_RGBM_DATA_EP_ADDR,
    .bmAttributes = USB_ENDPOINT_ATTR_BULK,
    .wMaxPacketSize = 64,
    .bInterval = 1,
} };

static const struct usb_interface_descriptor data_iface[] = {{
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 1,
    .bAlternateSetting = 0,
    .bNumEndpoints = 1,
    .bInterfaceClass = USB_CLASS_VENDOR,
    .bInterfaceSubClass = 0,
    .bInterfaceProtocol = 0,
    .iInterface = 0,

    .endpoint = data_endp,
} };

static const struct usb_interface ifaces[] = {{
    .num_altsetting = 1,
    .altsetting = data_iface,
}, };

static const struct usb_config_descriptor config = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = 0,
    .bNumInterfaces = 1,
    .bConfigurationValue = 1,
    .iConfiguration = 0,
    .bmAttributes = 0x80,
    .bMaxPower = 0x32,

    .interface = ifaces,
};

static const char * usb_strings[] = {
    "Pseudoberries",
    "RGB Matrix",
    "1234",
};

static usbd_device *usbdev;

/* Buffer to be used for control requests. */
uint8_t usbd_control_buffer[128];

/* Write position display backbuffer */
static __IO unsigned int dispbuf_pos = 0;

static int control_request(usbd_device *usbd_dev,
    struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
    void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req))
{
    DisplayBuf *dispbuf;
    uint16_t r = 0, g = 0, b = 0;

    (void)complete;
    (void)usbd_dev;
    (void)len;

    switch (req->bRequest) {
        case USB_RGBM_SWAPBUFFERS:
            spi_daisy_wait();
            spi_daisy_set_nss_high();
            display_swapbuffers();
            dispbuf_pos = 0;
            spi_daisy_set_nss_low();

            /* TODO: figure out a better way to sync displays on SPI */
            usleep(5000);

            return 1;
        case USB_RGBM_CLEAR:
            /* Get color from data phase (if any) */
            if (req->wLength == 6) {
                r = ((uint16_t *)(*buf))[0];
                g = ((uint16_t *)(*buf))[1];
                b = ((uint16_t *)(*buf))[2];
            }

            dispbuf = display_get_backbuffer();
            display_clear(dispbuf, r, g, b);
            /* Test pattern: */
            /*display_clear(dispbuf, 0xcdcd, 0xcdcd, 0xcdcd);*/
            /*display_set(dispbuf, 0, 0, 0xabab, 0xcdcd, 0xcdcd);*/
            /*display_set(dispbuf, 7, 7, 0xcdcd, 0xcdcd, 0xefef);*/
            return 1;
        case USB_RGBM_DEBUG:
            *buf[0] = dispbuf_pos;
            return 1;
        default:
            break;
    }

    return 0;
}

static void data_rx_cb(usbd_device *usbd_dev, uint8_t ep)
{
    /*static int cnt = 0;*/
    uint8_t buf[64];
    uint16_t i;
    uint8_t *dispbuf = (uint8_t *)display_get_backbuffer();
    uint16_t len = usbd_ep_read_packet(usbd_dev, USB_RGBM_DATA_EP_ADDR, buf, sizeof(buf));

    (void)ep;

    // TODO: DMA
    for (i = 0; i < len; i++) {
        /*printf("0x%x ", dispbuf[dispbuf_pos]);*/
        spi_daisy_send(dispbuf[dispbuf_pos]);
        dispbuf[dispbuf_pos] = buf[i];
        dispbuf_pos = (dispbuf_pos + 1) % sizeof(DisplayBuf);
    }
}

static bool connected = false;

static void suspend_callback(void)
{
    connected = false;

    /* USB suspended, we're now SPI slave */
    spi_daisy_init_slave();
}

static void set_config(usbd_device *usbd_dev, uint16_t wValue)
{
    (void)wValue;

    usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64, data_rx_cb);

    usbd_register_control_callback(
                usbd_dev,
                USB_REQ_TYPE_VENDOR | USB_REQ_TYPE_ENDPOINT,
                USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
                control_request);

    usbd_register_suspend_callback(usbd_dev, suspend_callback);

    connected = true;

    /* USB configured, we're the SPI master */
    spi_daisy_init_master();
}

void usb_init(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_OTGFS);

    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
            GPIO9 | GPIO11 | GPIO12);
    gpio_set_af(GPIOA, GPIO_AF10, GPIO9 | GPIO11 | GPIO12);

    usbdev = usbd_init(&otgfs_usb_driver, &dev, &config,
            usb_strings, 3,
            usbd_control_buffer, sizeof(usbd_control_buffer));

    usbd_register_set_config_callback(usbdev, set_config);
}

void usb_poll(void)
{
    usbd_poll(usbdev);
}

bool usb_connected(void)
{
    return connected;
}
