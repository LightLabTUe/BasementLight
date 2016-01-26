/*** Lightlab basement example code ***/
/*** Author: Martijn Imhoff         ***/
/*** Last update: 25/1/2016         ***/

/*** DMX Channels                   ***
 *   The installation has warm and cold light. (and one funky random rgb lamp)
 *   I've mapped the channels in this overview:
//************  Warm light:
 * Top row      1   - 7
 * Middle row   8   - 14
 * Bottom row   15  - 21
 * Bottom extra 22
//************  Cold Light
 * Top row      25  – 31
 * Middle row   32  – 38
 * Bottom row   39  – 45
//************  Blue, Red, Green (RGB)
 * middle/left  46  - 48
*/

#include <DmxSimple.h>

// Dmx vars
#define DmxChannels 48
byte DmxChannelValues[DmxChannels];

// buttons vars
byte buttonPins[3] = {8, 9, 10};

unsigned long lastPress[3];
boolean buttonState[3];
#define debounceDelay 100

// program state
byte state = 255;

void setup() {
  // init the button pins
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  // init serial connection
  Serial.begin(9600);

  // The DMX shield v1.1 has the Dmx pin on nr 11
  DmxSimple.usePin(11);

  // turn all strips off at the start
  setBrightnessAll(0);
}

void loop() {
  // a loop to update the button state.
  for (int i = 0; i < 3; i++) {
    // read the buttons and time.
    int readValue = digitalRead(buttonPins[i]);
    int readTime = millis();

    // Check if a button has been released
    if (readValue == 0 && buttonState[i] && readTime - lastPress[i] > debounceDelay) {
      Serial.print("Button ");
      Serial.print(i);
      Serial.println(" is released");

      // Do things on release

      buttonState[i] = false;
    }

    // Check if a button has been pressed
    if (readValue == 1 && !buttonState[i] && readTime - lastPress[i] > debounceDelay) {
      // handle the button press
      Serial.print("Button ");
      Serial.print(i);
      Serial.println(" is pressed");
      buttonState[i] = true;
      lastPress[i] = millis();

      // Do things on press


      // Set state for animations
      state = i;
      
      // reset lights on button press
      setBrightnessAll(0);

      // set a dark background for the state 0 animation
      if (state == 0) {
        setBrightnessColdAll(5);
      }

      // set a warm background for the state 1 animation
      if (state == 1) {
        setBrightnessWarmAll(180);
      }

      // set a cold background for the state 2 animation
      if (state == 2) {
        setBrightnessColdAll(100);
      }
    }
  }

  // Put animation updates here
  // The animations are handled with millis
  // This will allow you to do other stuff while the animation is running
  if (state == 0) {
    updateLightningAnimation();
  }

  if (state == 1) {
    updateFadingAnimation(false);
  }

  if (state == 2) {
    updateFadingAnimation(true);
  }
}

// Function updateLightningAnimation()
int strength = 0;
unsigned long nextLightning = 0, startLightningBatch = 0, lastFadeLightningStep = 0;
int maxNextLightningDelay = 800;
float fadeOutSpeed = 0.1;  // percentage
int fadeLightningTimeStep = 25;

int lightningBatchLength; // initial length of a batch
int maxLightningBatchLength = 1500; // max duration of a lightning batch
int maxNextLightningBatchDelay = 15000; // max time between 2 lightning batches
boolean isBatchRunning = true;

void updateLightningAnimation() {
  // Check if a batch should start
  if(millis() > startLightningBatch && !isBatchRunning) {
    isBatchRunning = true;
  }
  
  // Check if a lightningbatch is going on
  if (isBatchRunning) {
    //inside that batch, do several lightnings
    if (millis() > nextLightning) {
      strength = 55 + random(200);
      Serial.print("BANG ");
      Serial.println(strength);

      // generate moment for next lightning
      nextLightning = millis() + random(maxNextLightningDelay);
    }
  }

  // once the batch is over, set new starttime and new length for next lightning batch
  // only do this once
  if (millis() >  startLightningBatch + lightningBatchLength && isBatchRunning) {
    startLightningBatch = millis() + random(maxNextLightningBatchDelay);
    lightningBatchLength = 500 + random(maxLightningBatchLength); // 500 = minimum length
    isBatchRunning = false;
  }
  
  // apply the lightning
  setBrightnessColdAll(strength);

  // fade out effect
  if (millis() - lastFadeLightningStep > fadeLightningTimeStep && strength > 0) {
    strength = (int) strength * (1 - fadeOutSpeed);
    lastFadeLightningStep = millis();
  }
}

