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
#define printDotDistance 5 //Hvor mannge millimeter der er mellem hver prik der printes

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
#define joystickDeadzone 90000
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
    return;
  }

  Serial.println(2);
  setNamesToMain();
  //resetPos();
  //displayMenu();
  //moveCoords(50,50);
  //penUp();
  //penDown();
  //drawTurtle("/test2.turtle");
  //joystickControl();
  //printImage("/bytes.bwb");
  displayMenu();

}

void loop() {
  // Loops handling er afhængig af hvilken skærm der vises lige nu.
  
  if (screenName == "Hovedmenu"){
    //Hvis joysicket er trykket ned, og det ikke var før, vælges menuen
    if (digitalRead(joystickZPin) == HIGH && !joystickDown) {
            joystickDown = true;
            enterMenu(listNames[marked]);
    } else if (digitalRead(joystickZPin) == LOW && joystickDown)
      joystickDown = false;

    //Hvis koysticket holdes nede i lang tid skal den markerede ændres
    unsigned long startTime = millis();
    while (analogRead(joystickYPin) == 0 || analogRead(joystickYPin) > 4000) {
      if (millis() > startTime + joystickMoveInterval){

        if(marked>=1){
            if(analogRead(joystickYPin)==0&&digitalRead(joystickZPin) == LOW){
              marked+=1;
            }else if(analogRead(joystickYPin) != 0&&digitalRead(joystickZPin) == LOW){
              marked+=-1;
              }
        }else if(marked==0){
            if(analogRead(joystickYPin)==0&&digitalRead(joystickZPin) == LOW){
              marked+=1;
            }else if(analogRead(joystickYPin) != 0&&digitalRead(joystickZPin) == LOW){
              marked+=-1;
        }}
        
        marked = marked % 3;
        displayMenu();
        break;
      }
    }
//---------------------------------------------------------------------------------------------------------------------------------------
  } else if (screenName = "Print fra SD-kort") {
         //Hvis joysicket er trykket ned, og det ikke var før, vælges menuen
    if (digitalRead(joystickZPin) == HIGH && !joystickDown) {
            joystickDown = true;
            if (listNames[marked] == "Tilbage")
        enterMenu("Hovedmenu");
      else {
        if (listNames[marked].indexOf(".turtle") == -1)
           printImage((char*)(listNames[marked].c_str()));
        else
           drawTurtle((char*)(listNames[marked].c_str()));
        return;
      }           
    } else if (digitalRead(joystickZPin) == LOW && joystickDown)
      joystickDown = false;

    //Hvis koysticket holdes nede i lang tid skal den markerede ændres
    unsigned long startTime = millis();
    while (analogRead(joystickYPin) == 0 || analogRead(joystickYPin) > 4000) {
      if (millis() > startTime + joystickMoveInterval){

        if(marked>=1){
            if(analogRead(joystickYPin)==0&&digitalRead(joystickZPin) == LOW){
              marked+=1;
            }else if(analogRead(joystickYPin) != 0&&digitalRead(joystickZPin) == LOW){
              marked+=-1;
              }
        }else if(marked==0){
            if(analogRead(joystickYPin)==0&&digitalRead(joystickZPin) == LOW){
              marked+=1;
            }else if(analogRead(joystickYPin) != 0&&digitalRead(joystickZPin) == LOW){
              marked+=-1;
        }}
        
        displayMenu();
        break;
      }
    }
  } else if(screenName=="Confirm"){
    
    //Denne kode under er mening at skulle lave en confirm skærm, men det kom ikke til at virke
    /*Serial.println("JEGEHRE");
    //screenName="Confirm";
    //Hvis joysicket er trykket ned, og det ikke var før, vælges menuen
    if (digitalRead(joystickZPin) == HIGH && !joystickDown) {
            joystickDown = true;
            if(confirmChoice==true){
            if (listNames[marked].indexOf(".turtle") == -1)
              printImage((char*)(listNames[marked].c_str()));
            else
              drawTurtle((char*)(listNames[marked].c_str()));
            } else if(confirmChoice==false){
              //enterMenu("Hovedmenu");
            }
    } else if (digitalRead(joystickZPin) == LOW && joystickDown)
      joystickDown = false;

    //Hvis joysticket holdes nede i lang tid skal den markerede ændres
    unsigned long startTime = millis();
    while (analogRead(joystickYPin) == 0 || analogRead(joystickYPin) > 4000) {
      if (millis() > startTime + joystickMoveInterval){

        if(confirmChoice==false){
            if(analogRead(joystickYPin)==0&&digitalRead(joystickZPin) == LOW){
              confirmChoice=true;
            }else if(analogRead(joystickYPin) != 0&&digitalRead(joystickZPin) == LOW){
              confirmChoice=true;
              }
        }else if(confirmChoice==true){
            if(analogRead(joystickYPin)==0&&digitalRead(joystickZPin) == LOW){
              confirmChoice=false;
            }else if(analogRead(joystickYPin) != 0&&digitalRead(joystickZPin) == LOW){
              confirmChoice=false;
        }}
       
        displayConfirm();
        break;
      }
    }*/
   }

}
