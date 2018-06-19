#pragma once

#include <Arduboy2.h>
#include "Enums.h"
#define GREY 2
#define BORDER_NONE 0
#define BORDER_LEFT 1
#define BORDER_RIGHT 2

class Arduboy2Ext : public Arduboy2Base {

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
    void drawFastHLine2(int16_t x, int16_t y, uint8_t w, uint8_t color2 = WHITE);

    void displayWithBackground(TimeOfDay timeOfDay, uint8_t index, uint8_t band);
    void paintScreenWithBackground(uint8_t image[], TimeOfDay timeOfDay, uint8_t index, uint8_t band);

};
