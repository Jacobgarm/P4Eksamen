#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <LITTLEFS.h>
#include <TJpg_Decoder.h>
#include <ESP32Servo.h>
#include "dejavuserif.h"
#include "dejavuserifbold.h"
#include "SPIFFS.h"
#define FS_NO_GLOBALS

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
#define yPosDir LOW

//Pins for steppermotors
#define xStepPin 33
#define xDirPin 26

#define yStepPin 27
#define yDirPin 14

//Pins for servo motor
#define servoPin 12

//Pins for stopping buttons
#define xBackStopPin 17
#define yBackStopPin 13
#define xFrontStopPin 16
#define yFrontStopPin 34

//Pins for joystick
#define joystickXPin 25
#define joystickYPin 32
#define joystickZPin 35

//Joystick parameters
#define joystickXMid 2048 //Hvis det er med batterri så 2048, med pc 1348
#define joystickYMid 2048 //Hvis det er med batterri så 2048, med pc 1348
#define joystickDeadzone 360000
#define joystickMoveInterval 300

//Pins for chip select
#define tftCSPin 15
#define sdCSPin 5

TFT_eSPI tft = TFT_eSPI();
Servo myservo;

//State vars
String screenName = "Hovedmenu";
String mainMenuNames[100] = {"Printer til start", "Print fra SD-kort", "Print med joystick"};
String listNames[100] = {};
int marked = 0;
String selectedFile;
bool confirmChoice = true;
int prikNummer=1;

int procentLoad=0;
int TimerJz=0;
int timerZPin=0;


float penXPos = 0;
float penYPos = 0;
bool penIsDown = false;
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
  pinMode(joystickXPin, INPUT);
  pinMode(joystickYPin, INPUT);
  pinMode(joystickZPin, INPUT);
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
  if (!SD.begin(sdCSPin)) {
    Serial.println("Card Mount Failed");
    //return;
  }

  Serial.println(2);
  setNamesToMain();
  //resetPos();
  //displayMenu();
  //moveCoords(50,50);
  //penUp();
  //penDown();
  //drawTurtle("/test.turtle");
  //joystickControl();
  displayMenu();
}

void loop() {
  //Serial.print(digitalRead(xBackStopPin));
  //Serial.print(" ");
  //Serial.print(digitalRead(xFrontStopPin));
  //Serial.print(" ");
  //Serial.print(digitalRead(yBackStopPin));
  //Serial.print(" ");
  //Serial.println(digitalRead(yFrontStopPin));


  
  // Loops handling er afhængig af hvilken skærm der vises lige nu.
  if (screenName == "Hovedmenu"){

    //Hvis joysicket er trykket ned, og det ikke var før, vælges menuen
    if (digitalRead(joystickZPin) == HIGH && !joystickDown) {
      while(joystickZPin==HIGH){
          timerZPin++;
          Serial.println(analogRead(joystickYPin));
          if(timerZPin==300){
            timerZPin=0;
            joystickDown = true;
            enterMenu(mainMenuNames[2]);
          }
          delay(1);
        }
     timerZPin=0;
    } else if (digitalRead(joystickZPin) == LOW && joystickDown)
      joystickDown = false;

    //Hvis koysticket holdes nede i lang tid skal den markerede ændres
    unsigned long startTime = millis();
    while (analogRead(joystickYPin) == 0 || analogRead(joystickYPin) > 4000) {
      if (millis() > startTime + joystickMoveInterval){
        //marked += analogRead(joystickYPin) == 0 ? 1 : -1;
        if(marked>=1){
        marked += analogRead(joystickYPin) == 0 ? 1 : -1;
        }else if(marked==0){
          marked += analogRead(joystickYPin) == 0 ? 1 : 0;
        }
        //marked = marked % 3;
        displayMenu();
        break;
      }
    }
//---------------------------------------------------------------------------------------------------------------------------------------
  } else if (screenName= "Printer til start"){
    resetPos();
    marked=0;
    screenName="Hovedmenu";
    procentLoad=0;
    displayMenu();
//---------------------------------------------------------------------------------------------------------------------------------------
  } else if (screenName = "Print fra SD-kort") {
    if (digitalRead(joystickZPin) == LOW && !joystickDown) {
      if (listNames[marked] == "Tilbage")
        enterMenu("Hovedmenu");
      else {
        selectFile(listNames[marked]);
      }
      joystickDown = true;
    } else if (digitalRead(joystickZPin) == HIGH && joystickDown)
      joystickDown = false;

    unsigned long startTime = millis();
    while (analogRead(joystickXPin) == 0 || analogRead(joystickXPin) == 4095) {
      if (millis() > startTime + joystickMoveInterval){
        if(marked>=1){
        marked += analogRead(joystickXPin) == 0 ? -1 : 1;
        }else if(marked==0){
          marked += analogRead(joystickXPin) == 0 ? 0 : 1;
        }
        break;
      }
    }
    displayMenu();   
    //---------------------------------------------------------------------------------------------------------------------------------------
  } else if (screenName = "Confirm") {
    if (digitalRead(joystickZPin) == LOW && !joystickDown) {
      if (confirmChoice)
        if (listNames[marked].indexOf(".turtle") == -1)
          printImage(listNames[marked]);
        else
          drawTurtle(listNames[marked]);
      else {
        enterMenu("Hovedmenu");
      }
      joystickDown = true;
    } else if (digitalRead(joystickZPin) == HIGH && joystickDown)
      joystickDown = false;

    unsigned long startTime = millis();
    while (analogRead(joystickYPin) == 0 || analogRead(joystickYPin) == 4095) {
      if (millis() > startTime + joystickMoveInterval){
        confirmChoice = !confirmChoice;
        break;
      }
    }
    displayConfirm();
    //---------------------------------------------------------------------------------------------------------------------------------------
  } else if (screenName= "Print med joystick"){
    Serial.println("her");
    tft.setFreeFont(&DejaVu_Serif_Bold_16);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Du printer med joystick ",60,80);
    delay(1000);
    joystickControl();
    marked=3;
    screenName="Hovedmenu";
    displayMenu();
     
  }
  

}
