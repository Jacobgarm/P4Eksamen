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

void goToCoords(float x, float y) {
  // Move pen to coordinates in mm
  if (x < posX)
    digitalWrite(xDirPin, LOW);
  else
    digitalWrite(xDirPin, HIGH);
  if (y < posY)
    digitalWrite(yDirPin, LOW);
  else
    digitalWrite(yDirPin, HIGH);
  int xSteps = abs(x - posX) * stepsPerMillimeter;
  int ySteps = abs(y - posY) * stepsPerMillimeter;
  while (xSteps > 0 && ySteps > 0) {
    if (xSteps > 0)
      digitalWrite(xStepPin, HIGH);
    if (ySteps > 0)
      digitalWrite(yStepPin, HIGH);
    delayMicroseconds(700);
    if (ySteps > 0) {
      digitalWrite(yStepPin, LOW);
      xSteps--;
    }
    if (ySteps > 0) {
      digitalWrite(yStepPin, LOW);
      ySteps--;
    }
    delayMicroseconds(700);
  }

  posX = x;
  posY = y;
}

void printArray(int rows, int cols, int image[]) {
  //resetPos();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      goToCoords(i * printDotDistance, j * printDotDistance);
      if (image[i * cols + j]) {
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
