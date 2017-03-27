import usb.core
import usb.util
import array
import numpy as np
import time

USB_RGBM_SWAPBUFFERS = 0x11
USB_RGBM_CLEAR       = 0x12
USB_RGBM_DEBUG       = 0x99

USB_RGBM_DATA_EP_ADDR = 0x01

# 3 colors, 8x8 matrix
FRAME_SIZE = 3 * 8 * 8;

class RGBMatrix(object):
    def __init__(self, idVendor=0xcafe, idProduct=0xbabe):
        self.idVendor = idVendor
        self.idProduct = idProduct
        self.dev = usb.core.find(idVendor=0xcafe, idProduct=0xbabe)
        if self.dev is None:
            raise ValueError("Could not find device")

        # Disabled as workaround for libopencm3 issue #755
        # self.dev.set_configuration()

    def write_frame(self, frame):
        data = array.array('H')
        data.fromlist(frame)
        print("write_frame(): data ({}) = ".format(len(data)))
        print(", ".join(map("0x{:04x}".format, data)))
        written = self.dev.write(USB_RGBM_DATA_EP_ADDR, data, timeout=1500)
        print("write_frame(): wrote {} bytes".format(written))

    def swapbuffers(self):
        print("swapbuffers()")
        bmRequestType = usb.util.build_request_type(
                usb.util.CTRL_OUT,
                usb.util.CTRL_TYPE_VENDOR,
                usb.util.CTRL_RECIPIENT_ENDPOINT)
        self.dev.ctrl_transfer(bmRequestType, USB_RGBM_SWAPBUFFERS, timeout=1500)
        print("swapbuffers done")

    def clear(self, r=0, g=0, b=0):
        bmRequestType = usb.util.build_request_type(
                usb.util.CTRL_OUT,
                usb.util.CTRL_TYPE_VENDOR,
                usb.util.CTRL_RECIPIENT_ENDPOINT)
        data = array.array('H', [r, g, b])
        print("clear(0x{:x}, 0x{:x}, 0x{:x})".format(r, g, b))
        n = self.dev.ctrl_transfer(bmRequestType, USB_RGBM_CLEAR, data_or_wLength=data)
        print("{} bytes transferred".format(n))