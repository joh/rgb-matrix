from nose.tools import *
from rgbmatrix import RGBMatrix
import numpy as np
import time
from itertools import cycle

dev = None

def setup_module():
    global dev
    dev = RGBMatrix()

def teardown_module():
    global dev
    dev.clear(0, 0, 0)
    dev.swapbuffers()
    del dev

brightness = 0xfff

colors = np.array(
    [[1, 0, 0],
     [0, 1, 0],
     [0, 0, 1],
     [1, 1, 0],
     [0, 1, 1],
     [1, 0, 1],
     [1, 1, 1]])

def test_clear():
    for c in colors * brightness:
        dev.clear(*c)
        dev.swapbuffers()
        time.sleep(0.25)

def test_columns():
    for c in colors:
        for i in range(8):
            frame = np.zeros((8, 8, 3), dtype='uint16')
            frame[:,i] = c * brightness

            dev.write_frame(frame.flatten().tolist())
            dev.swapbuffers()

            time.sleep(0.1);

def test_rows():
    for c in colors:
        for i in range(8):
            frame = np.zeros((8, 8, 3), dtype='uint16')
            frame[i,:] = c * brightness

            dev.write_frame(frame.flatten().tolist())
            dev.swapbuffers()

            time.sleep(0.1);

def test_swapbuffers():
    dev = RGBMatrix()

    for i in range(100):
        dev.clear(brightness, 0, 0)
        dev.swapbuffers()
        dev.clear(0, brightness, 0)
        dev.swapbuffers()

def test_fps():
    red_frame = np.tile([1, 0, 0], 8*8) * brightness
    green_frame = np.tile([0, 1, 0], 8*8) * brightness
    frames = cycle([red_frame, green_frame])

    n_frames = 100
    t0 = time.time()

    for i in range(n_frames):
        frame = frames.next()
        dev.write_frame(frame.flatten().tolist())
        dev.swapbuffers()

    t1 = time.time()
    fps = n_frames / (t1 - t0)
    print("{:.2f} fps".format(fps))


def test_brightness():
    for c in colors:
        brightness = 0;

        frame = np.zeros((8, 8, 3), dtype='uint16')

        for i in range(8):
            for j in range(8):
                frame[i,j] = c * brightness
                brightness += 0xffff/64

        dev.write_frame(frame.flatten().tolist())
        dev.swapbuffers();
        time.sleep(0.5)


def test_white():
    dev = RGBMatrix()

    b = 0xffff
    dev.clear(b, b, b)
    dev.swapbuffers()

    time.sleep(1.0)


def test_random():
    for i in range(25):
        frame = np.random.randint(0, brightness, (8, 8, 3))
        dev.write_frame(frame.flatten().tolist())
        dev.swapbuffers();

        time.sleep(0.1)

def test_fade():
    for c in colors:
        for k in range(255):
            dev.clear(*(c * k ** 2))
            dev.swapbuffers()

        for k in range(255, 0, -1):
            dev.clear(*(c * k ** 2))
            dev.swapbuffers()

