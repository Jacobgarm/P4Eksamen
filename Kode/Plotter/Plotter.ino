#include <SD.h>
#include <SPI.h>
//#include <Servo.h>

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

//Pins for stopping buttons
#define xStopButtonPin 30
#define yStopButtonPin 31

const int stepsPerRevolution = 200;

//All distances are in millimeters
const int stepsPerMillimeter = 1;

//The horizontal and vertical seperation of the dots when printing an image in mm
const float printDotDistance = 4;

// Vaiables for the current position
float posX;
float posY;

//Pen state variable
bool penIsDown; 

void resetPos() {
  penUp();
  // Move pen to (0,0)
  return;
  while (!digitalRead(xStopButtonPin)) {
    ;
  }
  while (!digitalRead(yStopButtonPin)) {
    ;
  }
  posY = 0;
  posX = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(xStepPin, OUTPUT);
  pinMode(yStepPin, OUTPUT);
  pinMode(xDirPin, OUTPUT);
  pinMode(yDirPin, OUTPUT);
  pinMode(xStopButtonPin, INPUT);
  pinMode(yStopButtonPin, INPUT);
  return;
  Serial.println("Starting sd");
  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }
  File image_file = SD.open("bytes.bwb");
  int width = image_file.read();
  int height = image_file.read();
  int len = width*height;
  int img[len];
  for (int i = 0; i< len; i++)
    img[i] = (int)image_file.read();
  //image_file.read(img, len);
  Serial.println("File read");
  Serial.println(width);
  Serial.println(height);
  //resetPos();
  printArray(width, height, img);
}

void loop() {
  // put your main code here, to run repeatedly:
  goToCoords(random(1,10),random(1,10));
}
