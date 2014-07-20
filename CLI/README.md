# CLI
## Usage
	usage: baulicht-cli.py [-h] [-l] [-a <string>] [-r <int>] [-s <int>]
                       [-p {on,off}] [--pin <int>] [--status] [--start]
                       [--stop]
	
	Baulicht command line interface to list, add, remove texts and change
	settings.
	
	optional arguments:
	  -h, --help            show this help message and exit
	  -l, --list            List all active texts
	  -a <string>, --add <string>
	                        Add Text to morse
	  -r <int>, --remove <int>
	                        Remove Text by ID
	  -s <int>, --speed <int>
	                        length of a dit in ms
	  -p {on,off}, --pause {on,off}
	                        Stop morse/blink
	  --pin <int>           Set GPIO Pin
	  --status              Show current status
	  --start               Start morse/blink
	  --stop                Stop morse/blink
	
	That's how to do it!
	
