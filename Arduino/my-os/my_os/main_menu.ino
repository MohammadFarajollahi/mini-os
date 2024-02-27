

void main_menu_input() {
  touch();

  // if (first_start == 0) {
  //   first_start = 1;
  //   tft.fillScreen(TFT_BLACK);
  //   drawSdJpeg("/main_menu.jpg", 0, 0);
  // }

  if (x_t > 30 && x_t < 110 && y_t > 10 && y_t < 100) {  // terminal
    digitalWrite(buzzer, HIGH);
    delay(20);
    digitalWrite(buzzer, LOW);
    tft.setTextFont(2);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(1);
    first_show_lcd_config = 1;
    tft.fillScreen(TFT_WHITE);
    terminal = 1;
    tft.fillScreen(TFT_WHITE);
    drawSdJpeg("/terminal.jpg", 0, 0);
    x_t = 0;
    y_t = 0;
    main_menu = 0;
  }



  /////////
}