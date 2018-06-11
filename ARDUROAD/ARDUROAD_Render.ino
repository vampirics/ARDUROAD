#include "src/utils/Arduboy2Ext.h"


#define RENDER_CAR_COUNTER_LEFT     104
#define RENDER_CAR_COUNTER_TOP      3

#define RENDER_GEARBOX_RHS_LEFT     109
#define RENDER_GEARBOX_RHS_TOP      38

#define RENDER_GEARBOX_LHS_LEFT     1
#define RENDER_GEARBOX_LHS_TOP      39

#define RENDER_ODOMETER_LHS_LEFT    32
#define RENDER_ODOMETER_RHS_LEFT    120
#define RENDER_ODOMETER_TOP         56

bool drawOnLHS = true;


// Render the horizon ..

const uint8_t PROGMEM horizon[8] =            { 0, 2, 6, 12, 20, 30, 42, 56 };
const int16_t PROGMEM road_outside_left[8] =  { 53, 50, 46, 38, 29, 17, 2, -14 };
const int16_t PROGMEM road_outside_right[8] = { 74, 77, 82, 89, 98, 110, 125, 142 };
const int16_t PROGMEM road_marking_left[8] =  { 61, 60, 59, 57, 54, 51, 47, 42 };
const int16_t PROGMEM road_marking_right[8] = { 67, 67, 69, 71, 73, 77, 81, 85 };
const int8_t  PROGMEM curve_offset[8] =       { 32, 22, 14, 8, 4, 2, 1, 0 };

const int8_t  PROGMEM curve_offset1[8][32] = { 
                                      { 0,0,0,0,           // 0-7         Line 0
                                        0,0,0,0,           // 8-15
                                        0,0,0,0,           // 16-23
                                        0,0,0,0,           // 24-31
                                        0,0,0,0,           // 32-39
                                        0,0,0,0,           // 40-47
                                        0,0,0,0,           // 48-55
                                        0,0,0,0,},         // 56-63

                                      { 1,1,1,1,           // 0-7         Line 1
                                        1,1,1,2,           // 8-15
                                        0,0,0,0,           // 16-23
                                        0,0,0,0,           // 24-31
                                        0,0,0,0,           // 32-39
                                        0,0,0,0,           // 40-47
                                        0,0,0,0,           // 48-55
                                        0,0,0,0,},         // 56-63

                                      { 1,1,1,1,           // 0-7         Line 2
                                        1,1,1,1,           // 8-15
                                        0,0,0,0,           // 16-23
                                        0,0,0,0,           // 24-31
                                        0,0,0,0,           // 32-39
                                        0,0,0,0,           // 40-47
                                        0,0,0,0,           // 48-55
                                        0,0,0,0,},         // 56-63

                                      { 2,2,2,2,           // 0-7         Line 3
                                        2,2,2,2,           // 8-15
                                        2,2,0,0,           // 16-23
                                        0,0,0,0,           // 24-31
                                        0,0,0,0,           // 32-39
                                        0,0,0,0,           // 40-47
                                        0,0,0,0,           // 48-55
                                        0,0,0,0,},         // 56-63

                                      { 25,23,21,18,       // 0-7         Line 4
                                        16,14,12,11,       // 8-15
                                        9,8,7,6,           // 16-23
                                        5,5,4,4,           // 24-31
                                        4,4,3,3,           // 32-39
                                        3,2,2,2,           // 40-47
                                        2,2,2,1,           // 48-55
                                        0,0,0,0,},         // 56-63

                                      { 25,23,21,18,       // 0-7         Line 5
                                        16,14,12,11,       // 8-15
                                        9,8,7,6,           // 16-23
                                        5,5,4,4,           // 24-31
                                        3,3,3,3,           // 32-39
                                        3,2,2,2,           // 40-47
                                        2,2,2,1,           // 48-55
                                        0,0,0,0,},         // 56-63

                                      { 25,23,21,18,       // 0-7         Line 6
                                        16,14,12,11,       // 8-15
                                        9,8,7,6,           // 16-23
                                        5,5,4,4,           // 24-31
                                        3,3,3,3,           // 32-39
                                        3,2,2,2,           // 40-47
                                        2,2,2,1,           // 48-55
                                        0,0,0,0,},         // 56-63

                                      { 25,23,21,18,       // 0-7         Line 7
                                        16,14,12,11,       // 8-15
                                        9,8,7,6,           // 16-23
                                        5,5,4,4,           // 24-31
                                        3,3,3,3,           // 32-39
                                        3,2,2,2,           // 40-47
                                        2,2,2,1,           // 48-55
                                        0,0,0,0,}          // 56-63

                                    };

