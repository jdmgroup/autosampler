Arduino-powered autosampler
===========================

[Thomas W. Phillips](http://www.tomwphillips.co.uk)

## Licence

[CC-BY 3.0](http://creativecommons.org/licenses/by/3.0/deed.en_US)

## RS232 Commands
0 = switch valve off, response `off\r\n`.
1 = switch valve on, response `on\r\n`.
2 = advance one position, response `moved\r\n`.
? = check Arduino is responding, response `ready\r\n`.

## Arduino auto reset

The Arduino Uno automatically resets itself upon opening a serial connection. Two options to deal with this:

1. Keep the serial connection open when in use, which is what `autosampler.py` does.
2. Break the [RESET EN jumper](http://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection).

## Requirements
Requires [PySerial 2.6][PySerial]. Developed/tested on Windows 7 with Python 2.7.3 ([Enthought Canopy][] 7.3.1 64-bit).