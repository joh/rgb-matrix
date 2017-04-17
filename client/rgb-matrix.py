#!/usr/bin/env python
import argparse
import ast
import numpy as np

from rgbmatrix import RGBMatrix
from rgbmatrix.frame import *

def cmd_clear(args):
    rgbm = RGBMatrix()

    r = int(args.r, 16)
    g = int(args.g, 16)
    b = int(args.b, 16)

    rgbm.clear(r, g, b)

    if not args.no_swapbuffers:
        rgbm.swapbuffers()

def cmd_swapbuffers(args):
    rgbm = RGBMatrix()
    rgbm.swapbuffers()

def cmd_test(args):
    layout = list(ast.literal_eval(args.layout))
    print("layout=", layout)

    rgbm = RGBMatrix(layout=layout)

    num_height = len(layout)
    num_width = len(layout[0])

    print("#width={} #height={}".format(num_width, num_height))

    height = num_height * 8
    width = num_width * 8

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
    subparsers = parser.add_subparsers(help='sub-command help')

    parser_clear = subparsers.add_parser('clear', help='clear color')
    parser_clear.add_argument('r', nargs='?', default='0', help='red value (default: %(default)s)')
    parser_clear.add_argument('g', nargs='?', default='0', help='green value (default: %(default)s)')
    parser_clear.add_argument('b', nargs='?', default='0', help='blue value (default: %(default)s)')
    parser_clear.add_argument('-n', '--no-swapbuffers', action='store_true')
    parser_clear.set_defaults(func=cmd_clear)

    parser_swapbuffers = subparsers.add_parser('swapbuffers', help='perform swapbuffers')
    parser_swapbuffers.set_defaults(func=cmd_swapbuffers)

    parser_test = subparsers.add_parser('test', help='perform test')
    parser_test.add_argument('-l', '--layout', type=str, default="[[1,2],[3,4]]")
    parser_test.set_defaults(func=cmd_test)

    args = parser.parse_args()
    args.func(args)
