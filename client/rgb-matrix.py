#!/usr/bin/env python3
import argparse
import ast
import numpy as np
from PIL import Image
import time
from itertools import cycle

from rgbmatrix import RGBMatrix
from rgbmatrix.frame import *

def create_rgbm(args):
    layout = list(ast.literal_eval(args.layout))
    rgbm = RGBMatrix(layout=layout)

    return rgbm

def cmd_clear(args):
    rgbm = create_rgbm(args)

    r = int(args.r, 16)
    g = int(args.g, 16)
    b = int(args.b, 16)

    frame = Frame(size=rgbm.size, color=(r, g, b), dtype='uint16')
    rgbm.write_frame(frame)

    if not args.no_swapbuffers:
        rgbm.swapbuffers()

def cmd_text(args):
    rgbm = create_rgbm(args)

    bg = tuple(args.background)
    color = tuple(args.color)

    frame = Frame(size=rgbm.size, color=bg)
    frame = frame.text(args.text, color=color, size=9, pos=(0,0))
    frame = frame.torgb16()

    rgbm.write_frame(frame)
    rgbm.swapbuffers()

def cmd_random(args):
    rgbm = create_rgbm(args)

    width, height = rgbm.size
    frame = np.random.randint(args.min, args.max + 1, (height, width, 3))
    frame = Frame(frame)
    frame = frame.torgb16()

    rgbm.write_frame(frame)
    rgbm.swapbuffers()

def show_image(rgbm, image):
    frame = Image.new("RGB", rgbm.size, color=(0, 0, 0))
    frame.paste(image, (0, 0))
    frame = Frame(np.array(frame))
    frame = frame.torgb16()

    rgbm.write_frame(frame)
    rgbm.swapbuffers()

def extract_frames(image):
    frames = []
    i = 0
    while True:
        try:
            image.seek(i)
        except EOFError:
            break
        frames.append(image.copy())
        i += 1
    return frames

def cmd_image(args):
    rgbm = create_rgbm(args)

    image = Image.open(args.image)
    images = extract_frames(image)

    if len(images) == 1:
        show_image(rgbm, images[0])
    else:
        # animation
        duration = image.info['duration']
        if args.loop:
            images = cycle(images)

        for img in images:
            show_image(rgbm, img)
            time.sleep(duration / 1000)

def cmd_swapbuffers(args):
    rgbm = create_rgbm(args)
    rgbm.swapbuffers()

def cmd_layout(args):
    rgbm = create_rgbm(args)

    num_width, num_height = rgbm.layout_size
    width, height = rgbm.size

    frame = Frame(size=(width, height), color=(0, 0, 0))

    for j in xrange(0, num_height):
        for i in xrange(0, num_width):
            num = (j * (num_width)) + i + 1
            pos = (8*i+1, 8*j-1)
            frame = frame.text(str(num), pos)

    # frame.show()

    frame = frame.torgb16()

    rgbm.write_frame(frame)
    rgbm.swapbuffers()

if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-l', '--layout', type=str, default="[[1,2],[3,4]]")

    subparsers = parser.add_subparsers(help='sub-command help')

    parser_clear = subparsers.add_parser('clear', help='clear color')
    parser_clear.add_argument('r', nargs='?', default='0', help='red value (default: %(default)s)')
    parser_clear.add_argument('g', nargs='?', default='0', help='green value (default: %(default)s)')
    parser_clear.add_argument('b', nargs='?', default='0', help='blue value (default: %(default)s)')
    parser_clear.add_argument('-n', '--no-swapbuffers', action='store_true')
    parser_clear.set_defaults(func=cmd_clear)

    parser_text = subparsers.add_parser('text', help='show text')
    parser_text.add_argument('text')
    parser_text.add_argument('-c', '--color', nargs=3, type=int,
            metavar=('r', 'g', 'b'), default=(255, 255, 255),
            help='text color')
    parser_text.add_argument('-b', '--background', nargs=3, type=int,
            metavar=('r', 'g', 'b'), default=(0, 0, 0),
            help='background color')
    parser_text.set_defaults(func=cmd_text)

    parser_random = subparsers.add_parser('random', help='random colors')
    parser_random.add_argument('--min', type=int, default=0)
    parser_random.add_argument('--max', type=int, default=255)
    parser_random.set_defaults(func=cmd_random)

    parser_image = subparsers.add_parser('image', help='show image')
    parser_image.add_argument('image')
    parser_image.add_argument('--loop', type=bool, default=True)
    parser_image.set_defaults(func=cmd_image)

    parser_swapbuffers = subparsers.add_parser('swapbuffers', help='perform swapbuffers')
    parser_swapbuffers.set_defaults(func=cmd_swapbuffers)

    parser_layout = subparsers.add_parser('layout', help='show layout')
    parser_layout.set_defaults(func=cmd_layout)

    args = parser.parse_args()
    args.func(args)
