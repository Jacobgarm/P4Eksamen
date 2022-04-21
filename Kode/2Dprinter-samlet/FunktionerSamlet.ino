//Printer movement functions

void resetPos() {
  penUp();
  digitalWrite(xDirPin, !xPosDir);
  digitalWrite(yDirPin, !yPosDir);
  while (!digitalRead(xBackStopPin) && !digitalRead(yBackStopPin)) {
      if (!digitalRead(xBackStopPin))
        digitalWrite(xStepPin, HIGH);
      if (!digitalRead(yBackStopPin))
        digitalWrite(yStepPin, HIGH);
      delay(700);
      if (!digitalRead(xBackStopPin))
        digitalWrite(xStepPin, LOW);
      if (!digitalRead(yBackStopPin))
        digitalWrite(yStepPin, LOW);
      delay(700);
  }
  penXPos = 0;
  penYPos = 0;
}

void penUp() {
  if (penIsDown) {
    // Move pen up
    op(180,100);
    penIsDown = false;
  }
}

void penDown() {
  if (!penIsDown) {
    // Move pen down
    ned(0,100);
    penIsDown = true;
  }
}

void calibratePen() {}

void moveCoords(const float xLen, const float yLen) {
  if (xLen == 0 && yLen == 0)
    return;
  // Set DIR-pins alt efter om det er positiv eller negativ retning
  digitalWrite(xDirPin, xLen > 0 ? xPosDir : !xPosDir);
  digitalWrite(yDirPin, yLen > 0 ? yPosDir : !yPosDir);

  // Beregn antal steps der skal tages
  const int xSteps = int(abs(xLen) * stepsPerMM);
  const int ySteps = int(abs(yLen) * stepsPerMM);
  
  int xRemaining = xSteps;
  int yRemaining = ySteps;
  Serial.print(xSteps);
  Serial.print(' ');
  Serial.print(ySteps);
  // Den samlede mængde tid er bestemt af den akse der skal flytte sig længest
  const int totalTime = max(xSteps, ySteps) * 1400;
  
  // Intervallet mellem hver skift af STEP-signalet beregnes ud fra den totale tid delt med antallet af skridt
  // Denne metode sikrer at det bliver en lige linje.
  const unsigned long xInterval = xSteps == 0 ? 0 : totalTime / xSteps / 2;
  const unsigned long yInterval = ySteps == 0 ? 0 : totalTime / ySteps / 2;
  Serial.print(xInterval);
  Serial.print(' ');
  Serial.print(yInterval);
  unsigned long xTimer = 0;
  unsigned long yTimer = 0;
  
  int xState = HIGH;
  int yState = HIGH;
  digitalWrite(xStepPin,xState);
  digitalWrite(yStepPin,yState);

  // Loop indtil begge akser ikke mangler flere steps
  while (xRemaining != 0 || yRemaining != 0) {
    Serial.print(xState);
    Serial.print(' ');
    Serial.print(yRemaining);
    // Hvis der er steps tilbage på en akse, og den forløbne tid er over intervallet, skiftes STEP-pinnens tilstand.
    if (xRemaining && micros() > xTimer + xInterval) {
      xState = !xState;
      digitalWrite(xStepPin,xState);
      xTimer = micros();
      //Kun hele steps tælles, så antallet af resterende steps sænkes kun hvis pinnen går fra LOW til HIGH
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
  penXPos += xLen;
  penYPos += yLen;
  Serial.print(xSteps);
  Serial.print(' ');
  Serial.print(ySteps);
}

void goToCoords(int x, int y) {
  moveCoords(x - penXPos, y - penYPos);  
}

void moveDir(const float len, float dir) {
  //Lav dir til radianer
  dir = dir * PI / 180;
  
  //Distancer beregnes som kateter i en retvinklet trekant
  float xLen = len * cos(dir);
  float yLen = len * sin(dir);

  moveCoords(xLen, yLen);
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

// Kontrolfunktioner

void setNamesToMain() {
  //Sættter alle navne i listen til de forskellige valgmuligheder på hovedmenuen
  for (int i = 0; i < 100; i++)
    listNames [i] = mainMenuNames[i];
}

void enterMenu(String menuName) {
  screenName = menuName;
  if (menuName == "Print fra SD-kort") {
    //Hvis denne valgmulighed er valgt, hentes listen over filer på SD-kortet, som sættes til listen over valgmuligheder
    File root = SD.open("/");

    //Den øverste mulighed er en tilbageknap
    listNames[0] = "Tilbage";
    for (int i = 1; i < 99; i++) {
      File file = root.openNextFile();
      //Hvis der ikke er lere filer, stoppes loopet
      if (!file)
        continue;
      listNames[i] = file.name();
    }
  } else if (menuName == "Hovedmenu") {
    setNamesToMain();
    
  }
  marked = 0;
}

void selectFile(String fileName) {
  screenName = "Confirm";
  confirmChoice = false;
}