// Function updateFadingAnimation(warm)
// type     : name  - (allowed values) // description
// boolean  : warm  - (true/false)     // cycle through warm or cold colors
// Global vars:
unsigned long lastAnimationUpdate;
unsigned long currentStep = 3; // warm and cold lights start at one
int animationTimeStep = 5;
byte stepBrightness = 0;

void updateFadingAnimation(boolean warm) {
  if (millis() - lastAnimationUpdate > animationTimeStep) {
    lastAnimationUpdate = millis();

    // fadeout current step
    setBrightness(warm, currentStep % 7 + 1, easing(255 - stepBrightness));

    // fadein last part current step + 1
    setBrightness(warm, (currentStep + 1) % 7 + 1, easing(stepBrightness) / 2 + 127);

    // fadein first part current step + 2
    setBrightness(warm, (currentStep + 2) % 7 + 1, easing(stepBrightness) / 2);

    // cycle through brightness and step
    if (stepBrightness < 255) {
      stepBrightness++;
    } else {
      currentStep++;
      stepBrightness = 0;
    }
  }
}

// Function setBrightnessColdAll(b)
// type     : name  - (allowed values) // description
// int      : b     - (0  - 255)       // brightness of the lights will be controlled
// returns false when invalid input is given
boolean setBrightnessColdAll(int b) {
  if (b < 0 || b > 255) return false;
  for (int i = 1; i < 8; i++) {
    setBrightness(false, i, b);
  }
  return true;
}

// Function setBrightnessWarmAll(b)
// type     : name  - (allowed values) // description
// int      : b     - (0  - 255)       // brightness of the lights will be controlled
// returns false when invalid input is given
boolean setBrightnessWarmAll(int b) {
  if (b < 0 || b > 255) return false;
  for (int i = 1; i < 8; i++) {
    setBrightness(true, i, b);
  }
  return true;
}

// Function setBrightnessAll(b)
// type     : name  - (allowed values) // description
// int      : b     - (0  - 255)       // brightness
// returns false when invalid input is given
boolean setBrightnessAll(int b) {
  if (b < 0 || b > 255) {
    // invalid input
    return false;
  }

  for (int channel = 1; channel <= DmxChannels; channel++) {
    DmxSimple.write(channel, b);
    DmxChannelValues[channel] = b;
  }
  return true;
}

// Function setBrightness(warm, pos, b)
// type     : name  - (allowed values) // description
// boolean  : warm  - (true/false)     // set to true for controlling warm lights, false for cold lights
// int      : pos   - (1  - 7)         // position of controlled lights. 1 = left, 7 = right.
// int      : b     - (0  - 255)       // brightness of the lights will be controlled
// returns false when invalid input is given
boolean setBrightness(boolean warm, int pos, int b) {
  if (pos < 1 || pos > 7 || b < 0 || b > 255) {
    // invalid input
    return false;
  }

  for (int x = 0; x < 3; x++) {
    if (warm) {
      int channel = pos + x * 7;
      DmxSimple.write(channel, b);
      DmxChannelValues[channel] = b;
    } else {
      int channel = 24 + pos + x * 7;
      if (channel > 45) return true; // above 45 are colors, we dont want those for this function
      DmxSimple.write(channel, b);
      DmxChannelValues[channel] = b;
    }
  }
  return true;
}

// Function easing(value) return int
// type     : name  - (allowed values) // description
// value    : value - (0 - 255)        // The value that is to be eased
const float pi = 3.14;
int easing(byte value) {
  return int( (cos(value * pi / 255 - pi) + 1) * 127.5 );
}





