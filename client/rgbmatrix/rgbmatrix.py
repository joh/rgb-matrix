import array
import numpy as np
import time

from .frame import Frame, Layout

DISPLAY_SIZE = (8, 8)

class RGBMatrix(object):
    def __init__(self, layout=[1], gamma=1, brightness=0xffff, backend='usb'):
        self.layout = Layout(layout, DISPLAY_SIZE)
        self.gamma = gamma
        self.brightness = brightness

        if backend == 'usb':
            from .usb import RGBMatrixUSB
            self.dev = RGBMatrixUSB()
        elif backend == 'spi':
            from .spi import RGBMatrixSPI
            self.dev = RGBMatrixSPI()
        else:
            raise ValueError("Invalid backend", backend)

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
        frame = frame.astype('uint16')

        # Apply brightness adjustment
        if self.brightness != 0xffff:
            frame = (frame * (self.brightness / 0xffff)).astype('uint16')

        # Apply gamma correction
        if self.gamma != 1:
            frame = frame.gamma(self.gamma)

        # Reorder frames according to layout
        subframes = self.layout.subframes(frame, 'reverse')
        subframes = np.array(subframes)

        self.write_data(subframes)

    def write_data(self, data):
        self.dev.write_data(data)

    def swapbuffers(self):
        self.dev.swapbuffers()

    def clear(self, r=0, g=0, b=0):
        frame = Frame(size=self.size, color=(r, g, b), dtype='uint16')
        self.write_frame(frame)
