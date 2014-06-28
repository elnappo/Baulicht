#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import argparse

from pybaulicht import BaulichtDbus, BaulichSettings


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Baulicht command line interface to change mode, add text,"
                                                 " remove text or pause the blinking.",
                                     epilog="That's how to do it!")

    parser.add_argument("-l", "--list", action='store_true', help="List all active texts")
    parser.add_argument("-a", "--add", type=str, metavar='<string>', help="Add Text to morse")
    parser.add_argument("-r", "--remove", type=int, metavar='<int>', help="Remove Text by ID")
    parser.add_argument("-m", "--mode", choices=["text", "blink"], help="Set mode to text or blink")
    parser.add_argument("-s", "--speed", type=int, metavar='<int>', help="length of a dit in ms")
    parser.add_argument("-b", "--blink", nargs="?", metavar='<list<int>>', help="Set blink interval")
    parser.add_argument("-p", "--pause", choices=["on", "off"], help="Stop morse/blink")
    parser.add_argument("--pin", type=int, metavar='<int>', help="Set GPIO Pin")
    parser.add_argument("--status", action="store_true", help="Show current status")
    parser.add_argument("--start", action="store_true", help="Start morse/blink")
    parser.add_argument("--stop", action="store_true", help="Stop morse/blink")
    args = parser.parse_args()

    baulicht = BaulichtDbus()
    baulicht_settings = BaulichSettings()

    if args.status:
        paused = baulicht.paused
        mode = baulicht.mode
        speed = baulicht_settings.dit
        pin = baulicht_settings.pin
        text_spacing = baulicht_settings.text_spacing
        print("Current System Status:")
        print("Paused: %s" % (paused))
        print("Mode: %s" % (mode))
        print("Speed: %s" % (speed))
        print("GPIO pin: %s" % (pin))
        print("Text Spacing: %s" % (text_spacing))

    if args.list:
        for text in baulicht.list_text():
            print(text)

    if args.remove:
        baulicht.remove_text(args.remove)

    if args.add:
        path = baulicht.add_text(args.add)
        print('Added "%s". Path is "%s"' % (args.add, path))

    if args.pause == "on" or args.stop:
        baulicht.stop()
        print("Stop morse")

    elif args.pause == "off" or args.start:
        baulicht.start()
        print("Start morse")

    if args.speed:
        baulicht_settings.dit = args.speed
        print("Speed is now %d" % (baulicht_settings.dit))

    if args.mode:
        baulicht.mode = args.mode
        print("Set mode to %s" % (baulicht.mode))

    if args.pin:
        baulicht_settings.pin = args.pin
        print("GPIO pin is now %d" % (baulicht_settings.pin))
