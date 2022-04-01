#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <JPEGDecoder.h>
#include "FontIkkeFed.h"
#include "FontFed.h"

#define sgn(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))

//Standard A4 paper size
#define A4width 297
#define A4height 210

//Standard A3 paper size
#define A3width 420
#define A3height 297

//Size values;
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
String mainMenuNames[100] = {"Printer til start", "Print fra SD-kort", "Print med joystick", "Kalibrer og reset", "Sluk for display"};
String listNames[100] = mainMenuNames;
int marked = 0;
String selectedFile;
double penXPos;
double penYPos;
bool penIsDown;
String filNavn;

//Start på funktioner------------------------------------------------------------------------------------------------------------------------

//Printer movement functions

void resetPos() {
  penUp();  
}

void penUp() {
  if (penIsDown) {
    // Move pen up
    penIsDown = false;
  }
}

void penDown() {
  if (!penIsDown) {
    // Move pen down
    penIsDown = true;
  }
}

void goToCoords(int x, int y) {}

void calibratePen() {}

void moveDir(const float len, const float dir) {
  float xLen = abs(len * cos(dir));
  float yLen = len * sin(dir);
  digitalWrite(xDirPin, cos(dir) > 0 ? xPosDir : !xPosDir);
  digitalWrite(yDirPin, sin(dir) > 0 ? yPosDir : !yPosDir); 
  int xSteps = (int)(xLen * stepsPerMM);
  int ySteps = (int)(yLen * stepsPerMM);
  int xRemaining = xSteps;
  int yRemaining = ySteps;
  int totalTime = max(xSteps, ySteps) * 1400;
  int xInterval = totalTime / xSteps / 2;
  int yInterval = totalTime / ySteps / 2;
  unsigned long xTimer = 0;
  unsigned long yTimer = 0;
  int xState = HIGH;
  int yState = HIGH;
  digitalWrite(xStepPin,xState);
  digitalWrite(yStepPin,yState);
  while (xRemaining || yRemaining) {
    if (xRemaining && micros() > xTimer + xInterval) {
      xState = !xState;
      digitalWrite(xStepPin,xState);
      yTimer = micros();
      if (xState == HIGH)
        xRemaining--;
    }
    if (yRemaining && micros() > yTimer + yInterval) {
      yState = !yState;
      digitalWrite(yStepPin,yState);
      yTimer = micros();
      if (yState == HIGH)
        yRemaining--;
    }
  }
}

void drawTurtle(const char* filePath) {
  File file = SD.open(filePath);
  String command = "";
  String value = "";
  bool readingCommand = true;
  float heading = 0;
  while (file.available()) {
    char c = file.read();
    if (c == '\n') {
      float v = value.toFloat();
      if (command == "move")
        moveDir(v, heading);
      else if(command == "left")
        heading += v;
      else if (command == "right")
        heading -= v;
      else if(command == "wait")
        delay(v);
      else if(command == "pendown")
        penDown();
      else if(command == "penup")
        penUp();
      else
        Serial.println("Unknown command: " + command);
      command = "";
      value = "";
      readingCommand = true;
    } else if (c == ' ') {
      readingCommand = false;
    } else if (readingCommand) {
      command = command + String(c);
    } else {
      value = value + String(c);
    }
  }
  file.close();
}

void printImage(const char* filePath) {
  File file = SD.open(filePath);
  int cols = file.read();
  int rows = file.read();
  int len = cols*rows;
  int img[len];
  for (int i = 0; i< len; i++)
    img[i] = (int)file.read();
  file.close();
  for (int i = 0; i < rows; i++) {
    bool even = i % 2 == 0;
    for(int j = even ? 0 : cols - 1; even ? (j < cols) : (j>=0) ; even ? (j++) : (j--)) {
      goToCoords(j*printDotDistance,i*printDotDistance);
      if (img[i*cols + j]) {
        Serial.print("□");
        penDown();
        penUp();
      } else {
        Serial.print("■");
      }
    }
    Serial.println();
  }
}

