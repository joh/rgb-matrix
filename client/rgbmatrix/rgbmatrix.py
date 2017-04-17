import usb.core
import usb.util
import array
import numpy as np
import time

from .frame import Layout

USB_RGBM_SWAPBUFFERS = 0x11
USB_RGBM_CLEAR       = 0x12
USB_RGBM_DEBUG       = 0x99

USB_RGBM_DATA_EP_ADDR = 0x01

DISPLAY_SIZE = (8, 8)

class RGBMatrix(object):
    def __init__(self, idVendor=0xcafe, idProduct=0xbabe, layout=[1]):
        self.idVendor = idVendor
        self.idProduct = idProduct
        self.dev = usb.core.find(idVendor=0xcafe, idProduct=0xbabe)
        if self.dev is None:
            raise ValueError("Could not find device")

        self.layout = Layout(layout, DISPLAY_SIZE)

        # Disabled as workaround for libopencm3 issue #755
        # self.dev.set_configuration()

    def __del__(self):
        usb.util.dispose_resources(self.dev)

    def set_layout(self, layout):
        self.layout = Layout(layout, DISPLAY_SIZE)

    @property
    def layout_size(self):
        layout = self.layout.layout
        return (len(layout[0]), len(layout))

    @property
    def size(self):
        display_size = self.layout.size
        layout_size = self.layout_size
        return (layout_size[0] * display_size[0], layout_size[1] * display_size[1])

    def write_frame(self, frame):
        # Reorder frames according to layout
        subframes = self.layout.subframes(frame, 'reverse')
        subframes = np.array(subframes)

        self.write_data(subframes)

    def write_data(self, data):
        if isinstance(data, np.ndarray):
            data = data.flatten()
        data = array.array('H', data)
        # print("write_frame(): data ({}) = ".format(len(data)))
        # print(", ".join(map("0x{:04x}".format, data)))
        written = self.dev.write(USB_RGBM_DATA_EP_ADDR, data, timeout=1500)
        # print("write_frame(): wrote {} bytes".format(written))

    def swapbuffers(self):
        # print("swapbuffers()")
        bmRequestType = usb.util.build_request_type(
                usb.util.CTRL_OUT,
                usb.util.CTRL_TYPE_VENDOR,
                usb.util.CTRL_RECIPIENT_ENDPOINT)
        self.dev.ctrl_transfer(bmRequestType, USB_RGBM_SWAPBUFFERS, timeout=1500)
        # print("swapbuffers done")

    def clear(self, r=0, g=0, b=0):
        bmRequestType = usb.util.build_request_type(
                usb.util.CTRL_OUT,
                usb.util.CTRL_TYPE_VENDOR,
                usb.util.CTRL_RECIPIENT_ENDPOINT)
        data = array.array('H', [r, g, b])
        # print("clear(0x{:x}, 0x{:x}, 0x{:x})".format(r, g, b))
        n = self.dev.ctrl_transfer(bmRequestType, USB_RGBM_CLEAR, data_or_wLength=data)
        # print("{} bytes transferred".format(n))
