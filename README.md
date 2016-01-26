# BasementLight
A collection of functions and examples specifically made for the basement lighting installation.

The basement lighting installation was made in December 2015 by Jacob Alkema. 
http://www.jacobalkema.nl/

The installation consists out of three rows of ledstrips. Each row has 7 strips with white warm light and 7 strips with white cold light

Each strip can be individually controlled with the DMX protocol. There are several options to control DMX. This repository gives examples for Arduino and USB.

# Arduino
Use an Arduino to control the installation. This example features three example animations and some powerful functions to create your own programs.

## Hardware
In order to control the installation you will need an Arduino with a Dmx interface. If you are a student at the TU/e you may borrow a Dmx interface from the lightlab (scroll down for email address).

We used the following hardware:
1. Arduino Uno.
2. DMX shield v1.1 (Designed by Interactive Matter).
3. Three simple buttons (https://www.arduino.cc/en/Tutorial/Button).

The next step is to setup your hardware:
1. Connect the Dmx shield to the Arduino.
2. Connect the Dmx cable to the Dmx shield (The cable should be in the corner of the left room in the lightlab).
3. If you are going to use the example code then make sure you have the buttons connected to pin 8, 9 and 10 of the Arduino.
4. Turn on the installation (There is a small door behind the big pillar, enter and look for the switch).

## Software
1. Download the example code from the repository and put it in your Arduino sketchbook. To find the location of your sketchbook: In the arduino IDE go to "Preferences". The location is in the first field "Sketchbook location:".
2. Open the example code
3. Upload!
4. Try switching between scenes by pressing the buttons. 

### Program documentation
The program is fully commented and should explain itself. However if itisn't clear then this might section help. This is an overview of the functions of the program:

#### setBrightnessAll(b)
Use this function to set the brightness of all ledstrips.
- b: the brightness you want to set the strips to. This should be a value between 0 - 255.

#### setBrightnessWarmAll(b)
Use this function to set the brightness of all WARM ledstrips.
- b: the brightness you want to set the strips to. This should be a value between 0 - 255.

#### setBrightnessColdAll(b)
Use this function to set the brightness of all COOL ledstrips.
- b: the brightness you want to set the strips to. This should be a value between 0 - 255.

#### setBrightness(warm, pos, b)
Use this function to set the brightness of a specific set of warm or cool ledstrips. 
- warm: is a boolean which allows you to select the warm or cool ledstrips.
- pos: the position of the ledstrips you want to control. This should be a value between 1 and 7. 1 being the most left ledstrips, 7 being the most right.
- b: the brightness you want to set the strips to. This should be a value between 0 - 255.

#### updateFadingAnimation(warm)
- warm: allows you to set the animation to a warm or a cool light

Currently this is a fading animation that fades a light from left to right. This animation should be called in the loop at all times. It doesn't work if your program uses DELAYS! 

This function can serve as the base for any fading animation. It counts from 0 to 255 and then increases the currentStep. This allows you to slowly increase the brightness of one step and then go to the next step, which might be the decreasing of that section.

currentStep step doesn't reset when it reaches the end of the sections (which is at 7), it simple keeps incrementing. A modulo is used to calculate the current position. So currently this function does something like this:
- currentStep: decreasing from 255 to 0
- currentStep + 1: increasing from 127 to 255
- currentStep + 2: increasing from 0 to 127

#### updateLightningAnimation
- coming soon -

The lightning animation comes with a Processing sketch that play a thunder sound with each lightning strike. This sketch can be found in the Processing folder of the repository.


#### DmxChannelValues[DmxChannels]
The values of all channels
- coming soon -

# USB

- coming soon -

# Help

For questions send an email to: ID [dot] Lightsupport [at] tue [dot] nl