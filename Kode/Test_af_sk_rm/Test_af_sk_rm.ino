#include <TFT_eSPI.h>
#include <SPI.h>
#include "dejavuserif.h"
#include "dejavuserifbold.h"

TFT_eSPI tft=TFT_eSPI();

String screenName = "Hovedmenu";
String mainMenuNames[100] = {"Printer til start", "Print fra SD-kort", "Print med joystick", "Kalibrer og reset"};
String listNames[100] = mainMenuNames;
int marked = 0;

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
  tft.drawString("filNavn", 10, 21);


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


int prikNummer=1;
int procentLoad=0;

void displayLoading() {
  //Laver hele skærmen sort
  tft.fillScreen(TFT_BLACK);

  //Ændre tekst udsene
  tft.setFreeFont(&DejaVu_Serif_Bold_16);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  //Skriver at den printer og den skifter med forskellige prikker, samt skriver hvor mange procent
  //hvor den kører på et switch som den bare køre igennem igen og igen
  switch(prikNummer){
    case 1:
    tft.drawString("Printer . "+String(procentLoad)+"%",60,80);
    prikNummer++;
    break;
    case 2:
    tft.drawString("Printer .. "+String(procentLoad)+"%",60,80);
    prikNummer++;
    break;
    case 3:
    tft.drawString("Printer ... "+String(procentLoad)+"%",60,80);
    prikNummer=1;
    break;
    }

  //Laver en firekant, som ikke er indfyldt
  tft.drawRect(61,100,202,20,TFT_WHITE);
  //Laver nu en firekant som fylder den anden firekant op ligeså stille, afhængig af dens procent
  tft.fillRect(60,100,procentLoad*2,20,TFT_WHITE);
  
  
  //LAVER MINION HER


  
}

void setup() {
  tft.setRotation(2);
  // put your setup code here, to run once:
  tft.init();
  tft.fillScreen(TFT_RED);
  //displayMenu();
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("k");
  displayLoading();
  procentLoad++;
  delay(1000);

}
