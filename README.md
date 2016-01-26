# BasementLight
A collection of functions and examples specifically made for the basement lighting installation.

The basement lighting installation was made in December 2015 by Jacob Alkema. 
http://www.jacobalkema.nl/

The installation consists out of three rows of ledstrips. Each row has 7 strips with white warm light and 7 strips with white cold light

Each strip can be individually controlled with the DMX protocol. There are several options to control DMX. This repository gives examples for Arduino and USB.

# Arduino
Use an Arduino to control the installation. This example features three example animations and some powerful functions to create your own programs.

## Hardware
In order to control the installation you will need an Arduino with a Dmx shield. If you are a student at the TU/e you may borrow a Dmx shield from the lightlab (scroll down for email address).

### Hardware components:
1. Arduino Uno.
2. DMX shield v1.1 (Designed by Interactive Matter).
3. Three simple buttons (https://www.arduino.cc/en/Tutorial/Button).

### How to setup your hardware:
1. Connect the Dmx shield to the Arduino.
2. Connect the Dmx cable to the Dmx shield (The cable should be in the corner of the left room in the lightlab).
3. If you are going to use the example code then make sure you have the buttons connected to pin 8, 9 and 10 of the Arduino.
4. Turn on the installation (There is a small door behind the big pillar, enter and look for the switch).

## Software

### How to setup your software:
1. Download the example code from the repository and put it in your Arduino sketchbook. To find the location of your sketchbook: In the arduino IDE go to "Preferences". The location is in the first field "Sketchbook location:".
2. Open the example code
3. Upload!
4. Try switching between scenes by pressing the buttons. 

### Program documentation
The program is fully commented and should explain itself. For extra explanation of each function, look here: 
https://github.com/LightLabTUe/BasementLight/tree/master/Arduino 

# USB
Another option is to use the USB port on your computer. For this option you will need:

- A USB to DMX serial interface* (QuickDMX D512)
- QuickDMX: http://download.thelightingcontroller.com/software/V7/QuickDmx/
- Optional: the example: 

If you are a student at the TU/e you may borrow a this interface from the lightlab (scroll down for email address). 

* Other DMX interfaces will also work, just not with the example.

# Help

For questions send an email to: ID [dot] Lightsupport [at] tue [dot] nl