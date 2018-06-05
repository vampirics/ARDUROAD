#include "Arduboy2Ext.h"

Arduboy2Ext::Arduboy2Ext() : Arduboy2() { }

byte Arduboy2Ext::flicker = 0;

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




void Arduboy2Ext::displayWithBackground(uint8_t index, uint8_t band)
{
  paintScreenWithBackground(sBuffer, index, band);
}

// paint from a memory buffer, this should be FAST as it's likely what
// will be used by any buffer based subclass
// PaintScreen normally takes about 1496 us, so about 23936 clock cycles, so approx 23 clocks per byte
// The fastest possible is 1300 us, about 20800 clocks, approx 20 clocks per byte
// The loop takes 7 clocks, so 13 free clocks per byte to do something for free

  // const uint8_t PROGMEM masks[20][8] = {

	// 															{ 0, 215, 95, 245, 127, 85, 253, 255 }, 		// Row 0, Band 0 
	// 															{ 0, 235, 175, 250, 191, 170, 254, 255 },
	// 															{ 0, 125, 245, 95, 213, 255, 87, 85 }, 			// Row 0, Band 1 
	// 															{ 0, 190, 250, 175, 234, 255, 171, 170},

	// 															{ 0, 215, 95, 213, 255, 85, 245, 255 }, 		// Row 1, Band 0 
	// 															{ 0, 171, 191, 234, 255, 171, 234, 255 }, 
	// 															{ 0, 125, 245, 127, 85, 255, 95, 85 }, 			// Row 1, Band 1
	// 															{ 0, 254, 234, 191, 170, 254, 191, 170 },

	// 															{ 0, 87, 127, 85, 255, 87, 85, 255 },				// Row 2, Band 0 
	// 															{ 0, 175, 191, 170, 255, 175, 170, 255 },
	// 															{ 0, 253, 213, 255, 85, 253, 255, 85 }, 		// Row 2, Band 1 
	// 															{ 0, 250, 234, 255, 170, 250, 255, 170 },

	// 															{ 0, 86, 255, 85, 253, 127, 85, 253 }, 			// Row 3, Band 0 
	// 															{ 0, 174, 254, 170, 254, 191, 170, 250 },
	// 															{ 0, 252, 85, 255, 87, 213, 255, 87 }, 			// Row 3, Band 1 
	// 															{ 0, 250, 171, 255, 171, 234, 255, 175 },

	// 															{ 0, 94, 253, 87, 245, 255, 85, 245 }, 			// Row 4, Band 0 
	// 															{ 0, 174, 254, 171, 250, 255, 170, 250 },
	// 															{ 0, 244, 87, 253, 95, 85, 255, 255 }, 			// Row 4, Band 1
	// 															{ 0, 250, 171, 254, 175, 170, 255, 255}

  //                              };

  const uint8_t PROGMEM masks[] = {

																 0, 215, 95, 245, 127, 85, 253, 255, 				// Row 0, Band 0 
																 0, 235, 175, 250, 191, 170, 254, 255,
																 0, 125, 245, 95, 213, 255, 87, 85, 				// Row 0, Band 1 
																 0, 190, 250, 175, 234, 255, 171, 170,

																 0, 215, 95, 213, 255, 85, 245, 255,	 			// Row 1, Band 0 
																 0, 171, 191, 234, 255, 171, 234, 255, 
																 0, 125, 245, 127, 85, 255, 95, 85, 				// Row 1, Band 1
																 0, 254, 234, 191, 170, 254, 191, 170,

																 0, 87, 127, 85, 255, 87, 85, 255,					// Row 2, Band 0 
																 0, 175, 191, 170, 255, 175, 170, 255,
																 0, 253, 213, 255, 85, 253, 255, 85,		 		// Row 2, Band 1 
																 0, 250, 234, 255, 170, 250, 255, 170,

																 0, 86, 255, 85, 253, 127, 85, 253, 				// Row 3, Band 0 
																 0, 174, 254, 170, 254, 191, 170, 250,
																 0, 252, 85, 255, 87, 213, 255, 87,	 				// Row 3, Band 1 
																 0, 250, 171, 255, 171, 234, 255, 175,

																 0, 94, 253, 87, 245, 255, 85, 245, 				// Row 4, Band 0 
																 0, 174, 254, 171, 250, 255, 170, 250,
																 0, 244, 87, 253, 95, 85, 255, 255, 				// Row 4, Band 1
																 0, 250, 171, 254, 175, 170, 255, 255

                               };
// Row: 0, Band: 0 0 215 95 245 127 85 253 63 0 235 175 250 191 170 254 31, time:8752
// Row: 0, Band: 1 0 125 245 95 213 255 87 53 0 190 250 175 234 255 171 26, time:8648

// Row: 1, Band: 0 0 215 95 213 255 85 245 63 0 171 191 234 255 171 234 31, time:8752
// Row: 1, Band: 1 0 125 245 127 85 255 95 53 0 254 234 191 170 254 191 26, time:8604

//Row: 2, Band: 0 0 87 127 85 255 87 85 255 0 175 191 170 255 175 170 255, time:8768
// Row: 2, Band: 1 0 253 213 255 85 253 255 21 0 250 234 255 170 250 255 26, time:8592

// Row: 3, Band: 0 0 86 255 85 253 127 85 61 0 174 254 170 254 191 170 26, time:8516
// Row: 3, Band: 1 0 252 85 255 87 213 255 55 0 250 171 255 171 234 255 31, time:8368

// Row: 4, Band: 0 0 94 253 87 245 255 85 117 0 174 254 171 250 255 170 58, time:8488
// Row: 4, Band: 1 0 244 87 253 95 85 255 95 0 250 171 254 175 170 255 15, time:8416


void Arduboy2Ext::paintScreenWithBackground(uint8_t image[], uint8_t index, uint8_t band) {

	bool alternate = false;

	for (uint8_t y = 0; y < 8; y++) {

		// uint8_t mask1 = masks[(index * 4) + (band * 2)][y];
		// uint8_t mask2 = masks[(index * 4) + (band * 2) + 1][y];
		uint8_t mask1 = pgm_read_byte(&masks[(((index * 4) + (band * 2)) * 8) + y]);
		uint8_t mask2 = pgm_read_byte(&masks[(((index * 4) + (band * 2) + 1) * 8) + y]);
		// uint8_t mask1 = pgm_read_byte(&masks[1]);
		// uint8_t mask2 = pgm_read_byte(&masks[9]);

		for (uint8_t x = 0; x < WIDTH; x++) {

			SPDR = *image;

			*image = (x % 2 == 0 ? mask1 : mask2);
			*image++;
			alternate = ~alternate;

			// Spare cycles, we could use them to do something else for free:

			asm volatile("\
				nop \n\
				nop \n\
				nop \n\
				nop \n\
				nop \n\
				nop \n\
				nop \n\
				nop \n\
				nop \n\
				nop \n\
				");

			// One additional 'nop' to fix the problematic byte at (1,0) which remains black for mysterious reason.
			asm volatile("nop");

		}

	} 

	while (!(SPSR & _BV(SPIF))) {}

}
