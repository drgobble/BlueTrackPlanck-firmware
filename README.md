# BlueTrackPlanck-firmware
Firmware for the bluetooth planck.

Intro
=====
The keyboard and circuit can be seen at
https://www.reddit.com/r/MechanicalKeyboards/comments/31wn3e/modification_bluetrackplanck/
and
https://www.reddit.com/r/MechanicalKeyboards/comments/2z58z8/photos_custom_built_bluetooth_planck/
There is a BOM in the build logs.

The matrix scanning firmware is custom. It prepares packets that are sent over UART to the 
Bluefruit EZ-Key module, which then sends them over Bluetooth. There is currently no way to 
pair the module from the firmware since I never bothered soldering that connection, you have 
to open the case and hit the pair button. I also never implemented sleep mode on the Bluefruit,
which you can do by pulling RST to ground on the module to bring it down to 2A consumption 
from 20A.

The ps2 handling for the trackpoint module is gutted from the tmk firmware.

Installation
============
Build it with "make", and the output file is "main.hex" to be loaded onto the AVR. It's currently
configured for a DIP Atmega328 with the internal oscillator. I don't remember how to configure 
everything. 

TODO
====
Development on this code is dead, but I will help people getting started. My next version will 
use the new chip from Adafruit that has the Bluetooth module and Atmega on the same board.

Questions
=========
Message my reddit account /u/drgobble and I'll help.
