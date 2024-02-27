#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "Parallel16_9486.h"
LGFX tft;
static LGFX_Sprite sprite(&tft);  // Instance of LGFX_Sprite when using sprites
#include "EEPROM.h"
#define EEPROM_SIZE 256
#include "Arduino.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <JPEGDecoder.h>
#define SPI_MOSI 11  //1
#define SPI_MISO 13
#define SPI_SCK 12
#define SD_CS 2  //2
SPIClass SD_SPI;
#define minimum(a, b) (((a) < (b)) ? (a) : (b))
// Count how many times the image is drawn for test purposes
uint32_t icount = 0;
//----------------------------------------------------------------------------------------------------


int sd_state;

//*************************New*********************


void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(tft.getRotation() ^ 3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(0, 5);
  tft.println("***Start Program***");
  sd_start();


  //drawSdJpeg("/BACKGROUND.jpg", 0, 0);
 /// tft.setColorDepth(24);
 tft.drawJpgFile(SD, "/1.jpg", 0, 0);
}

void loop() {
  
}
