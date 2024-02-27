String ReadString;

void uart1() {

  while (Serial.available() > 0) {
    ReadString = Serial.readStringUntil('\n');
    ReadString.trim();
    // Serial.println(ReadString);
    if (uart_to_lcd == 1) show_lcd(ReadString);
    uart_config();
  }
}


void uart_config() {
  if (ReadString == "uart on") {
    uart_to_lcd = 1;
    show_lcd("---uart lcd on---");
  }
  ///
  if (ReadString == "uart off") {
    uart_to_lcd = 0;
    Serial.println("---uart lcd off---");
  }
  ///
  if (ReadString == "scrol") {
    for (int i = 0; i <= 10; i++) {
      show_lcd(String(i));
    }
  }


  //***************************************wifi**************************
  if (ReadString == "login") {  
     login_site =1;    
  }

  ////
}