#pragma once

#include <Arduboy2.h>
#define GREY 2
#define BORDER_NONE 0
#define BORDER_LEFT 1
#define BORDER_RIGHT 2
#define DIRECTION_STRAIGHT 0
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT 2

class Arduboy2Ext : public Arduboy2 {

  public:

    Arduboy2Ext();

    uint8_t justPressedButtons() const;
    uint8_t pressedButtons() const;
    uint16_t getFrameCount() const;
    uint8_t getFrameCount(uint8_t mod) const;
    bool isFrameCount(uint8_t mod) const;
    bool isFrameCount(uint8_t mod, uint8_t val) const;

    void clearButtonState();
    
    void drawHorizontalDottedLine(uint8_t x1, uint8_t x2, uint8_t y, uint8_t spacing);
    void drawVerticalDottedLine(uint8_t y1, uint8_t y2, uint8_t x, uint8_t spacing);
    void fillTrapezoidLH(int16_t x0, int16_t x1, int16_t yTop, int16_t x2, int16_t x3, int16_t yBottom, uint8_t color, uint8_t backgroundColor, uint8_t drawBorder, uint8_t drawBorderWidth);
    void fillTrapezoidRH(int16_t x0, int16_t x1, int16_t yTop, int16_t x2, int16_t x3, int16_t yBottom, uint8_t color, uint8_t backgroundColor, uint8_t drawBorder, uint8_t drawBorderWidth);

    void drawFastHLine2(int16_t x, int16_t y, uint8_t w, uint8_t color2 = WHITE);
};
