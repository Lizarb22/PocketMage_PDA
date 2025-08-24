//  oooooooooooo         ooooo ooooo      ooo oooo    oooo  //
//  `888'     `8         `888' `888b.     `8' `888   .8P'   //
//   888                  888   8 `88b.    8   888  d8'     //
//   888oooo8    8888888  888   8   `88b.  8   88888[       //
//   888    "             888   8     `88b.8   888`88b.     //
//   888       o          888   8       `888   888  `88b.   //
//  o888ooooood8         o888o o8o        `8  o888o  o888o  //
#include "globals.h"

void refresh() {
  // USE A SLOW FULL UPDATE EVERY N FAST UPDATES OR WHEN SPECIFIED
  if ((partialCounter >= FULL_REFRESH_AFTER) || forceSlowFullUpdate) {
    forceSlowFullUpdate = false;
    partialCounter = 0;
    setFastFullRefresh(false);
  }
  // OTHERWISE USE A FAST FULL UPDATE
  else {
    setFastFullRefresh(true);
    partialCounter++;
  }

  display.display(false);

  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.hibernate();
}

void multiPassRefesh(int passes) {
  display.display(false);
  if (passes > 0) {
    for (int i = 0; i < passes; i++) {
      delay(250);
      display.display(true);
    }
  }
  
  delay(100);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.hibernate();
}

void setFastFullRefresh(bool setting) {
  GxEPD2_310_GDEQ031T10::useFastFullUpdate = setting;
  /*if (GxEPD2_310_GDEQ031T10::useFastFullUpdate != setting) {
    GxEPD2_310_GDEQ031T10::useFastFullUpdate = setting;
  }*/
}

void einkHandler(void* parameter) {
  delay(250);
  /*display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.display(false);
  display.hibernate();*/

  while (true) {
    applicationEinkHandler();

    vTaskDelay(50 / portTICK_PERIOD_MS);
    yield();
  }
}

void statusBar(String input, bool fullWindow) {
  display.setFont(&FreeMonoBold9pt7b);
  if (!fullWindow) display.setPartialWindow(0, display.height() - 20, display.width(), 20);
  display.fillRect(0, display.height() - 26, display.width(), 26, GxEPD_WHITE);
  display.drawRect(0, display.height() - 20, display.width(), 20, GxEPD_BLACK);
  display.setCursor(4, display.height() - 6);
  display.print(input);

  /*switch (CurrentKBState) {
    case NORMAL:
      //Display battery level
      display.drawBitmap(display.width()-30,display.height()-20, KBStatusallArray[6], 30, 20, GxEPD_BLACK);
      break;
    case SHIFT:
      display.drawBitmap(display.width()-30,display.height()-20, KBStatusallArray[0], 30, 20, GxEPD_BLACK);
      break;
    case FUNC:
      display.drawBitmap(display.width()-30,display.height()-20, KBStatusallArray[1], 30, 20, GxEPD_BLACK);
      break;
  }*/
  display.drawRect(display.width() - 30, display.height() - 20, 30, 20, GxEPD_BLACK);
}

void drawStatusBar(String input) {
  display.fillRect(0, display.height() - 26, display.width(), 26, GxEPD_WHITE);
  display.drawRect(0, display.height() - 20, display.width(), 20, GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(4, display.height() - 6);
  display.print(input);

  // BATTERY INDICATOR
  //display.drawBitmap(display.width() - 30, display.height() - 20, KBStatusallArray[battState], 30, 20, GxEPD_BLACK);
  //display.drawRect(display.width() - 30, display.height() - 20, 30, 20, GxEPD_BLACK);
}

uint8_t getMaxCharsPerLine() {
  int16_t x1, y1;
  uint16_t charWidth, charHeight;
  // GET AVERAGE CHAR WIDTH
  display.getTextBounds("abcdefghijklmnopqrstuvwxyz", 0, 0, &x1, &y1, &charWidth, &charHeight);
  charWidth = charWidth / 52;

  return (display.width() / (charWidth));
}

uint8_t getMaxLines() {
  int16_t x1, y1;
  uint16_t charWidth, charHeight;
  // GET MAX CHAR HEIGHT
  display.getTextBounds("H", 0, 0, &x1, &y1, &charWidth, &charHeight);
  fontHeight = charHeight;

  return ((display.height() - 26) / (charHeight + lineSpacing));
}

void setTXTFont(const GFXfont* font) {
  // SET THE FONT
  display.setFont(font);
  currentFont = (GFXfont*)font;

  // UPDATE maxCharsPerLine & maxLines
  maxCharsPerLine = getMaxCharsPerLine();
  maxLines = getMaxLines();
}

void einkTextDynamic(bool doFull_, bool noRefresh) {
  // SET FONT
  setTXTFont(currentFont);

  // ITERATE AND DISPLAY
  uint8_t size = allLines.size();
  uint8_t displayLines = maxLines;

  if (displayLines > size) displayLines = size;  // PREVENT OUT OF BOUNDS

  // Apply dynamic scroll offset (make sure it's within the bounds)
  int scrollOffset = dynamicScroll;
  if (scrollOffset < 0) scrollOffset = 0;
  if (scrollOffset > size - displayLines) scrollOffset = size - displayLines;

  // FULL REFRESH OPERATION
  if (doFull_) {
    display.fillScreen(GxEPD_WHITE);
    for (uint8_t i = size - displayLines - scrollOffset; i < size - scrollOffset; i++) {
      if ((allLines[i]).length() > 0) {
        display.setFullWindow();
        //display.fillRect(0, (fontHeight + lineSpacing) * (i - (size - displayLines - scrollOffset)), display.width(), (fontHeight + lineSpacing), GxEPD_WHITE);
        display.setCursor(0, fontHeight + ((fontHeight + lineSpacing) * (i - (size - displayLines - scrollOffset))));
        display.print(allLines[i]);
        Serial.println(allLines[i]);
      }
    }
  }
  // PARTIAL REFRESH, ONLY SEND LAST LINE
  else {
    if ((allLines[size - displayLines - scrollOffset]).length() > 0) {
      display.setPartialWindow(0, (fontHeight + lineSpacing) * (size - displayLines - scrollOffset), display.width(), (fontHeight + lineSpacing));
      display.fillRect(0, (fontHeight + lineSpacing) * (size - displayLines - scrollOffset), display.width(), (fontHeight + lineSpacing), GxEPD_WHITE);
      display.setCursor(0, fontHeight + ((fontHeight + lineSpacing) * (size - displayLines - scrollOffset)));
      display.print(allLines[size - displayLines - scrollOffset]);
    }
  }

  drawStatusBar("L:" + String(allLines.size()) + " " + editingFile);
}

int countLines(String input, size_t maxLineLength) {
  size_t inputLength = input.length();
  uint8_t charCounter = 0;
  uint16_t lineCounter = 1;

  for (size_t c = 0; c < inputLength; c++) {
    if (input[c] == '\n') {
      charCounter = 0;
      lineCounter++;
      continue;
    } else if (charCounter > (maxLineLength - 1)) {
      charCounter = 0;
      lineCounter++;
    }
    charCounter++;
  }

  return lineCounter;
}