# Program documentation

## BasementLightExample
The program is fully commented and should explain itself. However if itisn't clear then this might section help. This is an overview of the functions of the program.

### Dependencies
All dependencies are included in the libraries folder.
- DmxSimple: https://github.com/Cathedrow/DmxSimple

### Functions

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
- warm: set fading light to be cool or warm

Currently this is a fading animation that fades a light from left to right. This animation should be called in the loop at all times. It doesn't work if your program uses DELAYS! 

This function can serve as the base for any fading animation. It counts from 0 to 255 and then increases the currentStep. This allows you to slowly increase the brightness of one step and then go to the next step, which might be the decreasing of that section.

currentStep step doesn't reset when it reaches the end of the sections (which is at 7), it simple keeps incrementing. A modulo is used to calculate the current position based on the currentStep. So currently each step this function does something like this:
- currentStep: decreasing from 255 to 0
- currentStep + 1: increasing from 127 to 255
- currentStep + 2: increasing from 0 to 127

#### updateLightningAnimation
This wouldn't be a fake basement window if we wouldn't be able to simulate lightning. Therefore we have made this lightning animation!

The lightning animation comes with a Processing sketch that plays a thunder sound with each lightning strike. This sketch can be found in the Processing folder of the repository.
https://github.com/LightLabTUe/BasementLight/tree/master/Processing

##### Function structure:
- To start A batch of lightingstrikes is created. This batch has a random starting time and random length.
- Lightning strikes hit during a batch at random intervals and with random strengths.
- When a lightning stike hits a BANG is printed to the serial port, this is used by the processing sound sketch.
- Lightning strikes slowly fade out. 

### Handy global variables

#### DmxChannelValues[DmxChannels]
This is an array with all the values of the DmxChannels.

#### buttonState[3]
The state of the buttons. TRUE is pressed, FALSE is not pressed.

# Help
For questions send an email to: ID [dot] Lightsupport [at] tue [dot] nl