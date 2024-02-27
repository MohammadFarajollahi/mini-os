


void test(){
tft.drawPixel(0, 0, 0xFFFF);    // White dot at coordinates 0, 0


  // A function to generate a color code is provided and can be used to specify
  // a color. As arguments specify red, green, and blue from 0 to 255, resp.
  // It is recommended to use color888 to prevent missing color information.
  tft.drawFastVLine(2, 0, 100, tft.color888(255,   0,   0));  // red
  tft.drawFastVLine(4, 0, 100, tft.color565(  0, 255,   0));  // green
  tft.drawFastVLine(6, 0, 100, tft.color332(  0,   0, 255));  // blue


  // If the color code generation function is not used, it will be as follows.
  // RGB888 24-bit specified uint32_t type
  // RGB565 16-bit specification uint16_t type, int32_t type
  // RGB332 Specify with 8 bits uint8_t type

  // If you use uint32_t type, it will be treated as 24-bit RGB888.
  // You can write in the order of red, green, and blue with 2 hexadecimal digits.
  // Use a uint32_t type variable, add a U at the end, or cast it to a uint32_t.
  uint32_t red = 0xFF0000;
  tft.drawFastHLine(0, 2, 100, red);            // horiz. line in red
  tft.drawFastHLine(0, 4, 100, 0x00FF00U);      // horiz. line in green
  tft.drawFastHLine(0, 6, 100, (uint32_t)0xFF); // horiz. line in blue

  // If you use uint16_t type and int32_t type, it will be treated as 16 bits
  // of RGB565. This method is used because it is treated as int32_t type unless
  // it is written in a special way. (This is done for compatibility with
  // AdafruitGFX and TFT_eSPI.)
  uint16_t green = 0x07E0;
  tft.drawRect(10, 10, 50, 50, 0xF800);         // red
  tft.drawRect(12, 12, 50, 50, green);          // green
  tft.drawRect(14, 14, 50, 50, (uint16_t)0x1F); // blue


  // If you use int8_t or uint8_t type, it will be treated as 8 bits, RGB332.
  uint8_t blue = 0x03;
  tft.fillRect(20, 20, 20, 20, (uint8_t)0xE0);  // red
  tft.fillRect(30, 30, 20, 20, (uint8_t)0x1C);  // green
  tft.fillRect(40, 40, 20, 20, blue);           // blue


  // The color of the drawing function argument can be omitted.
  // If omitted, the color set by the setColor function or the last used color
  // will be used as the foreground color. If you draw repeatedly in the same
  // color, omitting it will render slightly faster.
  tft.setColor(0xFF0000U);                        // red as drawing color
  tft.fillCircle ( 40, 80, 20    );               // fill circle in red
  tft.fillEllipse( 80, 40, 10, 20);               // fill arc in red
  tft.fillArc    ( 80, 80, 20, 10, 0, 90);        // fill ellipse in red
  tft.fillTriangle(80, 80, 60, 80, 80, 60);       // fill triangle red
  tft.setColor(0x0000FFU);                        // blue as drawing color
  tft.drawCircle ( 40, 80, 20    );               // circle outline in blue
  tft.drawEllipse( 80, 40, 10, 20);               // ellipse outline in blue
  tft.drawArc    ( 80, 80, 20, 10, 0, 90);        // arc outline in blue
  tft.drawTriangle(60, 80, 80, 80, 80, 60);       // triable outline in blue
  tft.setColor(0x00FF00U);                        // green as drawing color
  tft.drawBezier( 60, 80, 80, 80, 80, 60);        // green 3-point Bezier curve
  tft.drawBezier( 60, 80, 80, 20, 20, 80, 80, 60);// green 4-point Bezier curve

  // Using DrawGradientLine you cannot omit the color specification
  tft.drawGradientLine( 0, 80, 80, 0, 0xFF0000U, 0x0000FFU);// Red to blue

  delay(1000);

  // You can fill the entire screen with clear or fillScreen.
  // fillScreen is the same as specifying the entire screen of fillRect, and
  // the color specification is treated as the drawing color.
  tft.fillScreen(0xFFFFFFu);   // Fill with white
  tft.setColor(0x00FF00u);     // Green as the drawing color
  tft.fillScreen();            // Fill with green

  // clear is different from the drawing function and holds the color as a
  // background color. The background color is rarely used, but it is used as
  // the color to fill the gap when using the scroll function.
  tft.clear(0xFFFFFFu);        // Fill with white as background color
  tft.setBaseColor(0x000000u); // Specify black as the background color
  tft.clear();                 // Fill with black


  // The SPI bus is allocated and released automatically when drawing functions
  // are called. If drawing speed is important, use startWrite and endWrite
  // before and after the drawing process. This suppresses securing and releasing
  // the SPI bus, improving speed. In the case of electronic paper (EPD), any
  // drawing after startWrite() is held until calling endWrite().
  tft.drawLine(0, 1, 39, 40, red);       // Secure SPI bus, draw line, release
  tft.drawLine(1, 0, 40, 39, blue);      // Secure SPI bus, draw line, release
  tft.startWrite();                      // Secure SPI bus
  tft.drawLine(38, 0, 0, 38, 0xFFFF00U); // Draw a line
  tft.drawLine(39, 1, 1, 39, 0xFF00FFU); // Draw a line
  tft.drawLine(40, 2, 2, 40, 0x00FFFFU); // Draw a line
  tft.endWrite();                        // Release SPI bus


  // startWrite and endWrite internally count the number of calls and if you call
  // it repeatedly, it will only work at the beginning and end. Be sure to use
  // startWrite and endWrite so that they are paired. (If you don't mind occupying
  // the SPI bus, you can call startWrite once first and not endWrite.)
  tft.startWrite();     // Count +1, secure SPI bus
  tft.startWrite();     // Count +1
  tft.startWrite();     // Count +1
  tft.endWrite();       // Count -1
  tft.endWrite();       // Count -1
  tft.endWrite();       // Count -1, SPI bus release
  tft.endWrite();       // do nothing
  // If you call endWrite excessively, nothing will be done and the count will
  // not go negative.

  // If you want to forcibly release / secure the SPI bus regardless of the count
  // status of startWrite, use endTransaction / beginTransaction.
  // The count will not be cleared, so still be careful to make counts match.
  tft.startWrite();       // Count +1, secure SPI bus
  tft.startWrite();       // Count +1
  tft.drawPixel(0, 0);    // Draw
  tft.endTransaction();   // Release SPI bus
  // Other SPI devices can be used here.
  // When using another device (SD card, etc.) on the same SPI bus, make sure
  // that the SPI bus is free before continuing.
  tft.beginTransaction(); // Secure SPI bus
  tft.drawPixel(0, 0);    // Draw
  tft.endWrite();         // Count -1
  tft.endWrite();         // Count -1, SPI bus release



  // Apart from drawPixel, there is a function that draws a point called
  // writePixel. drawPixel reserves the SPI bus as needed, while writePixel does
  // not check the status of the SPI bus.
  tft.startWrite();   // Secure SPI bus
  for (uint32_t x = 0; x < 128; ++x) {
    for (uint32_t y = 0; y < 128; ++y) {
      tft.writePixel(x, y, tft.color888( x*2, x + y, y*2));
    }
  }
  tft.endWrite();    // SPI bus release
  // All functions whose names start with write (writePixel, writeFastVLine,
  // writeFastHLine, writeFillRect) must explicitly call startWrite.

  delay(1000);

  // Similar drawing functions can be used for drawing on sprites (offscreen).
  // First, specify the color depth of the sprite with setColorDepth. (If
  // omitted, it will be treated as 16.)
  //sprite.setColorDepth(1);   // Set to 1-bit (2 colors) palette mode
  //sprite.setColorDepth(2);   // Set to 2-bit (4 colors) palette mode
  //sprite.setColorDepth(4);   // Set to 4-bit (16 colors) palette mode
  //sprite.setColorDepth(8);   // Set to 8-bit RGB332
  //sprite.setColorDepth(16);  // Set to 16 bits in RGB565
  sprite.setColorDepth(24);    // Set to 24-bit RGB888


  // If you calling createPalette() after setting setColorDepth(8), it will be
  // in 256 color palette mode.
  // sprite.createPalette();


  // Use createSprite to specify the width and height to allocate memory.
  // Memory consumption is proportional to color depth and area. Please note
  // that if it is too large, memory allocation will fail.
  sprite.createSprite(65, 65); // Create sprite with width 65 and height 65.

  for (uint32_t x = 0; x < 64; ++x) {
    for (uint32_t y = 0; y < 64; ++y) {
      // Draw on sprite
      sprite.drawPixel(x, y, tft.color888(3 + x*4, (x + y)*2, 3 + y*4));
    }
  }
  sprite.drawRect(0, 0, 65, 65, 0xFFFF);

  // The created sprite can be output to any coordinates with pushSprite.
  // The output destination will be the LGFX passed as an argument when creating
  // the sprite instance.
  sprite.pushSprite(64, 0);        // Draw sprite at coordinates 64, 0 on tft

  // If you did not pass the pointer of the drawing destination when creating
  // the instance of sprite, or if you have multiple LGFX, you can also pushSprite
  // by specifying the output destination as the first argument.
  sprite.pushSprite(&tft, 0, 64);  // SPI bus release

  delay(1000);

  // You can rotate, scale, and draw sprites with pushRotateZoom.
  // The coordinates set by setPivot are treated as the center of rotation, and
  // the center of rotation is drawn so that it is located at the coordinates
  // of the drawing destination.
  sprite.setPivot(32, 32);    // Rotate around 32, 32
  int32_t center_x = tft.width()/2;
  int32_t center_y = tft.height()/2;
  tft.startWrite();
  for (int angle = 0; angle <= 360; ++angle) {
    // Draw at all angles, width 2.5 times, height 3 times,
    // in the center of the screen
    sprite.pushRotateZoom(center_x, center_y, angle, 2.5, 3);

    // Update the display for electronic paper once every 36 times
    if ((angle % 36) == 0) tft.display();
  }
  tft.endWrite();

  delay(1000);

  // Use deleteSprite to free memory for sprites that are no longer in use.
  sprite.deleteSprite();

  // The same instance can be reused after deleteSprite.
  sprite.setColorDepth(4);     // Set to 4-bit (16 colors) palette mode
  sprite.createSprite(65, 65);

  // In palette mode sprites, the color of the drawing function argument is
  // treated as the palette number. When drawing with pushSprite etc., the
  // actual drawing color is determined by referring to the palette.


  // In 4-bit (16 colors) palette mode, palette numbers 0 to 15 can be used.
  // The initial color of the palette is black at 0, white at the end of the
  // palette, and a gradation from 0 to the end. Use setPaletteColor() to set
  // the palette color.
  sprite.setPaletteColor(1, 0x0000FFU);    // Set palette 1 to blue
  sprite.setPaletteColor(2, 0x00FF00U);    // Set palette 2 to green
  sprite.setPaletteColor(3, 0xFF0000U);    // Set palette 3 to red

  sprite.fillRect(10, 10, 45, 45, 1);   // Fill rectangle with palette color 1
  sprite.fillCircle(32, 32, 22, 2);               // same for color 2
  sprite.fillTriangle(32, 12, 15, 43, 49, 43, 3); // same for color 3

  // The last argument of pushSprite allows you to specify a color that is not
  // drawn, meaning that where it appears in a sprite, the previous pixels that
  // were on the screen will still be visible after pushSprite.
  sprite.pushSprite( 0,  0, 0); // Draw sprite with palette color 0 transparent
  sprite.pushSprite(65,  0, 1); // Draw sprite with palette color 1 transparent
  sprite.pushSprite( 0, 65, 2); // Draw sprite with palette color 2 transparent
  sprite.pushSprite(65, 65, 3); // Draw sprite with palette color 3 transparent

  delay(5000);

  tft.startWrite(); // StartWrite() here to keep the SPI bus occupied.


}