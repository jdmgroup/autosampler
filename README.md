Arduino-powered autosampler
===========================

Written by [Thomas W. Phillips](http://www3.imperial.ac.uk/people/thomas.phillips07)

## Licence

[CC-BY 3.0](http://creativecommons.org/licenses/by/3.0/deed.en_US)

## Requirements

Requires [PySerial 2.6](http://pyserial.sourceforge.net). Developed/tested on Windows 7 with Python 2.7.3 (Enthought Canopy 7.3.1 64-bit).

## RS232 Commands

1. Switch valve off: `0`
2. Switch valve on: `1`
3. Advance one position: `2`
4. Check Arduino is responding: `?`

## Arduino auto reset

The Arduino Uno automatically resets itself upon opening a serial connection. Two options to deal with this:

1. Keep the serial connection open when in use, which is what `autosampler.py` does.
2. Break the [RESET EN jumper](http://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection).
