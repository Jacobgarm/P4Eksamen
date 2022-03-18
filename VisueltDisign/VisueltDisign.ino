#include <TFT_eSPI.h>
#include <SPI.h>
#include "FontIkkeFed.h"
#include "FontFed.h"

TFT_eSPI tft=TFT_eSPI();

template< typename T, size_t N > size_t ArraySize (T (&) [N]){ return N; }

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  tft.init();
  
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  String Navne[]={"1.","2.","3.","4.",""};
  StartSkarm(Navne,3);
  delay(1000);
}

void StartSkarm(String Navne[],int Marked){
  for (int i=0;Navne[i]!="";i++){
    int I=i*27;

    tft.fillRect(0,I,320,5,TFT_ORANGE);

    tft.setFreeFont(i==Marked?&Lato_Heavy_21:&Lato_Heavy_20);
    tft.drawString(Navne[i],20,I+5);
    }
  }
