

void sd_start(){
    //*******sd card*******
  Serial.println("check sd card");
   SD_SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  if (!SD.begin(SD_CS, SD_SPI, 40000000))
  {
    Serial.println("Card Mount Failed");
    //return 1;
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
}