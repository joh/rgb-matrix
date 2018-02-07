from nose.tools import *
from numpy.testing import *
from rgbmatrix.frame import *
import numpy as np

def test_frame():

    # Create empty with size
    frame = Frame(size=(8, 4))
    assert frame.shape == (4, 8, 3)
    assert frame.dtype == 'uint8'
    assert frame.width == 8
    assert frame.height == 4
    assert np.all(frame == (0, 0, 0))

    # Create with color
    frame = Frame(size=(16, 16), color=(1, 2, 3))
    assert frame.shape == (16, 16, 3)
    assert frame.width == 16
    assert frame.height == 16
    assert frame.dtype == 'uint8'
    assert np.all(frame == (1, 2, 3))

    # Create 16-bit frame
    frame = Frame(size=(16, 8), color=(0xffff, 0, 0), dtype='uint16')
    assert frame.shape == (8, 16, 3)
    assert frame.dtype == 'uint16'
    assert frame.width == 16
    assert frame.height == 8
    assert np.all(frame == (0xffff, 0, 0))

    # Create from flat array
    frame = Frame(np.zeros(5*5*3), size=(5,5))
    assert frame.shape == (5, 5, 3)
    assert frame.dtype == 'uint8'
    assert frame.width == 5
    assert frame.height == 5
    assert np.all(frame == (0, 0, 0))

    # Create from (m, n, 3) array
    frame = Frame(np.ones(2*2*3).reshape((2,2,3)))
    assert frame.shape == (2, 2, 3)
    assert frame.dtype == 'uint8'
    assert frame.width == 2
    assert frame.height == 2
    assert np.all(frame == (1, 1, 1))

    # Set all pixels
    frame[::] = (1,2,3)
    assert np.all(frame == (1, 2, 3))

def test_frame_text():
    frame = Frame(size=(8*9, 8))
    frame = frame.text("0123456789")
    frame.show()

    frame = Frame(size=(8*8, 16))
    frame = frame.text("hello, world!", (2, 2), color=(0, 255, 0))
    frame.show()

def test_frame_torgb8():
    rgb8 = Frame(size=(1,1))
    rgb8[::] = (0, 127, 255)
    assert_array_equal(rgb8.torgb8(), rgb8)

    rgb16 = Frame(size=(1,1), dtype='uint16')
    rgb16[::] = (0, 0x7f7f, 0xffff)
    assert_array_equal(rgb16.torgb8(), rgb8)

def test_frame_torgb16():
    rgb16 = Frame(size=(1,1), dtype='uint16')
    rgb16[::] = (0, 0x7f7f, 0xffff)
    assert_array_equal(rgb16.torgb16(), rgb16)

    rgb8 = Frame(size=(1,1))
    rgb8[::] = (0, 127, 255)
    assert_array_equal(rgb8.torgb16(), rgb16)


def test_rgb8_to_rgb16():
    assert rgb8_to_rgb16(0) == 0
    assert rgb8_to_rgb16(127) == 0x7f7f
    assert rgb8_to_rgb16(255) == 0xffff

    assert rgb8_to_rgb16([0]) == [0]
    assert rgb8_to_rgb16([127]) == [0x7f7f]
    assert rgb8_to_rgb16([255]) == [0xffff]

    assert rgb8_to_rgb16(0, 0xfff) == 0
    assert rgb8_to_rgb16(127, 0xfff) == 0x7f7
    assert rgb8_to_rgb16(255, 0xfff) == 0xfff

def test_layout_1x2():
    layout = [1, 2]
    layout = Layout(layout, (2, 2))

    frame = np.array([[1,   2,  3,  4],
                      [5,   6,  7,  8]])

    subframe1 = layout.subframe(frame, 1)
    assert_array_equal(subframe1, [[1, 2], [5, 6]])

    subframe2 = layout.subframe(frame, 2)
    assert_array_equal(subframe2, [[3, 4], [7, 8]])

    # Reversed order
    subframes = [s for s in layout.subframe_iter(frame)]

    assert_array_equal(subframes[0], subframe2)
    assert_array_equal(subframes[1], subframe1)

def test_layout_2x2():
    layout = [[1, 2],
              [3, 4]]
    layout = Layout(layout, (2, 2))

    frame = np.array([[1,   2,  3,  4],
                      [5,   6,  7,  8],
                      [9,  10, 11, 12],
                      [13, 14, 15, 16]])

    subframe1 = layout.subframe(frame, 1)
    assert_array_equal(subframe1, [[1, 2], [5, 6]])

    subframe2 = layout.subframe(frame, 2)
    assert_array_equal(subframe2, [[3, 4], [7, 8]])

    subframe3 = layout.subframe(frame, 3)
    assert_array_equal(subframe3, [[9, 10], [13, 14]])

    subframe4 = layout.subframe(frame, 4)
    assert_array_equal(subframe4, [[11, 12], [15, 16]])

    # Reversed order
    subframes = list(layout.subframe_iter(frame))

    assert_array_equal(subframes[0], subframe4)
    assert_array_equal(subframes[1], subframe3)
    assert_array_equal(subframes[2], subframe2)
    assert_array_equal(subframes[3], subframe1)

def test_layout_3x2():
    layout = [[0, 3, 4],
              [1, 2, 0]]
    layout = Layout(layout, (2, 2))

    frame = np.array([[1,   2,  3,  4,  5,  6],
                      [7,   8,  9, 10, 11, 12],
                      [13, 14, 15, 16, 17, 18],
                      [19, 20, 21, 22, 23, 24]])

    subframe1 = layout.subframe(frame, 1)
    assert_array_equal(subframe1, [[13, 14], [19, 20]])

    subframe2 = layout.subframe(frame, 2)
    assert_array_equal(subframe2, [[15, 16], [21, 22]])

    subframe3 = layout.subframe(frame, 3)
    assert_array_equal(subframe3, [[3, 4], [9, 10]])

    subframe4 = layout.subframe(frame, 4)
    assert_array_equal(subframe4, [[5, 6], [11, 12]])

    # Reversed order
    subframes = list(layout.subframe_iter(frame))

    assert_array_equal(subframes[0], subframe4)
    assert_array_equal(subframes[1], subframe3)
    assert_array_equal(subframes[2], subframe2)
    assert_array_equal(subframes[3], subframe1)

