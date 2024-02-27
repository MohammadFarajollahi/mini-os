
void main_screen_input() {
  touch();
  if (x_t > 0 && x_t < 100 && y_t > 250 && y_t < 300) {  //main menu bytton
    digitalWrite(buzzer, HIGH);
    delay(20);
    digitalWrite(buzzer, LOW);
    tft.fillScreen(TFT_BLACK);
    drawSdJpeg("/main_menu.jpg", 0, 0);
    x_t = 0;
    y_t = 0;
    main_menu = 1;
    main_screen = 0;
    delay(500);
  }
}