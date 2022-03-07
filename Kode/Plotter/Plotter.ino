#include <SD.h>
#include <SPI.h>

//Standard A4 paper size
#define A4width 297
#define A4height 210

//Standard A3 paper size
#define A3width 420
#define A3height 297

//Pins for steppermotors
#define xStepPin 30
#define xDirPin 31

#define yStepPin 30
#define yDirPin 31

//Pins for stopping buttons
#define xStopButtonPin 30
#define yStopButtonPin 31

const int stepsPerRevolution = 200;

//All distances are in millimeters
const int stepsPerMillimeter = 1;

//The horizontal and vertical seperation of the dots when printing an image
const float printDotDistance = 4;

// Vaiables for the current position
float posX;
float posY;

//Pen state variable
bool penIsDown; 

void resetPos() {
  penUp();
  // Move pen to (0,0)
  while (!digitalRead(xStopButtonPin)) {
    ;
  }
  while (!digitalRead(yStopButtonPin)) {
    ;
  }
  posY = 0;
  posX = 0;
}

void penUp() {
  if (penDown) {
    // Move pen up
    penIsDown = false;
  }
}

void penDown() {
  if (!penDown) {
    // Move pen down
    penIsDown = true;
  }
}

void goToCoords(float x, float y) {
  // Move pen to coordinates
  posX = x;
  posY = y;
}

void printArray(int rows, int cols, int image[]) {
  //resetPos();
  for (int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      goToCoords(i*printDotDistance,j*printDotDistance);
      if (image[i*cols + j]) {
        Serial.print("□");
        penDown();
        penUp();
        digitalWrite(xDirPin, HIGH);
      } else {
        Serial.print("■");
        digitalWrite(xDirPin, LOW);
      }
      for (int k = 0; k < stepsPerRevolution; k++) {
        digitalWrite(xStepPin, HIGH);
        delayMicroseconds(700);
        digitalWrite(xStepPin, LOW);
        delayMicroseconds(700);  
      }
    }
    Serial.println();
  } 
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

}
