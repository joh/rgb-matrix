#!/usr/bin/env python
import argparse

from rgbmatrix import RGBMatrix

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

    args = parser.parse_args()
    args.func(args)
