import numpy as np
from PIL import Image, ImageFont, ImageDraw

def rgb8_to_rgb16(rgb8, brightness=0xffff):
    if np.iterable(rgb8):
        rgb8 = np.asarray(rgb8, dtype='uint32')
    rgb16 = rgb8 * brightness // 255
    if np.iterable(rgb8):
        rgb16 = rgb16.astype('uint16')
    return rgb16

class Frame(np.ndarray):
    """ Frame, a subclass of ndarray with some bells and whistles """
    def __new__(cls, input_array=None, size=None, color=(0, 0, 0), dtype='uint8'):
        # Input array is an already formed ndarray instance

        assert input_array is not None or size is not None

        if input_array is not None:
            if size:
                width, height = size
                input_array = input_array.reshape((height, width, 3))

            assert len(input_array.shape) == 3, "Need to specify frame size"
            assert input_array.shape[2] == 3, "Only RGB color supported"

        elif size is not None:
            width, height = size
            input_array = np.zeros((height, width, 3), dtype=dtype)
            input_array[::] = color

        obj = np.asarray(input_array, dtype=dtype).view(cls)

        return obj

    @property
    def width(self):
        return self.shape[1]

    @property
    def height(self):
        return self.shape[0]

    def show(self):
        import matplotlib.pyplot as plt
        import matplotlib.ticker as ticker

        plt.imshow(self, interpolation='none')

        loc = ticker.MultipleLocator(base=8.0)
        plt.gca().xaxis.set_major_locator(loc)
        loc = ticker.MultipleLocator(base=4.0)
        plt.gca().xaxis.set_minor_locator(loc)

        plt.show()

    def save(self, filename):
        image = Image.fromarray(self, mode="RGB")
        image.save(filename)

    def text(self, text, pos=(0, -1), color=(255, 255, 255), size=11):
        image = Image.fromarray(self, mode="RGB")

        mask = Image.new("1", image.size, (1))
        font = ImageFont.truetype("helvetica.ttf", size)
        # font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", size)
        draw = ImageDraw.Draw(mask)
        draw.text(pos, text, fill=(0), font=font)

        # Combine two images with transparency mask
        color_mask = Image.new("RGB", image.size, color)
        result = Image.composite(image, color_mask, mask)

        return np.array(result).view(self.__class__)

    def torgb8(self):
        rgb8 = self.copy()
        if rgb8.dtype == 'uint8':
            return rgb8
        rgb8 >>= 8
        return rgb8.astype('uint8')

    def torgb16(self):
        rgb16 = self.copy()
        if rgb16.dtype == 'uint16':
            return rgb16
        rgb16 = rgb16.astype('uint16')
        rgb16 *= 0xffff // 255
        return rgb16

    # def __array_finalize__(self, obj):
        # if obj is None: return
        # self.size = getattr(obj, 'info', None)

class Layout(object):
    def __init__(self, layout, size=(8, 8)):
        self.layout = layout
        self.size = size

        width, height = size

        self.map = np.atleast_2d(layout)
        self.map = np.repeat(self.map, height, axis=0)
        self.map = np.repeat(self.map, width, axis=1)

    def subframe(self, frame, index):
        sub = frame[self.map == index]
        new_shape = (self.size[1], self.size[0])
        if len(frame.shape) > 2:
            new_shape += (-1,)
        sub = sub.reshape(new_shape)
        return sub

    def subframe_iter(self, frame, order='reverse'):
        last_index = np.max(self.layout)

        if order == 'reverse':
            it = range(last_index, 0, -1)
        else:
            it = range(1, last_index + 1)

        for i in it:
            yield self.subframe(frame, i)

    def subframes(self, frame, order='reverse'):
        return list(self.subframe_iter(frame, order))


