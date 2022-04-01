#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <JPEGDecoder.h>
#include "FontIkkeFed.h"
#include "FontFed.h"

TFT_eSPI tft = TFT_eSPI();

//Variabler

const int tftChipSelectPin = 15;
const int SDChipSelectPin = 15;

//Joystick ting
int JoystickTicker = 0;
const int JoyStickXPin = 33;
const int JoyStickZPin = 26;
int JoystickTimerVardi = 35;
//Tæller hvilken der er markederet
int Marked = 0;
String Navne[100] = {"Printer til start", "Print fra SD-kort", "Print med joystick", "Sluk for skaerm"};
String Titel = "Main";

void setup() {
  Serial.begin(9600);

  // Begge CS pins HIGH så de ikke begge kan kommunikeres med
  digitalWrite(15, tftChipSelectPin); // TFT screen chip select
  digitalWrite( 5, SDChipSelectPin); // SD chip select
  
  //Starter for skærmen, samt sætter den til sort
  tft.init();
  tft.fillScreen(TFT_BLACK);

  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  
  //Joystickpinsene
  pinMode(JoyStickXPin, INPUT);
  pinMode(JoyStickZPin, INPUT_PULLUP);

  //Start skærm
  TegnSkarm();
}

int lastUpdated = 0;

void loop(){
  //Laver start opsætning
  Marked = StyringAfSkarm();
  Serial.print("Z: ");
  Serial.println(digitalRead(JoyStickZPin));
  /
  // Minion animation
  if (Titel == "Main" && lastUpdated +100 < millis()) {
    lastUpdated = millis();
    int state = millis() / 101;
    state = state % 3 +1;
    if (state == 1)
      drawSdJpeg("/Minion1.jpg", 127, 300);
    if (state == 2)
      drawSdJpeg("/Minion2.jpg", 127, 300);
    if (state == 3)
      drawSdJpeg("/Minion3.jpg", 127, 300);
  }
}


//Denne method er til at skrive styrings muligheder på skærmen
int StyringAfSkarm() {
  //Laver et while loop, som virker, hvis man har taget Joysticket helt hen i en retning
  if (digitalRead(JoyStickZPin) == LOW) {
    enterMenu(Navne[Marked]);  
  }
  while (analogRead(JoyStickXPin) == 0 || analogRead(JoyStickXPin) == 4095) {
    //
    if (JoystickTicker == JoystickTimerVardi) {
      if (Navne[Marked + 1] != "") {
        Marked++;
      }
      TegnSkarm();
      JoystickTicker = 0;
    }
    else if (JoystickTicker == -JoystickTimerVardi) {
      if (Marked != 0) {
        Marked--;
      }
      TegnSkarm();
      JoystickTicker = 0;
    }
    delay(10);
    JoystickTicker = JoystickTicker + (analogRead(JoyStickXPin) == 0 ? 1 : -1);
  }
  JoystickTicker = 0;
  return Marked;

}

int enterMenu(String menu) {
  if (menu == "Print fra SD-kort") {
    File root = SD.open("/");
    Navne[0] = "Tilbage";
    for (int i = 1; i < 99; i++) {
      File file = root.openNextFile();
      if (!file)
        continue;
      Navne[i] = file.name();
    }
    Titel = "SD-kort: Vaelg fil";
    Marked = 0;
    JoystickTimerVardi = 20;
    
  } else if (menu == "Tilbage") {
      
  }
  TegnSkarm();
}

//Denne method er til at skrive Valgmulighederne på skærmen
void TegnSkarm() {
  //Laver hele skærmen sort
  tft.fillScreen(TFT_BLACK);

  //De næste par linjer laver topdelen af displayet, hvor den skriver tiltelen
  tft.setTextColor(TFT_BLACK, TFT_ORANGE);
  tft.setFreeFont(&Lato_Heavy_21);
  tft.fillRect(0, 0, 320, 30, TFT_ORANGE);
  tft.fillRect(0, 30, 320, 5, TFT_BLACK);
  tft.drawString(Titel, 21, 5);

  //Sætter teksten tilbage til normalt
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  int first = 0;
  if (Marked > 9)
    first = Marked - 9;
  
  //Laver et loop, som kører alle mulige valg igennem
  for (int i = 0; Navne[i+first] != ""; i++) {
    //Starter med at finde ud af hvor henne den skal tegne på skærmen
    int I = i * 35 + 35;

    //Laver et rektankel over teksten
    tft.fillRect(0, I, 320, 10, TFT_ORANGE);

    //Ændre fonten afhængig af om det er den marked, eller ikke er. HIvs det er så bliver den fed
    tft.setFreeFont(i+first == Marked ? &Lato_Heavy_21 : &Lato_Heavy_20);

    //Hvis det også er den markedet, så lavers der også en cirkel ud foran
    if (Marked == i+first) {
      tft.fillCircle(10, I + 18, 3, TFT_WHITE);
    }
    //Skriver nu hvad valgmuligheden hedder
    tft.drawString(String(i+first+1) + (i+first+1 < 10 ? " " : "") + Navne[i+first], 21, I + 11);

    //Dette loop kører igennem til at der ikke er flere valgmuligheder i arrayet
  }
}

void drawSdJpeg(const char *filename, int xpos, int ypos) {

  // Open the named file (the Jpeg decoder library will close it)
  File jpegFile = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
 
  if ( !jpegFile ) {
    Serial.print("ERROR: File \""); Serial.print(filename); Serial.println ("\" not found!");
    return;
  }

  Serial.println("===========================");
  Serial.print("Drawing file: "); Serial.println(filename);
  Serial.println("===========================");

  // Use one of the following methods to initialise the decoder:
  bool decoded = JpegDec.decodeSdFile(jpegFile);  // Pass the SD file handle to the decoder,
  //bool decoded = JpegDec.decodeSdFile(filename);  // or pass the filename (String or character array)

  if (decoded) {
    // print information about the image to the serial port
    //jpegInfo();
    // render the image onto the screen at given coordinates
    jpegRender(xpos, ypos);
  }
  else {
    Serial.println("Jpeg file format not supported!");
  }
}

//####################################################################################################
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//####################################################################################################
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
void jpegRender(int xpos, int ypos) {

  //jpegInfo(); // Print information from the JPEG file (could comment this line out)

  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;

  bool swapBytes = tft.getSwapBytes();
  tft.setSwapBytes(true);
  
  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  uint32_t min_w = jpg_min(mcu_w, max_x % mcu_w);
  uint32_t min_h = jpg_min(mcu_h, max_y % mcu_h);

  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;

  // record the current time so we can measure how long it takes to draw an image
  uint32_t drawTime = millis();

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

  // Fetch data from the file, decode and display
  while (JpegDec.read()) {    // While there is more data in the file
    pImg = JpegDec.pImage ;   // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

    // Calculate coordinates of top left corner of current MCU
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    // copy pixels into a contiguous block
    if (win_w != mcu_w)
    {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++)
      {
        p += mcu_w;
        for (int w = 0; w < win_w; w++)
        {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }

    // calculate how many pixels must be drawn
    uint32_t mcu_pixels = win_w * win_h;

    // draw image MCU block only if it will fit on the screen
    if (( mcu_x + win_w ) <= tft.width() && ( mcu_y + win_h ) <= tft.height())
      tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
    else if ( (mcu_y + win_h) >= tft.height())
      JpegDec.abort(); // Image has run off bottom of screen so abort decoding
  }

  tft.setSwapBytes(swapBytes);
}