void joystickControl() {
  int pz = 0;
  int xDir = xPosDir;
  int yDir = yPosDir;
  digitalWrite(xDirPin, xDir);
  digitalWrite(yDirPin, yDir);
  unsigned long xTimer = 0;
  unsigned long yTimer = 0;
  int xState = HIGH;
  int yState = HIGH;
  digitalWrite(xStepPin,xState);
  digitalWrite(yStepPin,yState);
  while (true) {
    int jx = analogRead(joystickXPin) - joystickXMid;
    int jy = analogRead(joystickYPin) - joystickYMid;
    int jz = digitalRead(joystickZPin);
    if (jz != pz && jz == HIGH) {
      if (penIsDown)
        penUp();
      else
        penDown();  
    }
    if ((jx * jx + jy * jy) < joystickDeadzone)
      continue;
    if ((jx < 0 && xDir == xPosDir) || (jx > 0 && xDir != xPosDir)) {
      xDir = !xDir;
      digitalWrite(xDirPin, xDir);
    }
    if ((jy < 0 && yDir == yPosDir) || (jy > 0 && yDir != yPosDir)) {
      yDir = !yDir;
      digitalWrite(yDirPin, yDir);
    }
    int xInterval = (int)(-0.341796875 * abs(jx) + 1400);
    int yInterval = (int)(-0.341796875 * abs(jy) + 1400);
    if (micros() > xTimer + xInterval) {
      xState = !xState;
      digitalWrite(xStepPin,xState);
      yTimer = micros();
    }
    if (micros() > yTimer + yInterval) {
      yState = !yState;
      digitalWrite(yStepPin,yState);
      yTimer = micros();
    }
  }
}

// Funktioner til at tegne de forskelige skærme

void displayMenu() {
  //Laver hele skærmen sort
  tft.fillScreen(TFT_BLACK);

  //De næste par linjer laver topdelen af displayet, hvor den skriver tiltelen
  tft.setTextColor(TFT_BLACK, TFT_ORANGE);
  tft.setFreeFont(&Lato_Heavy_21);
  tft.fillRect(0, 0, 320, 30, TFT_ORANGE);
  tft.fillRect(0, 30, 320, 5, TFT_BLACK);
  tft.drawString(screenName, 21, 5);

  //Sætter teksten tilbage til normalt
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  int first = 0;
  if (marked > 9)
    first = marked - 9;
  
  //Laver et loop, som kører alle mulige valg igennem
  for (int i = 0; listNames[i+first] != ""; i++) {
    //Starter med at finde ud af hvor henne den skal tegne på skærmen
    int I = i * 35 + 35;

    //Laver et rektankel over teksten
    tft.fillRect(0, I, 320, 10, TFT_ORANGE);

    //Ændre fonten afhængig af om det er den marked, eller ikke er. HIvs det er så bliver den fed
    tft.setFreeFont(i+first == marked ? &Lato_Heavy_21 : &Lato_Heavy_20);

    //Hvis det også er den markedet, så lavers der også en cirkel ud foran
    if (marked == i+first) {
      tft.fillCircle(10, I + 18, 3, TFT_WHITE);
    }
    //Skriver nu hvad valgmuligheden hedder
    tft.drawString(String(i+first+1) + (i+first+1 < 10 ? " " : "") + listNames[i+first], 21, I + 11);

    //Dette loop kører igennem til at der ikke er flere valgmuligheder i arrayet
  }  
}

void displayConfirm(bool valg) {
  //Laver hele skærmen sort
  tft.fillScreen(TFT_BLACK);

  //De næste par linjer laver topdelen af displayet, hvor den skriver om man vil forsætte
  tft.setTextColor(TFT_BLACK, TFT_ORANGE);
  tft.setFreeFont(&Lato_Heavy_21);
  tft.fillRect(0, 0, 320, 30, TFT_ORANGE);
  //tft.fillRect(0, 30, 320, 5, TFT_BLACK);
  tft.drawString("Vil du forsaette med at printe "+filNavn, 10, 5);


  //Laver firekanten til true
  tft.fillRect(60, 50, 200, 50, TFT_ORANGE);
  //Skriver "ja" i fed af hængig om man har valgt den, starter med at ændre fonten
  tft.setFreeFont(valg == true ? &Lato_Heavy_21 : &Lato_Heavy_20);
  tft.drawString("Ja",150,65);

  //Laver firekanten til false
  tft.fillRect(60, 150, 200, 50, TFT_ORANGE);
  //Skriver "nej" i fed af hængig om man har valgt den, starter med at ændre fonten
  tft.setFreeFont(valg == false ? &Lato_Heavy_21 : &Lato_Heavy_20);
  tft.drawString("Nej",150,165);
  

  //LAVER MINION HER


  
}

void displayProgress(float progress) {
  
}
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

  //Start SD-kortet
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }

  displayMenu();
  
  drawTurtle("/test.turtle");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
