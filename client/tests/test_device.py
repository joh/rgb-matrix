from nose.tools import *
from rgbmatrix import RGBMatrix, Frame
import numpy as np
import time
from itertools import cycle

dev = None
layout = [[1,2]]
num_height = len(layout)
num_width = len(layout[0])
height = num_height * 8
width = num_width * 8

def setup_module():
    global dev
    dev = RGBMatrix(layout=layout)

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
        for i in range(width):
            frame = Frame(size=(width, height), dtype='uint16')
            frame[:,i] = c * brightness

            dev.write_frame(frame)
            dev.swapbuffers()

            time.sleep(0.1)

def test_rows():
    for c in colors:
        for i in range(height):
            frame = Frame(size=(width, height), dtype='uint16')
            frame[i,:] = c * brightness

            dev.write_frame(frame)
            dev.swapbuffers()

            time.sleep(0.1)

def test_swapbuffers():
    dev = RGBMatrix()

    for i in range(100):
        dev.clear(brightness, 0, 0)
        dev.swapbuffers()
        dev.clear(0, brightness, 0)
        dev.swapbuffers()

def test_fps():
    red_frame = Frame(size=(width, height), color=(brightness, 0, 0), dtype='uint16')
    green_frame = Frame(size=(width, height), color=(0, brightness, 0), dtype='uint16')
    frames = cycle([red_frame, green_frame])

    n_frames = 100
    t0 = time.time()

    for i in range(n_frames):
        frame = frames.next()
        dev.write_frame(frame)
        # time.sleep(.1)
        dev.swapbuffers()
        # time.sleep(.0005)

    # dev.swapbuffers()
    t1 = time.time()
    fps = n_frames / (t1 - t0)
    print("{:.2f} fps".format(fps))


def test_brightness():
    for c in colors:
        brightness = 0

        frame = Frame(size=(width, height), dtype='uint16')

        for i in range(height):
            for j in range(width):
                frame[i,j] = c * brightness
                brightness += 0xffff/(width * height)

        dev.write_frame(frame)
        dev.swapbuffers()
        time.sleep(0.5)


def test_white():
    dev = RGBMatrix()

    b = 0xffff
    dev.clear(b, b, b)
    dev.swapbuffers()

    time.sleep(1.0)


def test_random():
    for i in range(25):
        frame = np.random.randint(0, brightness, (height, width, 3))
        frame = Frame(frame, dtype='uint16')
        dev.write_frame(frame)
        dev.swapbuffers()

        time.sleep(0.1)

def test_fade():
    for c in colors:
        for k in range(255):
            dev.clear(*(c * k ** 2))
            dev.swapbuffers()

        for k in range(255, 0, -1):
            dev.clear(*(c * k ** 2))
            dev.swapbuffers()

def test_fade2():
    frame = Frame(size=(16,8), color=(0, 0, 0), dtype='uint16')
    for c in colors:
        for k in range(255):
            frame[::] = c * k ** 2
            dev.write_frame(frame)
            dev.swapbuffers()
            time.sleep(.0005)

        for k in range(255, 0, -1):
            frame[::] = c * k ** 2
            dev.write_frame(frame)
            dev.swapbuffers()
            time.sleep(.0005)


def test_gamma():
    for c in colors:
        frame = Frame(size=(width, height), dtype='uint16')
        brightness = 0
        for i in range(height):
            for j in range(width):
                frame[i,j] = c * brightness
                # print(brightness)
                brightness += 0xffff/(width * height)

        for gamma in np.arange(1, 4.1, 0.1):
            print("gamma={:.1f}".format(gamma))
            dev.gamma = gamma
            dev.write_frame(frame)
            dev.swapbuffers()
            time.sleep(0.05)

def test_brightness_adjust():
    frame = np.random.randint(0, 0xffff, (height, width, 3))
    frame = Frame(frame, dtype='uint16')
    for brightness in np.linspace(0, 0xffff, 25, dtype='uint16'):
        dev.brightness = brightness
        dev.write_frame(frame)
        dev.swapbuffers()
        time.sleep(0.1)
