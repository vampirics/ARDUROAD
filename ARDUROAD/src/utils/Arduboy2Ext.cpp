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

void Arduboy2Ext::fillTrapezoidLH(int16_t x0, int16_t x1, int16_t yTop, int16_t x2, int16_t x3, int16_t yBottom, uint8_t colour, uint8_t backgroundColour, uint8_t drawBorder, uint8_t drawBorderWidth) {

	const int16_t dy = yBottom - yTop;
	const int16_t dx03 = x3 - x0;
	const int16_t dx13 = x3 - x1;

  int16_t dOld = 0;
	int16_t sc = 0;
	int16_t sd = 0;

	for (int16_t y = yTop; y <= yBottom; ++y) {
      
		if (y >= 64) break;
	
		int16_t c = x1 + sc / dy;
		int16_t d = x0 + sd / dy;

		if (c > d) { swap(c, d); }

		const int16_t temp = d + 1;

		if (temp > 0 && colour != backgroundColour) {
			drawFastHLine2(0, y, temp, colour);  
		}

    switch (drawBorder) {

      case BORDER_NONE:
        break;

      case BORDER_RIGHT: 
        {
          int16_t tempD = d + 1 - drawBorderWidth;
          int16_t tempWidth = drawBorderWidth;

          if (y != yTop) {
            if (tempD > dOld + 1) {
              tempD = dOld + 1;
              tempWidth = tempWidth + (tempD - dOld); 
            }
          }

          drawFastHLine(tempD, y, tempWidth, WHITE);

        }
        break;

    }

		sc += dx13;
		sd += dx03;
    dOld = d;

	}

}


void Arduboy2Ext::fillTrapezoidRH(int16_t x0, int16_t x1, int16_t yTop, int16_t x2, int16_t x3, int16_t yBottom, uint8_t colour, uint8_t backgroundColour, uint8_t drawBorder, uint8_t drawBorderWidth) {
		
	const int16_t dy = yBottom - yTop;	
	const int16_t dx02 = x2 - x0;
	const int16_t dx12 = x2 - x1;
	
  int16_t aOld = 0;
	int16_t sa = 0;
	int16_t sb = 0;

	for (int16_t y = yTop; y <= yBottom; ++y)	{

		if(y >= 64) break;
	
		int16_t a = x1 + sa / dy;
		int16_t b = x0 + sb / dy;

		if (a > b) { swap(a, b); }

		const int16_t temp = 127 - a + 1;

		if (temp > 0 && colour != backgroundColour) {
			drawFastHLine2(a, y, temp, colour);  
		}

    switch (drawBorder) {

      case BORDER_NONE:
        break;

      case BORDER_LEFT:
        {
          int16_t tempWidth = a + drawBorderWidth;
          if (y != yTop) {
            if (tempWidth < aOld) tempWidth = aOld; 
          }
          drawFastHLine(a, y,  tempWidth - a, WHITE);
        }
        break;

    }

		sa += dx12;
		sb += dx02;
    aOld = a;
    
	}
  
}

void Arduboy2Ext::drawFastHLine2(int16_t x, int16_t y, uint8_t width, uint8_t colour) {

	// Check width?
	// if (width == 0) return;
	
	// Do y bounds checks
	if (y < 0 || y >= HEIGHT) return;

	// last x point + 1
	int16_t xEnd = x + width;

	// Check if the entire line is not on the display
	if (xEnd <= 0 || x >= WIDTH) return;

	// Don't start before the left edge
	if (x < 0) x = 0;

	// Don't end past the right edge
	if (xEnd > WIDTH) xEnd = WIDTH;

	// calculate actual visibleWidth (even if unchanged)
	const uint8_t visibleWidth = xEnd - x;

	// buffer pointer plus row offset + x offset
	uint8_t * screenBufferRow = sBuffer + ((y / 8) * WIDTH) + x;

	// pixel mask
	uint8_t mask = 1 << (y & 7);

	switch (colour) {

		case WHITE:

			for(uint8_t i = visibleWidth; i > 0; --i)
			{
				*screenBufferRow |= mask;
				++screenBufferRow;
			}
			break;

		case BLACK:
		{
			const uint8_t invertedMask = ~mask;
			for(uint8_t i = visibleWidth; i > 0; --i) {
				*screenBufferRow &= invertedMask;
				++screenBufferRow;
			}
			break;
		}

		case GREY:
		{
			bool alt = !((y % 2 == 0) ^ (x % 2 == 0));
			const uint8_t invertedMask = ~mask;

			for(uint8_t i = visibleWidth; i > 0; --i) {

				if (alt) {
					*screenBufferRow |= mask;
				}
				else {
					*screenBufferRow &= invertedMask;
				}

				++screenBufferRow;
				alt = !alt;

			}

			break;

		}

	}

}
