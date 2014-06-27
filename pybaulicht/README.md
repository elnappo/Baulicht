# pybaulicht
## Requirements
* python 2
* dbus-python

## Install
```shell
    $ python setup.py install
```

## Usage
```python
from pybaulicht import BaulichtDbus
baulicht = BaulichtDbus()
baulicht.speed = 300
baulicht.add_text("Hello World")
baulicht.start()
```
