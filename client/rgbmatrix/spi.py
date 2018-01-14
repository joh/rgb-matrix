import spidev
import numpy as np
import array
import time

class RGBMatrixSPI(object):
    def __init__(self, bus=0, device=0, max_speed_hz=1000000):

        self.spi = spidev.SpiDev()
        self.spi.open(bus, device)
        self.spi.max_speed_hz = max_speed_hz

    def write_data(self, data):
        if isinstance(data, np.ndarray):
            data = data.flatten().tobytes()
        # data = array.array('B', data)
        data = list(bytearray(data))
        # print("write_frame(): data ({}) = ".format(len(data)))
        # print(", ".join(map("0x{:04x}".format, data)))
        self.spi.xfer(data)
        # print("write_frame(): wrote {} bytes".format(written))

    def swapbuffers(self):
        # TODO: Implement support for this in firmware
        time.sleep(1./120)

