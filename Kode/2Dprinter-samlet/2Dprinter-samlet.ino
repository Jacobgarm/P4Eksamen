#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <LITTLEFS.h>
#include <TJpg_Decoder.h>
#include <ESP32Servo.h>
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
#define servoPin 12

//Pins for stopping buttons
#define xBackStopPin 0
#define yBackStopPin 13
#define xFrontStopPin 16
#define yFrontStopPin 34

//Pins for joystick
#define joystickXPin 33
#define joystickYPin 32
#define joystickZPin 35

//Joystick parameters
#define joystickXMid 2048
#define joystickYMid 2048
#define joystickDeadzone 360000
#define joystickMoveInterval 300

//Pins for chip select
#define tftCSPin 15
#define sdCSPin 5

TFT_eSPI tft = TFT_eSPI();
Servo myservo;

//State vars
String screenName = "Hovedmenu";
String mainMenuNames[100] = {"Printer til start", "Print fra SD-kort", "Print med joystick", "Kalibrer og reset"};
String listNames[100] = {};
int marked = 0;

String selectedFile;
float penXPos;
float penYPos;
bool penIsDown = false;
String filNavn;
bool joystickDown = false;

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
  

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin servoPin to the servo object
  
  // Begge CS pins HIGH så de ikke begge kan kommunikeres med
  digitalWrite(tftCSPin, HIGH);
  digitalWrite(sdCSPin, HIGH);
  
  //Starter for skærmen, samt sætter den til sort
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(2);
  tft.setSwapBytes(true);

  //Setup til JPG bibliotek
  TJpgDec.setJpgScale(1);
  TJpgDec.setCallback(tft_output);

  //Start SD-kortet
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }

  
  setNamesToMain();
  //resetPos();
  //displayMenu();
  //drawTurtle("/test.turtle");
  joystickControl();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (screenName == "Hovedmenu"){
    if (digitalRead(joystickZPin) == LOW && !joystickDown) {
      enterMenu(listNames[marked]);
      joystickDown = true;
    } else if (digitalRead(joystickZPin) == HIGH && joystickDown)
      joystickDown = false;

    unsigned long startTime = millis();
    while (analogRead(joystickXPin) == 0 || analogRead(joystickXPin) == 4095) {
      if (millis() > startTime + joystickMoveInterval){
        marked += analogRead(joystickXPin) == 0 ? -1 : 1;
        break;
      }
    }
    displayMenu();
  } else if (screenName = "Print fra SD-kort") {
    if (digitalRead(joystickZPin) == LOW && !joystickDown) {
      if (listNames[marked] == "Tilbage")
        enterMenu("Hovedmenu");
      else {
        if (listNames[marked].indexOf(".turtle") == -1)
          printImage(listNames[marked]);
        else
          drawTurtle(listNames[marked]);
      }
      joystickDown = true;
    } else if (digitalRead(joystickZPin) == HIGH && joystickDown)
      joystickDown = false;

    unsigned long startTime = millis();
    while (analogRead(joystickXPin) == 0 || analogRead(joystickXPin) == 4095) {
      if (millis() > startTime + joystickMoveInterval){
        marked += analogRead(joystickXPin) == 0 ? -1 : 1;
        break;
      }
    }
    displayMenu();
  }
}
