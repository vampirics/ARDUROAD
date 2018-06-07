#include "src/utils/Arduboy2Ext.h"


#define RENDER_CAR_COUNTER_LEFT   104
#define RENDER_CAR_COUNTER_TOP    3

#define RENDER_GEARBOX_RHS_LEFT 108
#define RENDER_GEARBOX_RHS_TOP  47

#define RENDER_GEARBOX_LHS_LEFT 1
#define RENDER_GEARBOX_LHS_TOP  47

bool drawOnLHS = true;


// Render the horizon ..

const uint8_t horizon[8] = { 0, 2, 6, 12, 20, 30, 42, 56 };
const int16_t road_outside_left[8] =  { 53, 50, 46, 38, 29, 17, 2, -14 };
const int16_t road_outside_right[8] = { 74, 77, 82, 89, 98, 110, 125, 142 };
const int16_t road_marking_left[8] =  { 61, 60, 59, 57, 54, 51, 47, 42 };
const int16_t road_marking_right[8] = { 67, 67, 69, 71, 73, 77, 81, 85 };
const int8_t curve_offset[8] = { 32, 22, 14, 8, 4, 2, 1, 0 };

const int8_t curve_offset1[8][32] = { 
  //0
{ 
  0,0,0,0,   //0-7
  0,0,0,0,   //8-15
  0,0,0,0,   //16-23
  0,0,0,0,           //24-31
  0,0,0,0,           //32-39
  0,0,0,0,           //40-47
  0,0,0,0,           //48-55
  0,0,0,0,           //56-63
  },
  //1
{ 
  1,1,1,1,   //0-7
  1,1,1,2,   //8-15
  0,0,0,0,   //16-23
  0,0,0,0,           //24-31
  0,0,0,0,           //32-39
  0,0,0,0,           //40-47
  0,0,0,0,           //48-55
  0,0,0,0,           //56-63
  },
  //2
 { 
  1,1,1,1,   //0-7
  1,1,1,1,   //8-15
  0,0,0,0,   //16-23
  0,0,0,0,           //24-31
  0,0,0,0,           //32-39
  0,0,0,0,           //40-47
  0,0,0,0,           //48-55
  0,0,0,0,           //56-63
  },
  //3
 { 
  2,2,2,2,   //0-7
  2,2,2,2,   //8-15
  2,2,0,0,   //16-23
  0,0,0,0,           //24-31
  0,0,0,0,           //32-39
  0,0,0,0,           //40-47
  0,0,0,0,           //48-55
  0,0,0,0,           //56-63
  },
  //4
 { 
  25,23,21,18,   //0-7
  16,14,12,11,   //8-15
  9,8,7,6,   //16-23
  5,5,4,4,           //24-31
  4,4,3,3,           //32-39
  3,2,2,2,           //40-47
  2,2,2,1,           //48-55
  0,0,0,0,           //56-63
  },
  //5
{ 
  25,23,21,18,   //0-7
  16,14,12,11,   //8-15
  9,8,7,6,   //16-23
  5,5,4,4,           //24-31
  3,3,3,3,           //32-39
  3,2,2,2,           //40-47
  2,2,2,1,           //48-55
  0,0,0,0,           //56-63
  },
  //6
{ 
  25,23,21,18,   //0-7
  16,14,12,11,   //8-15
  9,8,7,6,   //16-23
  5,5,4,4,           //24-31
  3,3,3,3,           //32-39
  3,2,2,2,           //40-47
  2,2,2,1,           //48-55
  0,0,0,0,           //56-63
  },
  //7
{ 
  25,23,21,18,   //0-7
  16,14,12,11,   //8-15
  9,8,7,6,   //16-23
  5,5,4,4,           //24-31
  3,3,3,3,           //32-39
  3,2,2,2,           //40-47
  2,2,2,1,           //48-55
  0,0,0,0,           //56-63
  }
};


