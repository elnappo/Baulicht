# CLI
## Usage
	usage: baulicht-cli.py [-h] [-l] [-m {text,blink}] [-a <string>] [-r <int>]
	                       [-b [<list<int>>]] [-p {on,off}]

	Baulicht command line interface to change mode, add text, remove text or pause
	the blinking.

	optional arguments:
	  -h, --help            show this help message and exit
	  -l, --list            List all active texts
	  -m {text,blink}, --mode {text,blink}
	                        Set mode to text or blink
	  -a <string>, --add <string>
	                        Add Text to morse
	  -r <int>, --remove <int>
	                        Remove Text
	  -b [<list<int>>], --blink [<list<int>>]
	                        Set blink interval
	  -p {on,off}, --pause {on,off}
	                        Stop morse/blink

	That's how to do it!