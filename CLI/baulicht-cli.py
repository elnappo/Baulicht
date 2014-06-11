#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import argparse


parser = argparse.ArgumentParser(description="Baulicht command line interface to change mode, add text,"
                                             " remove text or pause the blinking.",
                                 epilog="That's how to do it!")

parser.add_argument("-l", "--list", action='store_true', help="List all active texts")
parser.add_argument("-a", "--add", type=str, metavar='<string>', help="Add Text to morse")
parser.add_argument("-r", "--remove", type=int, metavar='<int>', help="Remove Text")
parser.add_argument("-m", "--mode", choices=["text", "blink"], help="Set mode to text or blink")
parser.add_argument("-s", "--speed", type=int, metavar='<int>', help="length of a dit in ms")
parser.add_argument("-b", "--blink", nargs="?", metavar='<list<int>>', help="Set blink interval")
parser.add_argument("-p", "--pause", choices=["on", "off"], help="Stop morse/blink")

args = parser.parse_args()
