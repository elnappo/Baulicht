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
parser.add_argument("--status", action="store_true", help="Stop morse/blink")

args = parser.parse_args()

from baulicht_dbus import BaulichtDbus

baulicht = BaulichtDbus()

if args.status:
    print("Current System Status:")
    paused = baulicht.paused
    mode = baulicht.mode
    #speed = baulicht.speed
    print("Paused: %s" % (paused))
    print("Mode: %s" % (mode))
    # print("Speed: %s" % (speed))

if args.list:
    baulicht.list_text()

if args.add:
    path = baulicht.add_text(args.add)
    print('Added "%s". Path is "%s"' % (args.add, path))
    
if args.pause == "on":
    baulicht.paused = True
    print("Stop morse")

elif args.pause == "off":
    baulicht.paused = False
    print("Stop morse")
    
if args.speed:
    baulicht.speed = args.speed
    print("Set speed to %d" % (args.speed))

if args.mode:
    baulicht.mode = args.mode
    print("Set mode to %s" % (args.mode))
