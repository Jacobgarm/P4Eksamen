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
  const int xSteps = (int)(abs(xLen) * stepsPerMM);
  const int ySteps = (int)(abs(yLen) * stepsPerMM);
  
  int xRemaining = xSteps;
  int yRemaining = ySteps;

  // Den samlede mængde tid er bestemt af den akse der skal flytte sig længest
  const int totalTime = max(xSteps, ySteps) * 1400;
  
  const int xInterval = xSteps == 0 ? 0 : totalTime / xSteps / 2;
  const int yInterval = ySteps == 0 ? 0 : totalTime / ySteps / 2;
  
  unsigned long xTimer = 0;
  unsigned long yTimer = 0;
  
  int xState = HIGH;
  int yState = HIGH;
  digitalWrite(xStepPin,xState);
  digitalWrite(yStepPin,yState);

  // Loop indtil begge akser ikke mangler flere steps
  while (xRemaining || yRemaining) {
    // Hvis der er steps tilbage på en akse, og den forløbne tid er over intervallet, skiftes STEP-pinnens tilstand.
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
  penXPos += xLen;
  penYPos += yLen;
}

void goToCoords(int x, int y) {
  moveCoords(x - penXPos, y - penYPos);  
}

void moveDir(const float len, float dir) {
  //Lav dir til radianer
  dir = dir * PI / 180;
  
  float xLen = len * cos(dir);
  float yLen = len * sin(dir);

  moveCoords(xLen, yLen);
}

void drawTurtle(const char* filePath) {

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

    //Hvis char er et linjeskift, så er kommandoen færdig og skal udføres
    if (c == '\n') {
      // Tom linje
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
    else if (c == ' ')
      readingCommand = false;

    // Et hashtag indikerer starten af en kommentar
    else if (c == '#')
      isComment = true;

    // Ellers, tilføj charen til enten den nuværende kommando eller værdi
    else if (readingCommand)
      command = command + String(c);
    else
      value = value + String(c);
    
  }
  file.close();
}

void printImage(const char* filePath) {
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

  // For hver pixel, flyt til koordinaterne, og hvis positionen i arrayet er 1 laves en prik
  for (int i = 0; i < rows; i++) {

    // Ved hver anden række går den baglæns for at minimere distancen.
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
    int xInterval = (int)(-0.341796875 * abs(jx) + 1400);
    int yInterval = (int)(-0.341796875 * abs(jy) + 1400);

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

// Funktioner til at tegne de forskelige skærme

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
   // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  return 1;
}

void displayMenu() {
  //Laver hele skærmen sort
  tft.fillScreen(TFT_BLACK);

  //De næste par linjer laver topdelen af displayet, hvor den skriver tiltelen
  tft.setTextColor(TFT_BLACK, TFT_ORANGE);
  tft.setFreeFont(&DejaVu_Serif_16);
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
    tft.setFreeFont(i+first == marked ? &DejaVu_Serif_Bold_16 : &DejaVu_Serif_16);

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
  tft.setFreeFont(&DejaVu_Serif_16);
  tft.fillRect(0, 0, 320, 60, TFT_ORANGE);
  tft.drawString("Vil du forsaette med at printe:", 10, 5);
  tft.drawString(filNavn, 10, 21);


  //Laver firekanten til true
  tft.fillRect(60, 80, 200, 50, TFT_ORANGE);
  //Skriver "ja" i fed af hængig om man har valgt den, starter med at ændre fonten
  tft.setFreeFont(valg == true ? &DejaVu_Serif_Bold_16 : &DejaVu_Serif_16);
  tft.drawString("Ja",150,95);

  //Laver firekanten til false
  tft.fillRect(60, 180, 200, 50, TFT_ORANGE);
  //Skriver "nej" i fed af hængig om man har valgt den, starter med at ændre fonten
  tft.setFreeFont(valg == false ? &DejaVu_Serif_Bold_16 : &DejaVu_Serif_16);
  tft.drawString("Nej",150,195);
  

  //LAVER MINION HER


  
}

void displayProgress(float progress) {
  
}
