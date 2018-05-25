#include "Arduboy2Ext.h"

Arduboy2Ext::Arduboy2Ext() : Arduboy2() { }

uint8_t Arduboy2Ext::justPressedButtons() const {

  return (~previousButtonState & currentButtonState);

}

uint8_t Arduboy2Ext::pressedButtons() const {

  return currentButtonState;

}

void Arduboy2Ext::clearButtonState() {

  currentButtonState = previousButtonState = 0;

}

uint16_t Arduboy2Ext::getFrameCount() const {

  return frameCount;

}

uint8_t Arduboy2Ext::getFrameCount(uint8_t mod) const {

  return frameCount % mod;

}

bool Arduboy2Ext::isFrameCount(uint8_t mod) const {

  return (frameCount % mod) == 0;

}

bool Arduboy2Ext::isFrameCount(uint8_t mod, uint8_t val) const {

  return (frameCount % mod) == val;

}

/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 */
void Arduboy2Ext::drawHorizontalDottedLine(uint8_t x1, uint8_t x2, uint8_t y, uint8_t spacing) {

  for (uint8_t x3 = x1; x3 <= x2; x3+=spacing) {
    drawPixel(x2, y, WHITE);
  }
  
}


/* ----------------------------------------------------------------------------
 *  Draw a vertical dotted line. 
 */
void Arduboy2Ext::drawVerticalDottedLine(uint8_t y1, uint8_t y2, uint8_t x, uint8_t spacing) {

  for (uint8_t y3 = y1; y3 <= y2; y3+=spacing) {
    drawPixel(x, y3, WHITE);
  }
  
}


void Arduboy2Ext::fillTrapezoid(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint8_t color) {

  int16_t a, b, c, d, y;

  int16_t dx02 = x2 - x0,
          dy02 = y2 - y0,
          dx12 = x2 - x1,
          dy12 = y2 - y1,
          dx03 = x3 - x0,
          dy03 = y3 - y0,
          dx13 = x3 - x1,
          dy13 = y3 - y1,
          sa = 0,
          sb = 0,
          sc = 0,
          sd = 0;

  y = y0;

  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  sc = dx13 * (y - y1);
  sd = dx03 * (y - y0);

  for(; y <= y2; y++) {

    a = x1 + sa / dy12;
    b = x0 + sb / dy02;
    c = x1 + sc / dy13;
    d = x0 + sd / dy03;

    sa += dx12;
    sb += dx02;
    sc += dx13;
    sd += dx03;

    if (a > b) { swap(a, b); }
    if (c > d) { swap(c, d); }

    drawFastHLine( a, y, d-a+1, color);

  }

}