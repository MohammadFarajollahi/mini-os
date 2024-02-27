
void touch(){

    if (tft.getTouch(&x_t, &y_t)) {
    touch_change = 1;
    tft.fillRoundRect(0, 299, 80, 15, 5, TFT_WHITE);
    tft.setCursor(1, 300);
    String s1 = "x:" + String(x_t) + "  y:" + String(y_t);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.println(s1);

    
    }
}