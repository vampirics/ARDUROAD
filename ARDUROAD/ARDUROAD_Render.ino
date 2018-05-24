#include "src/utils/Arduboy2Ext.h"

uint8_t bander = 0;
// --------------------------------------------------------------------------------------
//  Render the screen
//
void RenderScreen(/*Player *player, Enemy *enemies*/) {

  Sprites::drawOverwrite(0, 0, horizon_dawn, 0);

  // Render the horizon ..

  const uint8_t horizon[5][8] = {
                                { 0, 2,  6, 12, 20, 30, 42, 56 },
                                { 0, 2,  7, 13, 22, 33, 45, 59 },
                                { 0, 3,  8, 14, 24, 35, 48, 62 },
                                { 1, 3,  9, 16, 26, 38, 51, 66 },
                                { 1, 4, 10, 18, 28, 40, 54, 70 }
                                };


  uint8_t row = level.getHorizon();

  for (uint8_t col = 0; col < HORIZON_COL_COUNT; col++) {

    uint8_t y1 = horizon[row][col] + HORIZON_OFFSET;
    uint8_t y2 = horizon[row][col + 1] + HORIZON_OFFSET;

    if (col % 2 == level.getBand()) {
      
      while (y1 <= y2) {
      
        uint8_t const *imageName = nullptr;
        uint8_t y3 = y1;
      
        switch (y2 - y1) {

          case 0:
            y1 = y1 + 1;
            break;
          
          case 1:
            imageName = check16x1;
            y1 = y1 + 1;
            break;

          case 2 ... 3:
            imageName = check16x2;
            y1 = y1 + 2;
            break;

          case 4 ... 7:
            imageName = check16x4;
            y1 = y1 + 4;
            break;

          case 8 ... 999:
            imageName = check16x8;
            y1 = y1 + 8;
            break;

        }

        if (imageName != nullptr) {

          for (uint8_t x = 0; x < WIDTH; x+=16) {

            Sprites::drawSelfMasked(x, y3, imageName, 0);

          }

        }

      }

    }

  }

}
