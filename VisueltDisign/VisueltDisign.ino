#include <TFT_eSPI.h>
#include <SPI.h>
#include "FontIkkeFed.h"
#include "FontFed.h"

TFT_eSPI tft = TFT_eSPI();


//Variabler
  //Joystick ting
  int JoystickTimer = 0;
  int JoyStickXPin=33;
  //Tæller hvilken der er markederet
  int Marked = 1;
  String Navne[] = {"Printer til start", "Print fra SD-kort", "Print med joystick", "Sluk for skærm", ""};

void setup() {
  Serial.begin(9600);
  //Starter for skærmen, samt sætter den til sort
  tft.init();
  tft.fillScreen(TFT_BLACK);

  //Joystickpinsene
  pinMode(JoyStickXPin, INPUT);
  pinMode(35, INPUT);

  //Start skærm
  
  StartSkarm(Navne, Marked,"Main");
}

void loop() {
  while (analogRead(JoyStickXPin) == 0||analogRead(JoyStickXPin)==4095) {
    if (JoystickTimer == 50) {
      if(Navne[Marked+1]!=""){
      Marked++;
        }
      StartSkarm(Navne, Marked,"Main");
      JoystickTimer = 0;
    }else if(JoystickTimer==-50){
      if(Marked!=0){
      Marked--;}
      StartSkarm(Navne,Marked,"Main");
      JoystickTimer=0;
    }
    JoystickTimer=0;
    delay(10);
    JoystickTimer=JoystickTimer+(analogRead(JoyStickXPin) == 0 ? 1 : -1);
  }
}



void StartSkarm(String Navne[], int Marked, String Titel) {
  tft.fillScreen(TFT_BLACK);

  tft.setFreeFont(&Lato_Heavy_21);
  tft.fillRect(0,0,320,30,TFT_ORANGE);
  tft.fillRect(0,30,320,5,TFT_BLACK);
  tft.drawString(Titel,21,5);
  
  for (int i = 0; Navne[i] != ""; i++) {
    int I = i * 35+35;

    tft.fillRect(0, I, 320, 10, TFT_ORANGE);

    tft.setFreeFont(i == Marked ? &Lato_Heavy_21 : &Lato_Heavy_20);

    if (Marked == i) {
      tft.fillCircle(10, I + 18, 3, TFT_WHITE);
    }
    tft.drawString(Navne[i], 21, I + 11);
  }
}
