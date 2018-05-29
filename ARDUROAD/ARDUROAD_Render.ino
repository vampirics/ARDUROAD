#include "src/utils/Arduboy2Ext.h"



void RenderScreen(/*Player *player, Enemy *enemies*/) {



  Sprites::drawOverwrite(level.getHorizonX(), 0, horizon_dawn, 0);
  Sprites::drawOverwrite(level.getHorizonX() + 128, 0, horizon_dawn, 0);

  // Render the horizon ..

  const uint8_t horizon[5][8] = {
                                { 0, 2,  6, 12, 20, 30, 42, 56 },
                                { 0, 2,  7, 13, 22, 33, 45, 59 },
                                { 0, 3,  8, 14, 24, 35, 48, 62 },
                                { 1, 3,  9, 16, 26, 38, 51, 66 },
                                { 1, 4, 10, 18, 28, 40, 54, 70 }
                                };

  const int16_t road_outside_left[5][8] =  {
                                            { 53, 50, 46, 38, 29, 17,   2, -14 },
                                            { 53, 50, 44, 37, 26, 13,  -1, -19 },
                                            { 53, 49, 43, 36, 24, 11,  -5, -22 },
                                            { 52, 49, 42, 34, 22,  7,  -8, -26 },
                                            { 52, 48, 41 ,31, 19,  5, -12, -31 },
                                            };
  
    const int16_t road_outside_right[5][8] = {
                                            { 74, 77, 82, 89,  98, 110, 125, 142 },
                                            { 74, 77, 83, 90, 101, 114, 128, 146 },
                                            { 75, 78, 84, 92, 103, 116, 132, 149 },
                                            { 76, 78, 85, 94, 106, 120, 136, 154 },
                                            { 76, 79, 86, 96, 108, 122, 139, 158 },
                                            };
  
    const int16_t road_marking_left[5][8] =  {
                                            { 61, 60, 59, 57, 54, 51, 47, 42 },
                                            { 61, 60, 58, 56, 53, 50, 46, 41 },
                                            { 61, 60, 58, 56, 53, 49, 45, 40 },
                                            { 60, 60, 58, 55, 52, 48, 44, 39 },
                                            { 60, 59, 57, 55, 51, 47, 43, 37 },
                                            };
  
    const int16_t road_marking_right[5][8] = {
                                            { 67, 67, 69, 71, 73, 77, 81, 85 },
                                            { 67, 67, 69, 71, 74, 78, 82, 87 },
                                            { 67, 68, 69, 71, 75, 78, 83, 87 },
                                            { 67, 68, 70, 72, 75, 79, 84, 89 },
                                            { 67, 68, 70, 73, 76, 80, 85, 90 },
                                            };

  uint8_t row = level.getHorizonY();
  int8_t xPlayerOffset = player.getXOffset();

  for (uint8_t col = 0; col < HORIZON_COL_COUNT; col++) {

    int16_t x1 = road_outside_left[row][col] + level.getCurve(col) + xPlayerOffset;
    uint8_t y1 = horizon[row][col] + HORIZON_OFFSET;
    
    int16_t x2 = road_outside_left[row][col + 1] + level.getCurve(col + 1) + xPlayerOffset;
    uint8_t y2 = horizon[row][col + 1] + HORIZON_OFFSET;

    int16_t x3 = road_outside_right[row][col] + level.getCurve(col) + xPlayerOffset;
    int16_t x4 = road_outside_right[row][col + 1] + level.getCurve(col + 1) + xPlayerOffset;

    int16_t x5 = road_marking_left[row][col] + level.getCurve(col) + xPlayerOffset;
    int16_t x6 = road_marking_left[row][col + 1] + level.getCurve(col + 1) + xPlayerOffset;
    int16_t x7 = road_marking_right[row][col] + level.getCurve(col) + xPlayerOffset;
    int16_t x8 = road_marking_right[row][col + 1] + level.getCurve(col + 1) + xPlayerOffset;

    uint8_t backgroundColour = BLACK;
    uint8_t colour = (col % 2 == level.getBand() ? BLACK : GREY );

    arduboy.fillTrapezoidLH(0,x1,y1, 0,x2,y2, colour, backgroundColour, 2, 2);
    arduboy.fillTrapezoidRH(x3,WIDTH,y1, x4,WIDTH,y2, colour, backgroundColour, 1, 2);

    if (col > 0 && (col % 2 == level.getBand())) {

      arduboy.drawLine(x5, y1, x6, y2);
      arduboy.drawLine(x7, y1, x8, y2);

      switch (col) {

        case 4 ... 5:

          arduboy.drawLine(x5, y1, x6 + 1, y2);
          arduboy.drawLine(x7, y1, x8 + 1, y2);
          break;

        case 6 ... 7:

          arduboy.drawLine(x5 + 1, y1, x6 + 1, y2);
          arduboy.drawLine(x7 + 1, y1, x8 + 1, y2);
          break;

      }

    }

    Sprites::drawExternalMask(player.getX(), 40, mainCar, mainCarMask, mainCarFrame, 0);


  }

}