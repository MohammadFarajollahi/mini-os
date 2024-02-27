int lcd_row;
String lcd_ch[100];
int lcd_ch_count1;
int lcd_ch_count2;
int first_show_lcd_config;
String lcd_ch2[20];
int lcd_char2 = 0;

void show_lcd(String text) {

  //tft.fillRoundRect(148, 38, 155, 20, 5 , TFT_WHITE);
  // if (first_show_lcd_config == 0) {
  //   tft.setTextFont(2);
  //   tft.setTextColor(TFT_GREEN, TFT_BLACK);
  //   tft.setTextSize(1);
  //   first_show_lcd_config = 1;
  //   tft.fillScreen(TFT_BLACK);
  // }

  tft.setCursor(2, lcd_row);
  if (lcd_row < 280) lcd_row = lcd_row + 20;

  if (lcd_row >= 280) {
    lcd_row = 280;
    tft.fillRoundRect(0, 280, 400, 18, 5, TFT_WHITE);
  }

  lcd_ch[lcd_ch_count1] = text;  // daryaft matn vorodi az uart
  tft.println(lcd_ch[lcd_ch_count1]);
  lcd_ch_count1 += 1;


  if (lcd_ch_count1 > 15) {
    lcd_row = 0;
    for (int i = lcd_ch_count1 - 15; i <= lcd_ch_count1 - 1; i++) {

      tft.fillRoundRect(0, lcd_row - 1, 400, 18, 5, TFT_WHITE);
      tft.setCursor(2, lcd_row);
      lcd_row = lcd_row + 20;
      tft.println(lcd_ch[i]);
    }
    lcd_row = 280;
  }


  // //*********************show for help******************
  // for (int i = 0; i <= lcd_ch_count1; i++) {
  //   Serial.print(lcd_ch[lcd_ch_count1]);
  // }


  // Serial.print("number of row:");
  // Serial.println(String(lcd_ch_count1));
}
