#include <TFT_eSPI.h>
#include <SPI.h>
#include "FontIkkeFed.h"
#include "FontFed.h"

TFT_eSPI tft = TFT_eSPI();


//Variabler
  //Joystick ting
  int Abe = 0;
  int JoyStickXPin=33;
  //Tæller hvilken der er markederet
  int Marked = 1;
  int LaengdeAfNavne=3;

void setup() {
  Serial.begin(9600);
  //Starter for skærmen, samt sætter den til sort
  tft.init();
  tft.fillScreen(TFT_BLACK);

  //Joystickpinsene
  pinMode(JoyStickXPin, INPUT);
  pinMode(35, INPUT);

  //Start skærm
  String Navne[] = {"Printer til start", "Print fra SD-kort", "Print med joystick", "4.", ""};
  StartSkarm(Navne, Marked);
}

void loop() {
  //
  String Navne[] = {"Printer til start", "Print fra SD-kort", "Print med joystick", "4.", ""};
  while (analogRead(JoyStickXPin) == 0||analogRead(JoyStickXPin)==4095) {
    if (Abe == 50) {
      if(Marked!=LaengdeAfNavne){
      Marked++;
        }
      StartSkarm(Navne, Marked);
      Abe = 0;
    }else if(Abe==-50){
      if(Marked!=0){
      Marked--;}
      StartSkarm(Navne,Marked);
      Abe=0;
    }
    delay(10);
    Abe=Abe+(analogRead(JoyStickXPin) == 0 ? 1 : -1);
  }
  Serial.println(analogRead(JoyStickXPin));
}

void StartSkarm(String Navne[], int Marked) {
  tft.fillScreen(TFT_BLACK);
  for (int i = 0; Navne[i] != ""; i++) {
    int I = i * 35;

    tft.fillRect(0, I, 320, 10, TFT_ORANGE);

    tft.setFreeFont(i == Marked ? &Lato_Heavy_21 : &Lato_Heavy_20);

    if (Marked == i) {
      tft.fillCircle(10, I + 18, 3, TFT_WHITE);
    }
    tft.drawString(Navne[i], 21, I + 11);
  }
}
