void printImage(const String filePath) {
  // Læs filen med billedet
  File file = SD.open(filePath);

  // De første to bytes indeholder antallet af kolonner og rækker
  int cols = file.read();
  int rows = file.read();
  int len = cols*rows;

  // Et array til pixels fyldes med resten af filens bytes
  int img[len];
  for (int i = 0; i< len; i++)
    img[i] = (int)file.read();
  file.close();
  int printed = 0;
  // For hver pixel, flyt til koordinaterne, og hvis positionen i arrayet er 1 laves en prik
  for (int i = 0; i < rows; i++) {

    // Ved hver anden række går den baglæns for at minimere distancen.
    bool even = i % 2 == 0;
    for(int j = even ? 0 : cols - 1; even ? (j < cols) : (j>=0) ; even ? (j++) : (j--)) {
      displayProgress(int(float(printed)/len * 100));
      goToCoords(j*printDotDistance,i*printDotDistance);
      if (img[i*cols + j]) {
        Serial.print("□");
        penDown();
        penUp();
      } else {
        Serial.print("■");
      }
      printed++;
    }
    Serial.println();
  }
}

void drawTurtle(const String filePath) {

  //Læs filen
  File file = SD.open(filePath);

  //Command indeholder den første del af linjen, der bestemmer hvilken funktion der skal udføres
  // Value er den tilhørende værdi.
  String command = "";
  String value = "";
  bool readingCommand = true;
  bool isComment = false;
  float heading = 0;

  unsigned long loopPos = 0;
  int loopCount = 0;
  while (file.available()) {
    
    //Læs filen en char ad gangen
    char c = file.read();
    Serial.print(c);

    //Hvis char er et linjeskift, så er kommandoen færdig og skal udføres
    if (c == '\n') {
      // Tom linje
      Serial.println(command);
      Serial.println(value);
      Serial.println(readingCommand);
      if (command == "")
        continue;
      command.toLowerCase();
      float v;
      if (value == "")
        v = 0;
      else
        v = value.toFloat();

      // move kommando flytter turtle fremad efter dens nuværende retning
      if (command == "move")
        moveDir(v, heading);

      // Drej turtle
      else if(command == "left")
        heading += v;
      else if (command == "right")
        heading -= v;
      else if (command == "setdir")
        heading = v;

      // Vent i v millisekunder
      else if(command == "wait")
        delay(v);

      // Flyt pennen op eller ned
      else if(command == "pendown")
        penDown();
      else if(command == "penup")
        penUp();

      // Start et loop der gentager efterfølgende kode v gange
      else if(command == "repeat") {
        loopPos = file.position();  
        loopCount = v;
      } 

      // Slut loopet. Hvis det ikke er udført v gange, så hop tilbage til starten af loopet
      else if (command == "endrepeat") {
        if (loopCount > 0) {
          loopCount--;
          file.seek(loopPos);  
        }
      }
      else
        Serial.println("Unknown command: " + command);
      command = "";
      value = "";
      readingCommand = true;
      isComment = false;
    } 
    // Hvis den nuværende linje er en kommentar, fortsæt
    else if (isComment)
      continue;

    // Et mellemrum adskiller kommandoen og værdien
    else if (c == 10)
      readingCommand = false;

    // Et hashtag indikerer starten af en kommentar
    else if (c == 35)
      isComment = true;

    // Ellers, tilføj charen til enten den nuværende kommando eller værdi
    else if (readingCommand)
      command = command + String(c);
    else
      value = value + String(c);
    
  }
  file.close();
}

void joystickControl() {
  int pz = 0;
  int xDir = xPosDir;
  int yDir = yPosDir;
  digitalWrite(xDirPin, xDir);
  digitalWrite(yDirPin, yDir);
  
  // Start begge timere ved nul
  unsigned long xTimer = 0;
  unsigned long yTimer = 0;

  // Start begge STEP-pins på HIGH
  int xState = HIGH;
  int yState = HIGH;
  digitalWrite(xStepPin,xState);
  digitalWrite(yStepPin,yState);
  
  while (true) {
    //Læs joystickværdier
    int jx = analogRead(joystickXPin) - joystickXMid;
    int jy = analogRead(joystickYPin) - joystickYMid;
    int jz = digitalRead(joystickZPin);
    Serial.println(jy);
    //Hvis joysticket er blevet trykket ned, toggle pennen
    if (jz != pz && jz == HIGH) {
      if (penIsDown)
        penUp();
      else
        penDown();  
    }

    // Hvis joysticket ikke er flyttet udenfor deadzone, gør intet
    if ((jx * jx + jy * jy) < joystickDeadzone)
      continue;

    // Hvis joysticket har ændret retning, skal steppermotoren vende
    if ((jx < 0 && xDir == xPosDir) || (jx > 0 && xDir != xPosDir)) {
      xDir = !xDir;
      digitalWrite(xDirPin, xDir);
    }
    if ((jy < 0 && yDir == yPosDir) || (jy > 0 && yDir != yPosDir)) {
      yDir = !yDir;
      digitalWrite(yDirPin, yDir);
    }

    //Beregn stepintervallet ud fra joystickets position, jo større værdi jo mindre interval
    int xInterval = -0.341796875 * abs(jx) + 1400;
    int yInterval = -0.341796875 * abs(jy) + 1400;

    // Hvis den forløbne tid er større end intervallet, step
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