void RenderScreen(uint8_t gear) {
 
  uint8_t row = level.getHorizonY();

//uint16_t m = micros();

  int8_t xPlayerOffset = player.getXOffset();

  for (uint8_t col = 0; col < HORIZON_COL_COUNT; col++) {


    int8_t curve0 = level.getCurve(col);
    int8_t curve1 = level.getCurve(col + 1);

    int8_t curveOffset0 = (curve0 < 0 ? -1 : 1) * curve_offset[HORIZON_COL_COUNT - absT(curve0)] + xPlayerOffset;
    int8_t curveOffset1 = (curve1 < 0 ? -1 : 1) * curve_offset[HORIZON_COL_COUNT - absT(curve1)] + xPlayerOffset;

    int16_t x1 = road_outside_left[col] + curveOffset0;
    uint8_t y1 = horizon[col] + HORIZON_OFFSET;
    
    int16_t x2 = road_outside_left[col + 1] + curveOffset1;
    uint8_t y2 = horizon[col + 1] + HORIZON_OFFSET;

    int16_t x3 = road_outside_right[col] + curveOffset0;
    int16_t x4 = road_outside_right[col + 1] + curveOffset1;

    int16_t x5 = road_marking_left[col] + curveOffset0;
    int16_t x6 = road_marking_left[col + 1] + curveOffset1;
    uint8_t y5 = horizon[col] + HORIZON_OFFSET;
    int16_t x7 = road_marking_right[col] + curveOffset0;
    int16_t x8 = road_marking_right[col + 1] + curveOffset1;
    uint8_t y7 = horizon[col + 1] + HORIZON_OFFSET;


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
    case TimeOfDay::Dusk:

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

    OtherCar *otherCar = otherCars.getCar(otherCars.getSortedIndex(i));

    if (otherCar->isActive() && otherCar->isVisible()) {

      uint8_t otherCarY = otherCar->getYDisplay();
      int8_t otherCarX = otherCar->getX();
      uint8_t colIndex = determineOtherCarArrayIndex(0, otherCar);
      int8_t curveIndex = level.getCurve(colIndex);

      int8_t offset = (curveIndex < 0 ? -1 : 1) * curve_offset1[absT(curveIndex)][otherCarY / 2];
      uint8_t w = otherCar->getImageWidthHalf();
      int16_t x = 64 + ((otherCarX * otherCarY) / 56) + offset + xPlayerOffset;

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



  // Render car counter ..
  
  Sprites::drawExternalMask(RENDER_CAR_COUNTER_LEFT, RENDER_CAR_COUNTER_TOP, CarCounter, CarCounterMask, 0, 0);
  {
    uint8_t carsPassed = player.getCarsPassed();

    Sprites::drawExternalMask(RENDER_CAR_COUNTER_LEFT +  3, RENDER_CAR_COUNTER_TOP + 3, numbers_white, numbers_white_mask, carsPassed / 100, 0);                           
    carsPassed = carsPassed % 100;
    Sprites::drawExternalMask(RENDER_CAR_COUNTER_LEFT +  9, RENDER_CAR_COUNTER_TOP + 3, numbers_white, numbers_white_mask, carsPassed / 10, 0);                           
    Sprites::drawExternalMask(RENDER_CAR_COUNTER_LEFT + 15, RENDER_CAR_COUNTER_TOP + 3, numbers_white, numbers_white_mask, carsPassed % 10, 0);
  }


  // Render gearbox ..
  {
    uint8_t xPos = 0;
    uint8_t yPos = 0; 

    switch (player.getX()) {

      case 0 ... 30:
        xPos = RENDER_GEARBOX_RHS_LEFT;
        yPos = RENDER_GEARBOX_RHS_TOP;
        drawOnLHS = false;
        break;

      case 31 ... 41:
        if (!drawOnLHS) {
          xPos = RENDER_GEARBOX_RHS_LEFT;
          yPos = RENDER_GEARBOX_RHS_TOP;
          drawOnLHS = false;
        }
        else {
          xPos = RENDER_GEARBOX_LHS_LEFT;
          yPos = RENDER_GEARBOX_LHS_TOP;
          drawOnLHS = true;
        }
        break;

      case 42 ... 52:
        if (!drawOnLHS) {
          xPos = RENDER_GEARBOX_RHS_LEFT;
          yPos = RENDER_GEARBOX_RHS_TOP;
          drawOnLHS = false;
        }
        else {
          xPos = RENDER_GEARBOX_LHS_LEFT;
          yPos = RENDER_GEARBOX_LHS_TOP;
          drawOnLHS = true;
        }
        break;

      case 53 ... 85:
        xPos = RENDER_GEARBOX_LHS_LEFT;
        yPos = RENDER_GEARBOX_LHS_TOP;
        drawOnLHS = true;
        break;

    }

    Sprites::drawExternalMask(xPos, yPos, gearbox, gearbox_mask, 0, 0);

    switch (gear) {

      case 0:

        switch (arduboy.getFrameCount(16)) {

          case 0 ... 3:     xPos+= 2;   yPos+= 6;  break;
          case 4 ... 7:     xPos+= 3;   yPos+= 6;  break;
          case 8 ... 11:    xPos+= 4;   yPos+= 6;  break;
          case 12 ... 15:   xPos+= 3;   yPos+= 6;  break;
            
        }
        break;
      
      case 1:                                      break;
      case 2:                           yPos+= 11; break;
      case 3:               xPos+= 6;              break;
      case 4:               xPos+= 6;   yPos+= 11; break;

    }

    Sprites::drawExternalMask(xPos, yPos, gearbox_knob, gearbox_knob_mask, 0, 0);

  }



}

uint8_t determineOtherCarArrayIndex(uint8_t row, OtherCar *otherCar) {

  for (uint8_t i = 0; i < HORIZON_COL_COUNT; i ++) {

    if (otherCar->getY() < horizon[i] + HORIZON_OFFSET) {

      return i;

    }

  }

  return 0;

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
