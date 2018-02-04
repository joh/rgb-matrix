import spidev
import numpy as np
import time
import struct
from math import ceil

CMD_SIZE = 1
DATA_SIZE = 64
PACKET_SIZE = CMD_SIZE + DATA_SIZE

SPI_CMD_WRITE = 0x01
SPI_CMD_SWAPBUFFERS = 0x02

class RGBMatrixSPI(object):
    def __init__(self, bus=0, device=0, max_speed_hz=10000000):
        self.spi = spidev.SpiDev()
        self.spi.open(bus, device)
        self.spi.max_speed_hz = max_speed_hz

    def _create_packet(self, cmd, data=[]):
        fmt = ('B' * (len(data) + 1)) + ('x' * (DATA_SIZE - len(data)))
        packet = struct.pack(fmt, cmd, *data)
        packet = list(bytearray(packet))
        return packet

    def write_data(self, data):
        if isinstance(data, np.ndarray):
            data = data.flatten().tobytes()

        # Split data into chunks of 64 bytes
        n_chunks = ceil(len(data) / DATA_SIZE)
        for i in range(n_chunks):
            chunk = data[DATA_SIZE * i:DATA_SIZE * (i+1)]
            packet = self._create_packet(SPI_CMD_WRITE, chunk)
            self.spi.xfer(packet)

    def swapbuffers(self):
        packet = self._create_packet(SPI_CMD_SWAPBUFFERS)
        self.spi.xfer(packet)
        time.sleep(1/100) # seems to work

