#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>

#include "usb.h"
#include "display.h"

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
    .bEndpointAddress = 0x01,
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

/* Buffer to be used for control requests. */
uint8_t usbd_control_buffer[128];

static int control_request(usbd_device *usbd_dev,
    struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
    void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req))
{
    (void)complete;
    (void)buf;
    (void)usbd_dev;

    return 0;
}

/*DisplayBuf buf;*/
unsigned int i = 0;

static void data_rx_cb(usbd_device *usbd_dev, uint8_t ep)
{
    (void)ep;
    DisplayBuf *dispbuf = display_get_backbuffer();
    char buf[64];
    unsigned int remaining = sizeof(*dispbuf) - i;
    int len = usbd_ep_read_packet(usbd_dev, 0x01, buf, 64);

    if (len > remaining)
        len = remaining;

    memcpy((void *)dispbuf + i, buf, len);

    i += len;
    if (i == sizeof(*dispbuf)) {
        i = 0;
        display_swapbuffers();
    }
}

static void set_config(usbd_device *usbd_dev, uint16_t wValue)
{
    (void)wValue;

    usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64, data_rx_cb);
    /*usbd_ep_setup(usbd_dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, NULL);*/
    /*usbd_ep_setup(usbd_dev, 0x83, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);*/

    /*usbd_register_control_callback(*/
                /*usbd_dev,*/
                /*USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,*/
                /*USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,*/
                /*control_request);*/
}

static usbd_device *usbd_dev;

void usb_init(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_OTGFS);

    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
            GPIO9 | GPIO11 | GPIO12);
    gpio_set_af(GPIOA, GPIO_AF10, GPIO9 | GPIO11 | GPIO12);

    usbd_dev = usbd_init(&otgfs_usb_driver, &dev, &config,
            usb_strings, 3,
            usbd_control_buffer, sizeof(usbd_control_buffer));

    usbd_register_set_config_callback(usbd_dev, set_config);
}

void usb_poll(void)
{
    usbd_poll(usbd_dev);
}