void RenderScreen(uint8_t gear) {

// uint16_t m = micros();

  int8_t xPlayerOffset = player.getXOffset();

  for (uint8_t col = 0; col < HORIZON_COL_COUNT; col++) {


    int8_t curve0 = level.getCurve(col);
    int8_t curve1 = level.getCurve(col + 1);

    int8_t curveOffset0 = (curve0 < 0 ? -1 : 1) * pgm_read_byte(&curve_offset[HORIZON_COL_COUNT - absT(curve0)]) + xPlayerOffset;
    int8_t curveOffset1 = (curve1 < 0 ? -1 : 1) * pgm_read_byte(&curve_offset[HORIZON_COL_COUNT - absT(curve1)]) + xPlayerOffset;

    int16_t x1 = pgm_read_word_near(&road_outside_left[col]) + curveOffset0;
    uint8_t y1 = pgm_read_byte(&horizon[col]) + HORIZON_OFFSET;
    
    int16_t x2 = pgm_read_word_near(&road_outside_left[col + 1]) + curveOffset1;
    uint8_t y2 = pgm_read_byte(&horizon[col + 1]) + HORIZON_OFFSET;

    int16_t x3 = pgm_read_word_near(&road_outside_right[col]) + curveOffset0;
    int16_t x4 = pgm_read_word_near(&road_outside_right[col + 1]) + curveOffset1;

    int16_t x5 = pgm_read_word_near(&road_marking_left[col]) + curveOffset0;
    int16_t x6 = pgm_read_word_near(&road_marking_left[col + 1]) + curveOffset1;
    int16_t x7 = pgm_read_word_near(&road_marking_right[col]) + curveOffset0;
    int16_t x8 = pgm_read_word_near(&road_marking_right[col + 1]) + curveOffset1;
    
    drawRoadSegment(x1, x3, y1, x2, x4, y2);


    if (col > 0 && (col % 2 == level.getBand())) {

      switch (col) {

        case 2 ... 3:
          arduboy.drawLine(x5, y1, x6, y2);
          arduboy.drawLine(x7, y1, x8, y2);
          break;

        case 4 ... 5:
          arduboy.drawLine(x5, y1, x6, y2);
          arduboy.drawLine(x7, y1, x8, y2);
          #ifdef THICK_LINES
          arduboy.drawLine(x5, y1, x6 - 1, y2);
          arduboy.drawLine(x7, y1, x8 + 1, y2);
          #endif
          break;

        case 6 ... 7:
          arduboy.drawLine(x5, y1, x6, y2);
          arduboy.drawLine(x7, y1, x8, y2);
          #ifdef THICK_LINES
          arduboy.drawLine(x5 - 1, y1, x6 - 1, y2);
          arduboy.drawLine(x7 + 1, y1, x8 + 1, y2);
          #endif
          break;

      }

    }

  }


  // uint16_t n = micros();

  // Serial.print(", time:");
  // Serial.println(n - m);


  // Render horizon

  arduboy.fillRect(0, 0, WIDTH, pgm_read_byte(&horizon_heights[level.getTimeOfDayImageIndex()]), BLACK);
  Sprites::drawSelfMasked(level.getHorizonX(), 0, horizons, level.getTimeOfDayImageIndex());
  Sprites::drawSelfMasked(level.getHorizonX() + 128, 0, horizons, level.getTimeOfDayImageIndex());


  // Render other cars ..

  carController.sortCars();

  for (uint8_t i = 0; i < NUMBER_OF_CARS_INC_PLAYER; i++) {

    Base *baseCar = carController.getCarBase(carController.getSortedIndex(i));

    switch (baseCar->getCarType()) {

      case CarType::OtherCar:
        {
          OtherCar *otherCar = (OtherCar *)baseCar;
          TimeOfDay timeOfDay = level.getTimeOfDay();

          if (otherCar->isActive() && otherCar->isVisible(timeOfDay)) {
            
            uint8_t mask = (timeOfDay == TimeOfDay::Night ? 1 : 0);

            uint8_t otherCarY = otherCar->getYDisplay();
            int8_t otherCarX = otherCar->getX();
            uint8_t colIndex = determineOtherCarArrayIndex(otherCar);
            int8_t curveIndex = level.getCurve(colIndex);

            int8_t offset = (curveIndex < 0 ? -1 : 1) * pgm_read_byte(&curve_offset1[absT(curveIndex)][otherCarY / 2]);
            uint8_t w = otherCar->getImageWidthHalf();
// Serial.print(otherCarX);
// Serial.print(" ");
// Serial.print(otherCarY);
// Serial.print(" ");
// Serial.print((otherCarX * otherCarY) / 39);
// Serial.print(" ");
// Serial.print(offset);
// Serial.print(" ");
// Serial.print(xPlayerOffset);
            
            int16_t x = 64 + ((otherCarX * otherCarY) / 39) + offset + xPlayerOffset;
// Serial.print(" ");
// Serial.println(x);

            uint8_t index = static_cast<uint8_t>(otherCar->getImageSize());
            Sprites::drawExternalMask(x - w, otherCarY, opp_cars[index], opp_car_masks[index], mask, 0);

          }

        }
        break;

      case CarType::Player:

        Sprites::drawExternalMask(player.getX(), 39, mainCar, mainCarMask, mainCarFrame, 0);
        {
          uint8_t dirtCloud = player.getDirtCloud();

          if (dirtCloud > 0) {

            Sprites::drawExternalMask(player.getX(), 57, dirt_cloud, dirt_cloud_mask, dirtCloud - 1, dirtCloud - 1);
            player.decDirtCloud();

          }
        }
        break;

      case CarType::Unknown:
        break;

    }

  }


  // Render car counter ..
  
  if (showGauges) {
      
    Sprites::drawExternalMask(RENDER_CAR_COUNTER_LEFT, RENDER_CAR_COUNTER_TOP, CarCounter, CarCounterMask, 0, 0);
    {
      uint8_t carsPassed = player.getCarsPassed();

      Sprites::drawOverwrite(RENDER_CAR_COUNTER_LEFT +  2, RENDER_CAR_COUNTER_TOP + 2, numbers_white, carsPassed / 100);                           
      carsPassed = carsPassed % 100;
      Sprites::drawOverwrite(RENDER_CAR_COUNTER_LEFT +  8, RENDER_CAR_COUNTER_TOP + 2, numbers_white, carsPassed / 10);                           
      Sprites::drawOverwrite(RENDER_CAR_COUNTER_LEFT + 14, RENDER_CAR_COUNTER_TOP + 2, numbers_white, carsPassed % 10);
    }


    // Render gearbox and odometer ..
    {
      uint8_t xPos = 0;
      uint8_t yPos = 0; 

      switch (player.getX()) {

        case 0 ... 39:
          xPos = RENDER_GEARBOX_RHS_LEFT;
          yPos = RENDER_GEARBOX_RHS_TOP;
          drawOnLHS = false;
          break;

        case 40 ... 42:
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

        case 43 ... 46:
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

        case 47 ... 85:
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


      // Score ..
      {
        uint8_t digits[5] = {};
        extractDigits(digits, player.getOdometer() / 10);
        
        for (uint8_t i = 0, x2 = (drawOnLHS ? RENDER_ODOMETER_LHS_LEFT : RENDER_ODOMETER_RHS_LEFT) - 7; i < 5; ++i, x2 -= 6) {
          Sprites::drawOverwrite(x2, RENDER_ODOMETER_TOP, numbers_white, digits[i]);
        }

        Sprites::drawOverwrite((drawOnLHS ? RENDER_ODOMETER_LHS_LEFT : RENDER_ODOMETER_RHS_LEFT), RENDER_ODOMETER_TOP, numbers_black, player.getOdometer() % 10);
        
      }

    }

  }

}

uint8_t determineOtherCarArrayIndex(OtherCar *otherCar) {

  for (uint8_t i = 0; i < HORIZON_COL_COUNT; i ++) {

    if (otherCar->getY() < horizon[i] + HORIZON_OFFSET) {

      return i;

    }

  }

  return 0;

}

void drawRoadSegment(int16_t x0, int16_t x1, uint8_t y01, int16_t x2, int16_t x3, uint8_t y23) {
		
 	const int8_t dy = y23 - y01;
 	const int8_t dx02 = x2 - x0;
 	const int8_t dx13 = x3 - x1;
	
	int16_t sb = 0;
	int16_t sc = 0;

	for (int16_t y = y01; y <= y23; ++y) {

		if (y >= 64) break;
	
		int16_t a = x0 + sb / dy;
		int16_t d = x1 + sc / dy;

		arduboy.drawFastHLine(a, y, 2, WHITE);  
		arduboy.drawFastHLine(a + 2, y, d - a - 3, BLACK);  
		arduboy.drawFastHLine(d - 1, y, 2, WHITE);  

		sb += dx02;
		sc += dx13;
	
	}

}
