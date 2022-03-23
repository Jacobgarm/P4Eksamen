#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <JPEGDecoder.h>
#include "FontIkkeFed.h"
#include "FontFed.h"

//Standard A4 paper size
#define A4width 297
#define A4height 210

//Standard A3 paper size
#define A3width 420
#define A3height 297

//Pins for steppermotors
#define xStepPin 26
#define xDirPin 25

#define yStepPin 14
#define yDirPin 27

//Pins for servo motor
#define servoPin 34

//Pins for stopping buttons
#define xBackStopPin 30
#define yBackStopPin 31
#define xFrontStopPin 30
#define yFrontStopPin 31

//Pins for joystick
#define joystickXPin 33
#define joystickYPin 33
#define joystickZPin 35

//Pins for chip select
#define tftCSPin 15
#define sdCSPin 5

void setup() {
  // Start Serial
  Serial.begin(9600);

  // Pin Modes
  pinMode(xStepPin,OUTPUT);
  pinMode(xDirPin,OUTPUT);
  pinMode(yStepPin,OUTPUT);
  pinMode(yDirPin,OUTPUT);
  pinMode(servoPin,OUTPUT);
  pinMode(xBackStopPin,INPUT);
  pinMode(yBackStopPin,INPUT);
  pinMode(xFrontStopPin,INPUT);
  pinMode(yFrontStopPin,INPUT);
  pinMode(joystickXPin, INPUT_PULLUP);
  pinMode(joystickYPin, INPUT_PULLUP);
  pinMode(joystickZPin, INPUT_PULLUP);
  pinMode(tftCSPin,OUTPUT);
  pinMode(sdCSPin,OUTPUT);

  // Begge CS pins HIGH så de ikke begge kan kommunikeres med
  digitalWrite(tftCSPin, HIGH); // TFT screen chip select
  digitalWrite(sdCSPin, HIGH); // SD chip select
  
  //Starter for skærmen, samt sætter den til sort
  tft.init();
  tft.fillScreen(TFT_BLACK);

  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
