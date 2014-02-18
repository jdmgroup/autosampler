Arduino-powered autosampler
===========================

[Thomas W. Phillips](http://www.tomwphillips.co.uk)

## Licence

[CC-BY 3.0](http://creativecommons.org/licenses/by/3.0/deed.en_US)

## RS232 Commands
0 = switch valve off
1 = switch valve on
2 = advance one position
? = check Arduino is responding

## Arduino auto reset

The Arduino Uno automatically resets itself upon serial connection. Two options to get around this:

1. Break the [RESET EN jumper](http://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection).
2. Keep the serial connection open when in use.

## Tested on
Windows 7 64-bit using MATLAB R2013a and Arduino 1.0.5
