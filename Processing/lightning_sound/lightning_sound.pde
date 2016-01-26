/*** Lightlab basement example code ***/
/*** Author: Martijn Imhoff         ***/
/*** Last update: 25/1/2016         ***/

import processing.serial.*;
import ddf.minim.*;
Minim minim;
AudioPlayer[] file;
int lastSound;

int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port

void setup() {
  size(200, 200);
  background(15);
  
  // List all the available serial ports
  printArray(Serial.list());
  
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.clear();
  
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
    
  // Preload the sound files
  minim = new Minim(this);
  file = new AudioPlayer[4];
  
  for(int i = 0; i < 4;i++) {
   println(dataPath("thunder" + (i+1) + ".wav"));
   file[i] = minim.loadFile(dataPath("thunder" + (i+1) + ".wav"));
  }
}      

void draw() {  
  while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      println(myString);
      
      if (myString.contains("BANG")) {
        // we dont want the same sound to play twice after eachother, therefore
        int randomSound = int(random(4));
        while(lastSound == randomSound) {
          randomSound = int(random(4));
        }
        
        // rewind the sound, then play it (it might have been played before)
        file[randomSound].rewind();
        file[randomSound].play();
        
        // Some useless but nice looking visual feedback that a sound is being played
        background(15);
        fill(150 + randomSound * 20);
        rect(50,50,100,100);
      }
    }
  }
}