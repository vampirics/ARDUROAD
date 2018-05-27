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


void Arduboy2Ext::fillTrapezoid(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, 
                                int16_t x3, int16_t y3, uint8_t color, uint8_t backgroundColor, 
                                uint8_t drawBorder, uint8_t drawBorderWidth) {

  int16_t a, b, c, d, y, aOld, dOld;

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



    if (color != backgroundColor) { 

      if (y < 64 && d - a + 1 > 0 ) {

        drawFastHLine2( a, y, d - a + 1, color); 
  
      }
    
    }

    switch (drawBorder) {

      case 0:
        break;

      case 1:  // left
        {
          int16_t tempWidth = a + drawBorderWidth;
          if (y != y0) {
            if (tempWidth < aOld) tempWidth = aOld; 
          }
          drawFastHLine(a, y,  tempWidth - a, WHITE);
        }
        break;

      case 2:  // right
        {
          int16_t tempD = d + 1 - drawBorderWidth;
          int16_t tempWidth = drawBorderWidth;
          if (y != y0) {
            if (tempD > dOld + 1) {
              tempD = dOld + 1;
              tempWidth = tempWidth + (tempD - dOld); 
            }
          }
          drawFastHLine(tempD, y, tempWidth, WHITE);
        }
        break;

    }

    aOld = a;
    dOld = d;

  }
  //Serial.println("\n\n");

}

void Arduboy2Ext::drawFastHLine2(int16_t x, int16_t y, uint8_t w, uint8_t color2) {

  int16_t xEnd; // last x point + 1
  uint8_t color = color2;
  bool alt = false;

  // Do y bounds checks
  if (y < 0 || y >= HEIGHT)
    return;

  xEnd = x + w;

  // Check if the entire line is not on the display
  if (xEnd <= 0 || x >= WIDTH)
    return;

  // Don't start before the left edge
  if (x < 0)
    x = 0;

  // Don't end past the right edge
  if (xEnd > WIDTH)
    xEnd = WIDTH;

  // calculate actual width (even if unchanged)
  w = xEnd - x;

  // buffer pointer plus row offset + x offset
  register uint8_t *pBuf = sBuffer + ((y / 8) * WIDTH) + x;

  // pixel mask
  register uint8_t mask = 1 << (y & 7);

  switch (color) {

    case WHITE:
      while (w--) {
        *pBuf++ |= mask;
      }
      break;

    case BLACK:
      mask = ~mask;
      while (w--) {
        *pBuf++ &= mask;
      }
      break;

    case GREY:
    {
      register uint8_t mask2 = ~(1 << (y & 7));
      alt = ((x ) % 2 == 0);// + (y%2 == 0);
      alt = (y%2==0 ? alt : !alt);

      while (w--) {
        if (!alt) {
        *pBuf++ &= ~mask;
        }
        else {
          *pBuf++ |= mask;
        }
        alt = !alt;
      }
    }
      break;

  }

}