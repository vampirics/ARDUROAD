#include "src/utils/Arduboy2Ext.h"




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

    const int8_t curve_offset[5][8] = {
        { 32, 22, 14, 8, 4, 2, 1, 0 },
        { 32, 22, 14, 8, 4, 2, 1, 0 },
        { 32, 22, 14, 8, 4, 2, 1, 0 },
        { 32, 22, 14, 8, 4, 2, 1, 0 },
        { 32, 22, 14, 8, 4, 2, 1, 0 },
    };


void RenderScreen(/*Player *player, Enemy *enemies*/) {
 
  uint8_t row = level.getHorizonY();

#ifdef DEBUG_CURVES

font4x6.setCursor(60,50);
font4x6.print(row);

// 0 > 7
// 85,8 73,10        106,8 100,10        
// 73,10 60,14        100,10 96,14        
// 60,14 46,20        96,14 97,20        
// 46,20 33,28        97,20 102,28        
// 33,28 19,38        102,28 112,38        
// 19,38 3,50        112,38 126,50        
// 3,50 -14,64        126,50 142,64        

if (row == 0) {
//                        x1, x2, yTop, x3,   x4, yBottom
  arduboy.fillTrapezoidLH(0,  85,    8,   0,  73,  10, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0,  73,   10,   0,  60,  14, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0,  60,   14,   0,  46,  20, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0,  46,   20,   0,  33,  28, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0,  33,   28,   0,  19,  38, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0,  19,   38,   0,   3,  50, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0,   3,   50,   0, -14,  64, BLACK, BLACK, 2, 2);

//                         x1,    x2, yTop,  x3 ,   x4, yBottom
  arduboy.fillTrapezoidRH(106, WIDTH,    8, 101, WIDTH, 10, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(101, WIDTH,   10,  96, WIDTH, 14, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH( 96, WIDTH,   14,  97, WIDTH, 20, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH( 97, WIDTH,   20, 102, WIDTH, 28, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(102, WIDTH,   28, 112, WIDTH, 38, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(112, WIDTH,   38, 126, WIDTH, 50, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(126, WIDTH,   50, 142, WIDTH, 64, BLACK, BLACK, 1, 2);
}

// 1 > 7
// 85,8 72,10        106,8 99,10        
// 72,10 58,15        99,10 97,15        
// 58,15 45,21        97,15 98,21        
// 45,21 30,30        98,21 105,30        
// 30,30 15,41        105,30 116,41        
// 15,41 0,53        116,41 129,53        
// 0,53 -19,67        129,53 146,67  

if (row == 1) {
  arduboy.fillTrapezoidLH(0, 85, 8, 0, 72, 10, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 72, 10, 0, 58, 15, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 58, 15, 0, 44, 21, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 45, 21, 0, 30, 30, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 30, 30, 0, 15, 41, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 15, 41, 0, 0, 53, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 0, 53, 0, -19, 67, BLACK, BLACK, 2, 2);
  
  arduboy.fillTrapezoidRH(106, WIDTH,8, 99,WIDTH,10, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(99, WIDTH,10, 97,WIDTH,15, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(97, WIDTH,15, 98,WIDTH,21, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(98, WIDTH,21, 105,WIDTH,30, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(105, WIDTH,30, 116,WIDTH,41, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(116, WIDTH,41, 129,WIDTH,53, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(129, WIDTH,53, 146,WIDTH,67, BLACK, BLACK, 1, 2);
}

// 2 > 7
// 85,8 71,11        107,8 100,11        
// 71,11 57,16        100,11 98,16        
// 57,16 44,22        98,16 100,22        
// 44,22 28,32        100,22 107,32        
// 28,32 13,43        107,32 118,43        
// 13,43 -4,56        118,43 133,56        
// -4,56 -22,70        133,56 149,70  

if (row == 2) {
  arduboy.fillTrapezoidLH(0, 85, 8, 0, 71, 11, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 71, 11, 0, 57, 16, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 57, 16, 0, 44, 22, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 44, 22, 0, 28, 32, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 28, 32, 0, 13, 43, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 13, 43, 0, -4, 56, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, -4, 56, 0, -22, 70, BLACK, BLACK, 2, 2);
  
  arduboy.fillTrapezoidRH(107, WIDTH,8, 100,WIDTH,11, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(100, WIDTH,11, 98,WIDTH,16, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(98, WIDTH,16, 100,WIDTH,22, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(100, WIDTH,22, 107,WIDTH,32, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(107, WIDTH,32, 118,WIDTH,43, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(118, WIDTH,43, 133,WIDTH,56, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(133, WIDTH,56, 146,WIDTH,70, BLACK, BLACK, 1, 2);
}

// 3 > 7
// 84,9 71,11        108,9 100,11        
// 71,11 56,17        100,11 99,17        
// 56,17 42,24        99,17 102,24        
// 42,24 26,34        102,24 110,34        
// 26,34 9,46        110,34 122,46        
// 9,46 -7,59        122,46 137,59        
// -7,59 -26,74        137,59 154,74  

if (row == 3) {
  arduboy.fillTrapezoidLH(0, 84, 9, 0, 71, 11, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 71, 11, 0, 56, 17, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 56, 17, 0, 42, 24, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 42, 24, 0, 26, 34, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 26, 34, 0, 9, 46, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 9, 46, 0, -7, 59, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, -7, 59, 0, -26, 74, BLACK, BLACK, 2, 2);
  
  arduboy.fillTrapezoidRH(108, WIDTH, 9, 100,WIDTH,11, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(100, WIDTH, 11, 99,WIDTH,17, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(99, WIDTH, 17, 102,WIDTH,24, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(102, WIDTH,24, 110,WIDTH,34, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(110, WIDTH,34, 122,WIDTH,46, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(122, WIDTH,46, 137,WIDTH,59, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(137, WIDTH,59, 154,WIDTH,74, BLACK, BLACK, 1, 2);
}

// 4 > 7
// 84,9 70,12        108,9 101,12        
// 70,12 55,18        101,12 100,18        
// 55,18 39,26        100,18 104,26        
// 39,26 23,36        104,26 112,36        
// 23,36 7,48        112,36 124,48        
// 7,48 -11,62        124,48 140,62        
// -11,62 -31,78        140,62 158,78  

if (row == 4) {
  arduboy.fillTrapezoidLH(0, 84, 9, 0, 70, 12, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 70, 12, 0, 55, 18, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 55, 18, 0, 39, 26, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 39, 26, 0, 23, 36, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 23, 36, 0, 7, 48, BLACK, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, 7, 48, 0, -11, 62, GREY, BLACK, 2, 2);
  arduboy.fillTrapezoidLH(0, -11, 62, 0, -31, 78, BLACK, BLACK, 2, 2);
  
  arduboy.fillTrapezoidRH(108, WIDTH, 9, 101,WIDTH,12, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(101, WIDTH, 12, 100,WIDTH,18, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(100, WIDTH, 18, 104,WIDTH,26, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(104, WIDTH,26, 112,WIDTH,36, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(112, WIDTH,36, 124,WIDTH,48, BLACK, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(124, WIDTH,48, 140,WIDTH,62, GREY, BLACK, 1, 2);
  arduboy.fillTrapezoidRH(140, WIDTH,62, 158,WIDTH,78, BLACK, BLACK, 1, 2);
}

return;

#endif

// Serial.println("");
// Serial.print(row);
// Serial.print(" > ");
// Serial.print(level.getCurve(0));
// Serial.println("");  
  int8_t xPlayerOffset = player.getXOffset();

  for (uint8_t col = 0; col < HORIZON_COL_COUNT; col++) {

    int8_t curve0 = level.getCurve(col);
    int8_t curve1 = level.getCurve(col + 1);

    int8_t curveOffset0 = (curve0 < 0 ? -1 : 1) * curve_offset[row][HORIZON_COL_COUNT - absT(curve0)] + xPlayerOffset;
    int8_t curveOffset1 = (curve1 < 0 ? -1 : 1) * curve_offset[row][HORIZON_COL_COUNT - absT(curve1)] + xPlayerOffset;

    int16_t x1 = road_outside_left[row][col] + curveOffset0;
    uint8_t y1 = horizon[row][col] + HORIZON_OFFSET;
    
    int16_t x2 = road_outside_left[row][col + 1] + curveOffset1;
    uint8_t y2 = horizon[row][col + 1] + HORIZON_OFFSET;

    int16_t x3 = road_outside_right[row][col] + curveOffset0;
    int16_t x4 = road_outside_right[row][col + 1] + curveOffset1;

    int16_t x5 = road_marking_left[row][col] + curveOffset0;
    int16_t x6 = road_marking_left[row][col + 1] + curveOffset1;
    int16_t x7 = road_marking_right[row][col] + curveOffset0;
    int16_t x8 = road_marking_right[row][col + 1] + curveOffset1;

    uint8_t backgroundColour = BLACK;

// Serial.print(x1);
// Serial.print(",");
// Serial.print(y1);
// Serial.print(" ");
// Serial.print(x2);
// Serial.print(",");
// Serial.print(y2);
// Serial.print("        ");
// Serial.print(x3);
// Serial.print(",");
// Serial.print(y1);
// Serial.print(" ");
// Serial.print(x4);
// Serial.print(",");
// Serial.print(y2);
// Serial.println("        ");


    uint8_t colour = GREY;

    if (col % 2 == level.getBand()) {

      switch (level.getTimeOfDay()) {

        case TimeOfDay::Dawn:
        case TimeOfDay::Day:
          colour = WHITE;
          break;

        case TimeOfDay::Night:
          colour = BLACK;
          break;

      }
    
    }

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

  }

  // Render horizon

  switch (level.getTimeOfDay()) {

    case TimeOfDay::Dawn:

      arduboy.fillRect(0, 0, WIDTH, 10, BLACK);
      Sprites::drawSelfMasked(level.getHorizonX(), 0, horizon_dawn, 0);
      Sprites::drawSelfMasked(level.getHorizonX() + 128, 0, horizon_dawn, 0);
      break;

    case TimeOfDay::Day:

      arduboy.fillRect(0, 0, WIDTH, 10, BLACK);
      Sprites::drawSelfMasked(level.getHorizonX(), 0, horizon_day, 0);
      Sprites::drawSelfMasked(level.getHorizonX() + 128, 0, horizon_day, 0);
      break;

    case TimeOfDay::Night:

      arduboy.fillRect(0, 0, WIDTH, 15, BLACK);
      Sprites::drawSelfMasked(level.getHorizonX(), 0, horizon_night, 0);
      Sprites::drawSelfMasked(level.getHorizonX() + 128, 0, horizon_night, 0);
      break;

  }


  // Render other cars ..

  otherCars.sortCars();

  Direction direction = level.getTurnDirection();

  for (uint8_t i = 0; i < NUMBER_OF_OTHER_CARS; i++) {

//    OtherCar *otherCar = otherCars.getCar(otherCars.getSortedIndex(i));
    OtherCar *otherCar = otherCars.getCar(i);
    // int16_t roadOutsideRight = road_outside_right[row][colIndex] - 64;

    if (otherCar->isActive()) {

      uint8_t colIndex = determineOtherCarArrayIndex(row, otherCar);
      uint8_t otherCarY = otherCar->getY();
      int8_t otherCarX = otherCar->getX();
      uint8_t w = otherCar->getImageWidth();
      int8_t curveIndex = level.getCurve(colIndex);
      int8_t offset = (curveIndex < 0 ? -1 : 1) * curve_offset[row][HORIZON_COL_COUNT - absT(curveIndex)];
      int16_t x = 64 + ((otherCarX + xPlayerOffset) * otherCarY / 67) + offset;

      switch (otherCar->getImageSize()) {

        case ImageSize::Small:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_small, opp_car_small_mask, 0, 0);
          break;

        case ImageSize::Medium:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_medium, opp_car_medium_mask, 0, 0);
          break;

        case ImageSize::Large:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_large, opp_car_large_mask, 0, 0);
          break;
          
      }

    }

  }


  // Render player car last ..

  Sprites::drawExternalMask(player.getX(), 40, mainCar, mainCarMask, mainCarFrame, 0);

}

uint8_t determineOtherCarArrayIndex(uint8_t row, OtherCar *otherCar) {

  uint8_t index = 0;

  for (uint8_t i = 0; i < HORIZON_COL_COUNT; i ++) {

    if (otherCar->getY() < horizon[row][i] + HORIZON_OFFSET) {

      index = i;
      break;

    }

  }

  return index;

}

