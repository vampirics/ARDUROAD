#include "src/utils/Arduboy2Ext.h"




  // Render the horizon ..

  const uint8_t horizon[5][8] = {//w g  w   g   w   g   w   g
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

void RenderScreen(uint8_t speed) {
 
  uint8_t row = level.getHorizonY();

//uint16_t m = micros();

  int8_t xPlayerOffset = player.getXOffset();

  for (uint8_t col = 0; col < HORIZON_COL_COUNT; col++) {


    int8_t curve0 = level.getCurve(col);
    int8_t curve1 = level.getCurve(col + 1);

    int8_t curveOffset0 = (curve0 < 0 ? -1 : 1) * curve_offset[0][HORIZON_COL_COUNT - absT(curve0)] + xPlayerOffset;
    int8_t curveOffset1 = (curve1 < 0 ? -1 : 1) * curve_offset[0][HORIZON_COL_COUNT - absT(curve1)] + xPlayerOffset;

    int16_t x1 = road_outside_left[0][col] + curveOffset0;
    uint8_t y1 = horizon[0][col] + HORIZON_OFFSET;
    
    int16_t x2 = road_outside_left[0][col + 1] + curveOffset1;
    uint8_t y2 = horizon[0][col + 1] + HORIZON_OFFSET;

    int16_t x3 = road_outside_right[0][col] + curveOffset0;
    int16_t x4 = road_outside_right[0][col + 1] + curveOffset1;

    int16_t x5 = road_marking_left[0][col] + curveOffset0;
    int16_t x6 = road_marking_left[0][col + 1] + curveOffset1;
    uint8_t y5 = horizon[0][col] + HORIZON_OFFSET;
    int16_t x7 = road_marking_right[0][col] + curveOffset0;
    int16_t x8 = road_marking_right[0][col + 1] + curveOffset1;
    uint8_t y7 = horizon[0][col + 1] + HORIZON_OFFSET;

    // uint8_t backgroundColour = BLACK;


    // uint8_t colour = GREY;

    // if (col % 2 == level.getBand()) {

    //   switch (level.getTimeOfDay()) {

    //     case TimeOfDay::Dawn:
    //     case TimeOfDay::Day:
    //       colour = WHITE;
    //       break;

    //     case TimeOfDay::Night:
    //       colour = BLACK;
    //       break;

    //   }
    
    // }


    drawRoadSegment(x1, y1, x3, y1, x2, y2, x4, y2);


    if (col > 0 && (col % 2 == level.getBand())) {

      switch (col) {

        case 2 ... 3:
          arduboy.drawLine(x5, y5, x6, y7);
          arduboy.drawLine(x7, y5, x8, y7);
          break;

        case 4 ... 5:
          arduboy.drawLine(x5, y5, x6 + 1, y7);
          arduboy.drawLine(x7, y5, x8 + 1, y7);
          break;

        case 6 ... 7:
          arduboy.drawLine(x5 + 1, y5, x6 + 1, y7);
          arduboy.drawLine(x7 + 1, y5, x8 + 1, y7);
          break;

      }

    }

  }


  // uint16_t n = micros();

  // Serial.print(", time:");
  // Serial.println(n - m);


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

  // for (uint8_t i = 0; i < NUMBER_OF_OTHER_CARS; i++) {
  //   OtherCar *otherCar = otherCars.getCar(i);
  //   if (otherCar->isActive()) {
  //   Serial.print("i: ");
  //   Serial.print(i);
  //   Serial.print(" ");
  //   Serial.print(otherCar->isActive());
  //   Serial.print(" ");
  //   Serial.print(otherCar->getX());
  //   Serial.print(", ");
  //   Serial.print(otherCar->getY().getInteger());
  //   Serial.print(" ");
  //   }
    
  // }
  // Serial.println(" ");
  // for (uint8_t i = 0; i < NUMBER_OF_OTHER_CARS; i++) {
  //   uint8_t s = otherCars.getSortedIndex(i);
  //   Serial.print("  i: ");
  //   Serial.print(i);
  //   Serial.print(",");
  //   Serial.print(s);
  //   Serial.print(" ");
    
  // }
  // Serial.println(" ");


  for (uint8_t i = 0; i < NUMBER_OF_OTHER_CARS; i++) {

    OtherCar *otherCar = otherCars.getCar(otherCars.getSortedIndex(i));

    if (otherCar->isActive() && otherCar->isVisible()) {
      uint8_t colIndex = determineOtherCarArrayIndex(0, otherCar);
//      uint8_t otherCarY = otherCar->getY().getInteger() + otherCar->getYOffset();
      uint8_t otherCarY = otherCar->getYDisplay();
      int8_t otherCarX = otherCar->getX();
      uint8_t w = otherCar->getImageWidthHalf();
      int8_t curveIndex = level.getCurve(colIndex);
      int8_t offset = (curveIndex < 0 ? -1 : 1) * curve_offset[0][HORIZON_COL_COUNT - absT(curveIndex)];
      int16_t x = 64 + (((otherCarX * otherCarY) / 67) + offset + xPlayerOffset);
Serial.print("colIndex=");
Serial.print(colIndex);
Serial.print(" otherCarY=");
Serial.print(otherCarY);
Serial.print(" w=");
Serial.print(w);
Serial.print(" ci=");
Serial.print(curveIndex);
Serial.print(" offset=");
Serial.print(offset);
Serial.print(" x=");
Serial.print(x);
Serial.println("");

Serial.print(otherCar->getYOffset());
Serial.print(" ");
Serial.println(otherCarY);
      switch (otherCar->getImageSize()) {

        case ImageSize::Disappearing:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_6, opp_car_6_mask, 0, 0);
          break;

        case ImageSize::Minute:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_5, opp_car_5_mask, 0, 0);
          break;

        case ImageSize::Tiny:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_4, opp_car_4_mask, 0, 0);
          break;

        case ImageSize::Small:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_3, opp_car_3_mask, 0, 0);
          break;

        case ImageSize::Medium:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_2, opp_car_2_mask, 0, 0);
          break;

        case ImageSize::Large:
          Sprites::drawExternalMask(x - w, otherCarY, opp_car_1, opp_car_1_mask, 0, 0);
          break;
          
      }

    }

  }


  // Render player car last ..

  Sprites::drawExternalMask(player.getX(), 40, mainCar, mainCarMask, mainCarFrame, 0);


  #ifdef GEARBOX

  Sprites::drawExternalMask(108, 47, gearbox, gearbox_mask, 0, 0);

  switch (speed) {

    case 0 ... 1: 
      Sprites::drawExternalMask(108, 46, ShiftStickKnob, ShiftStickKnobMask, 0, 0);
      break;

    case 2: 
      Sprites::drawExternalMask(108, 58, ShiftStickKnob, ShiftStickKnobMask, 0, 0);
      break;

    case 3: 
      Sprites::drawExternalMask(114, 46, ShiftStickKnob, ShiftStickKnobMask, 0, 0);
      break;

    case 4: 
      Sprites::drawExternalMask(114, 58, ShiftStickKnob, ShiftStickKnobMask, 0, 0);
      break;

  }

  #endif
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

void drawRoadSegment(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3) {
		
 	const int8_t dy02 = y2 - y0;
 	const int8_t dy13 = y3 - y1;
 	const int8_t dx02 = x2 - x0;
 	const int8_t dx13 = x3 - x1;
	const int8_t yDiff = y0 - y1;
	
	int16_t sb = 0;
	int16_t sc = dx13 * yDiff;

	for (int16_t y = y0; y <= y2; ++y) {

		if (y >= 64) break;
	
		int16_t a = x0 + sb / dy02;
		int16_t d = x1 + sc / dy13;

		arduboy.drawFastHLine(a, y, 2, WHITE);  
		arduboy.drawFastHLine(a + 2, y, d - a - 3, BLACK);  
		arduboy.drawFastHLine(d - 1, y, 2, WHITE);  

		sb += dx02;
		sc += dx13;
	
	}

}
