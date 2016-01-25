/*** Lightlab basement example code ***/
/*** Author: Martijn Imhoff         ***/
/*** Last update: 25/1/2016         ***/

import processing.serial.*;
import ddf.minim.*;
Minim minim;
AudioPlayer file[];

int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port

void setup() {
  size(100, 100);
  background(15);
  
  // List all the available serial ports
  printArray(Serial.list());
  
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 115200);
  myPort.clear();
  
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
    
  // Preload the sound files
  minim = new Minim(this);
  for(int i = 0; i < 4;i++) {
    println("thunder" + (i+1) + ".mp3");
    //file[i] = minim.loadFile("thunder" + (i+1) + ".mp3");
    file[i] = minim.loadFile("thunder1.wav");
  }
}      

void draw() {
  background(15);
  
  while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      println(myString);
      
      if (myString.contains("BANG")) {
        int randomSound = int(random(4));
        file[randomSound].play();
        
        fill(15 + randomSound * 10);
        rect(20,20,60,60);
      }
    }
  }
}