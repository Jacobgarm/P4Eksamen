#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <JPEGDecoder.h>
#include "dejavuserif.h"
#include "dejavuserifbold.h"

#define sgn(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))

//Standard A4 paper size
#define A4width 297
#define A4height 210

//Standard A3 paper size
#define A3width 420
#define A3height 297

//Size values
#define stepsPerMM 5 //Hvor mange steps der skal til for at bevæge en millimeter
#define printDotDistance 4 //Hvor mannge millimeter der er mellem hver prik der printes

//Dirs for steppermotor
#define xPosDir HIGH
#define yPosDir HIGH

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

//Joystick parameters
#define joystickXMid 2048
#define joystickYMid 2048
#define joystickDeadzone 360000

//Pins for chip select
#define tftCSPin 15
#define sdCSPin 5

TFT_eSPI tft = TFT_eSPI();

//State vars
String screenName = "Hovedmenu";
String mainMenuNames[100] = {"Printer til start", "Print fra SD-kort", "Print med joystick", "Kalibrer og reset"};
String listNames[100] = mainMenuNames;
int marked = 0;

String selectedFile;
double penXPos;
double penYPos;
bool penIsDown;
String filNavn;

//Start på void setup og loop------------------------------------------------------------------------------------------------------------------------
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
  digitalWrite(tftCSPin, HIGH);
  digitalWrite(sdCSPin, HIGH);
  
  //Starter for skærmen, samt sætter den til sort
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(2);

  //Start SD-kortet
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }

  drawTurtle("/test.turtle");
  displayMenu();
}

void loop() {
  // put your main code here, to run repeatedly:
}
