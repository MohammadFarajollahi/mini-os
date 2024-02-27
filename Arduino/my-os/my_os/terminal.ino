

void terminal_usb() {
  uart_to_lcd = 1;
  uart1();
  touch();
  if (x_t > 450 && x_t < 480 && y_t > 250 && y_t < 300 ) {  //EXIT terminal
    digitalWrite(buzzer, HIGH);
    delay(20);
    digitalWrite(buzzer, LOW);
    tft.setTextFont(2);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(1);
    first_show_lcd_config = 1;
    tft.fillScreen(TFT_WHITE);
    terminal = 0;
    tft.fillScreen(TFT_WHITE);
    drawSdJpeg("/main_menu.jpg", 0, 0);
    x_t = 0;
    y_t = 0;
    uart_to_lcd = 0;
    main_menu = 1;
    delay(500);
  }
}