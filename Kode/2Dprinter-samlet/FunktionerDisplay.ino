// Funktioner til at tegne de forskelige skærme

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
   // Stop further decoding as image is running off bottom of screen
  if (y >= tft.height()) return 0;

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

void displayConfirm() {
  //Laver hele skærmen sort
  tft.fillScreen(TFT_BLACK);

  //De næste par linjer laver topdelen af displayet, hvor den skriver om man vil forsætte
  tft.setTextColor(TFT_BLACK, TFT_ORANGE);
  tft.setFreeFont(&DejaVu_Serif_16);
  tft.fillRect(0, 0, 320, 60, TFT_ORANGE);
  tft.drawString("Vil du forsaette med at printe:", 10, 5);
  tft.drawString(selectedFile, 10, 21);


  //Laver firekanten til true
  tft.fillRect(60, 80, 200, 50, TFT_ORANGE);
  //Skriver "ja" i fed af hængig om man har valgt den, starter med at ændre fonten
  tft.setFreeFont(confirmChoice == true ? &DejaVu_Serif_Bold_16 : &DejaVu_Serif_16);
  tft.drawString("Ja",150,95);

  //Laver firekanten til false
  tft.fillRect(60, 180, 200, 50, TFT_ORANGE);
  //Skriver "nej" i fed af hængig om man har valgt den, starter med at ændre fonten
  tft.setFreeFont(confirmChoice == false ? &DejaVu_Serif_Bold_16 : &DejaVu_Serif_16);
  tft.drawString("Nej",150,195);
  

  //LAVER MINION HER


  
}

void displayProgress(float progress) {
  
}
