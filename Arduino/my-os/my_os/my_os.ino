
//***************************************wifi********************************
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "F3";
const char* password = "rakhsh70";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://dgcart.ir";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
//*****************************8******wifi********************************

#include "EEPROM.h"
#define EEPROM_SIZE 256
#include "Arduino.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <JPEGDecoder.h>
//****touch*****
#define CALIBRATION_FILE "/TouchCalData3"
#define REPEAT_CAL false
bool SwitchOn = false;

// Comment out to stop drawing black spots
#define BLACK_SPOT
// Switch position and size
#define FRAME_X 100
#define FRAME_Y 64
#define FRAME_W 120
#define FRAME_H 50
// Red zone size
#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W / 2)
#define REDBUTTON_H FRAME_H
// Green zone size
#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y

#define GREENBUTTON_W (FRAME_W / 2)
#define GREENBUTTON_H FRAME_H

uint16_t x_t, y_t;  // touch
int touch_change;

//***********software Serial********
HardwareSerial hwSerial(1);

#define minimum(a, b) (((a) < (b)) ? (a) : (b))
//#include "bitmap.h"
//#include "jpeg1.h"

//******pins_config*******
int buzzer = 17;
int lcd_back = 32;
int sd_state;
int uart_to_lcd;

//******main_menu******
int first_start;
int main_menu;
//wifi site
int login_site = 0;
//terminal
int terminal;
//main sreen
 int main_screen;


void setup() {
  Serial.begin(115200);
  Serial.println("start...");
  //***************eeprom********************
  EEPROM.begin(EEPROM_SIZE);
  //  step_count = 1;
  //  speed_count = 500;
  //  EEPROM.writeFloat(0, step_count);
  //  delay(50);
  //  EEPROM.commit();
  //  delay(50);
  //  EEPROM.writeFloat(10, speed_count);
  //  delay(50);
  //  EEPROM.commit();
  //  delay(50);
  //resume_mode = EEPROM.readFloat(0);
  //line_number = EEPROM.readFloat(20);

  //**********port config*********
  digitalWrite(22, HIGH);  // Touch controller chip select (if used)
  digitalWrite(15, HIGH);  // TFT screen chip select
  digitalWrite(5, HIGH);   // SD card chips select, must use GPIO 5 (ESP32 SS)
  pinMode(buzzer, OUTPUT);
  pinMode(lcd_back, OUTPUT);
  digitalWrite(lcd_back, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);


//////////software serial*************
hwSerial.begin(115200, SERIAL_8N1, 33, 32);  //(rx,tx)

  //****lcd start***
  tft.begin();

  //*******sd card*******
  Serial.println("check sd card");
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    sd_state = 0;
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    sd_state = 0;
    return;
  }
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
    sd_state = 1;
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
    sd_state = 1;
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
    sd_state = 1;
  } else {
    Serial.println("UNKNOWN");
    sd_state = 1;
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.println("initialisation done.");

  tft.setRotation(3);  // portrait
  tft.fillScreen(TFT_BLACK);

  //lcd config
  tft.init();
  tft.setRotation(1);  // portrait

  //**************touch***********
  // SPIFFS.remove(CALIBRATION_FILE);
  // SPIFFS.format();
  // SPIFFS.begin();
  // touch_calibrate();

//***************sd card informatio for first start****************
  // show_lcd("booting system...");
  // if (sd_state == 1) {
  //   show_lcd("sd card insert");
  //   //    String ss = cardSize + "mb";
  //   //    show_lcd(ss);
  //   show_lcd("initialisation done.");
  //   show_lcd("list all data in sd card");
  //   //listDir(SD, "/files", 0);
  // }
  // if (sd_state == 0) {
  //   show_lcd("sd card failed.");
  //   show_lcd("insert sd card to boot the system...");
  // }



  // wifi_connect();
  main_menu = 0;
  main_screen = 1;
   tft.fillScreen(TFT_BLACK);
    drawSdJpeg("/BACKGROUND.jpg", 0, 0);
}

void loop() {
  
  if(main_screen == 1)main_screen_input();
  if(main_menu == 1)main_menu_input();
  if(terminal == 1) terminal_usb();
  // if(login_site == 1)wifi_login();
  //send_server();
  //server_read();
}
