//Printer movement functions

void resetPos() {
  displayProgress(0);
  penUp();
  digitalWrite(xDirPin, !xPosDir);
  digitalWrite(yDirPin, !yPosDir);
  while (!digitalRead(xBackStopPin) || !digitalRead(yBackStopPin)) {
      if (!digitalRead(xBackStopPin))
        digitalWrite(xStepPin, HIGH);
      if (!digitalRead(yBackStopPin))
        digitalWrite(yStepPin, HIGH);
        
      delayMicroseconds(700);
      
      if (!digitalRead(xBackStopPin))
        digitalWrite(xStepPin, LOW);
      if (!digitalRead(yBackStopPin))
        digitalWrite(yStepPin, LOW);
        
      delayMicroseconds(700);
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
  
  // Den samlede mængde tid er bestemt af den akse der skal flytte sig længest
  const int totalTime = max(xSteps, ySteps) * 2000;
  
  // Intervallet mellem hver skift af STEP-signalet beregnes ud fra den totale tid delt med antallet af skridt
  // Denne metode sikrer at det bliver en lige linje.
  const unsigned long xInterval = xSteps == 0 ? 0 : totalTime / xSteps / 2;
  const unsigned long yInterval = ySteps == 0 ? 0 : totalTime / ySteps / 2;

  unsigned long xTimer = 0;
  unsigned long yTimer = 0;
  
  int xState = HIGH;
  int yState = HIGH;
  digitalWrite(xStepPin,xState);
  digitalWrite(yStepPin,yState);

  // Loop indtil begge akser ikke mangler flere steps
  while (xRemaining != 0 || yRemaining != 0) {
    //Hvis du vil havde den til at printe langsommere, og mere præcis, så behold serial.println under
    Serial.println(xRemaining);
    Serial.println(xRemaining);
    Serial.println(xRemaining);
    
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
      //Hvis der ikke er flere filer, stoppes loopet
      if (!file)
        break;
      listNames[i] = file.name();
    }
    marked=0;
    displayMenu();  
  
  } else if (menuName == "Hovedmenu") {
    setNamesToMain();
    displayMenu();
    
    
  } else if (menuName=="Printer til start"){
    //Kører resetpos koden
    resetPos();
    //Sætter den marked til 0, samt sætter de andre ting til normal menu igen
    marked=0;
    screenName="Hovedmenu";
    procentLoad=0;
    displayMenu();

  } else if (menuName=="Print med joystick"){
    //Sætter skærmen til at skrive med joystick
    tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(&DejaVu_Serif_Bold_16);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Du printer med joystick ",60,80);
    delay(1000);
    
    //Skriver med joystick
    joystickControl();

    //Gør klar til menu'en igen
    marked=2;
    delay(1000);
    screenName="Hovedmenu";
    displayMenu();
  }
}

void selectFile(String fileName) {
  screenName = "Confirm";
  selectedFile=fileName;
  confirmChoice = true;
  displayConfirm();
  delay(2000);
}
