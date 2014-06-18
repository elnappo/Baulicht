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


import dbus
bus = dbus.SessionBus()
root_object = bus.get_object("de.naptower.Baulicht", "/")

if args.status:
    print("Current System Status:")
    paused = root_object.paused()
    mode = root_object.mode()
    #speed = root_object.
    print("Paused: %s" % (paused))
    print("Mode: %s" % (mode))
    
if args.add:
    path = root_object.addText(args.add , 1, 1)
    print('Added "%s". Path is "%s"' % (args.add, path))
    
if args.pause == "on":
    root_object.setPaused(False)
    print("Start morse")
elif args.pause == "off":
    root_object.setPaused(True)
    print("Stop morse")
    
if args.speed:
    root_object.setSpeed(args.speed)
    print("Set speed to %d" % (args.speed))

if args.mode == "text":
    root_object.setMode(0)
    print("Set mode to %s" % (args.mode))
elif args.mode == "blink":
    root_object.setMode(1)
    print("Set mode to %s" % (args.mode))
    