#ifndef USB_H
#define USB_H

/* Control requests */
#define USB_RGBM_SWAPBUFFERS 0x11
#define USB_RGBM_CLEAR       0x12
#define USB_RGBM_DEBUG       0x99

/* Endpoints */
#define USB_RGBM_DATA_EP_ADDR 0x01

void usb_init(void);
void usb_poll(void);
bool usb_connected(void);

#endif
