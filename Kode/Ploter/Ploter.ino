#include <Stepper.h>

const int stepsPerRevolution = 100;

Stepper stepmotor(stepsPerRevolution, 8, 9, 10, 11);

const int stepsPerMillimeter = 1;

//All sizes are in millimeters

//Standard A4 paper size
const float width = 297;
const float height = 210;

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

void printArray(const bool image[][], int rows, int cols) {
  resetPos();
  for (int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      goToCoords(i*printDotDistance,j*printDotDistance);
      if (image[i][j]) {
        penDown();
        penUp();
      }
    }
  } 
}

void setup() {
  // put your setup code here, to run once:
  resetPos();
  bool[3][3] img = {{0,1,0},{1,1,1},{0,1,0}};
  printArray(img, 3, 3);
}

void loop() {
  // put your main code here, to run repeatedly:

}
