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

//  uint32_t m = micros();

  int8_t xPlayerOffset = player.getXOffset();

  for (uint8_t col = 0; col < HORIZON_COL_COUNT; col++) {

    int8_t curve0 = level.getCurve(col);
    int8_t curve1 = level.getCurve(col + 1);

    int8_t curveOffset0 = pgm_read_byte(&curve_offset[HORIZON_COL_COUNT - absT(curve0)]);
    if (curve0 < 0) curveOffset0 = -curveOffset0;
    curveOffset0  += xPlayerOffset;

    int8_t curveOffset1 = pgm_read_byte(&curve_offset[HORIZON_COL_COUNT - absT(curve1)]);
    if (curve1 < 0) curveOffset1 = -curveOffset1;
    curveOffset1  += xPlayerOffset;

    int16_t x1 = pgm_read_word_near(&road_outside_left[col]) + curveOffset0;
    uint8_t y1 = pgm_read_byte(&horizon[col]) + HORIZON_OFFSET;
    
    int16_t x2 = pgm_read_word_near(&road_outside_left[col + 1]) + curveOffset1;
    uint8_t y2 = pgm_read_byte(&horizon[col + 1]) + HORIZON_OFFSET;

    int16_t x3 = pgm_read_word_near(&road_outside_right[col]) + curveOffset0;
    int16_t x4 = pgm_read_word_near(&road_outside_right[col + 1]) + curveOffset1;


    drawRoadSegment(x1, x3, y1, x2, x4, y2);


    if (col > 0 && (col % 2 == level.getBand())) {

      const int16_t x5 = pgm_read_word_near(&road_marking_left[col]) + curveOffset0;
      const int16_t x6 = pgm_read_word_near(&road_marking_left[col + 1]) + curveOffset1;
      const int16_t x7 = pgm_read_word_near(&road_marking_right[col]) + curveOffset0;
      const int16_t x8 = pgm_read_word_near(&road_marking_right[col + 1]) + curveOffset1;

      const uint8_t col2 = col / 2;
      if (col2 > 0 && col2 < 4) {

        arduboy.drawLine(x5, y1, x6, y2);
        arduboy.drawLine(x7, y1, x8, y2);

      }

    }

  }


  // uint32_t n = micros();

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

    if (baseCar->getId() == PLAYER_INDEX) {

        Sprites::drawPlusMask(player.getX(), 39, mainCar, mainCarFrame);
        uint8_t dirtCloud = player.getDirtCloud();

        if (dirtCloud > 0) {

          Sprites::drawPlusMask(player.getX(), 57, dirt_cloud, (dirtCloud % 3));
          player.decDirtCloud();

        }

    }
    else {

      OtherCar *otherCar = (OtherCar *)baseCar;
      TimeOfDay timeOfDay = level.getTimeOfDay();

      if (otherCar->isActive() && otherCar->isVisible(timeOfDay)) {
        
        uint8_t mask = (timeOfDay == TimeOfDay::Night ? 1 : 0);

        uint8_t otherCarY = otherCar->getYDisplay();
        int8_t otherCarX = otherCar->getX();
        uint8_t colIndex = determineOtherCarArrayIndex(otherCar);
        int8_t curveIndex = level.getCurve(colIndex);

        int8_t offset = pgm_read_byte(&curve_offset1[absT(curveIndex)][otherCarY / 2]);
        if (curveIndex < 0) offset = -offset;

        uint8_t w = otherCar->getImageWidthHalf();
        int16_t x = 64 + ((otherCarX * otherCarY) / 39) + offset + xPlayerOffset;

        uint8_t index = static_cast<uint8_t>(otherCar->getImageSize());
        Sprites::drawPlusMask(x - w, otherCarY, opp_cars[index], mask);

      }

    }

  }


  // Render car counter ..
  
  if (showGauges && gameState != GameState::GameOver) {
      
    Sprites::drawPlusMask(RENDER_CAR_COUNTER_LEFT, RENDER_CAR_COUNTER_TOP, CarCounter, 0);

//    if (gameState == GameState::PlayGame || (gameState == GameState::PlayGame_StartOfDay && carCounterBlink % 2 == 0)) {
    if (carCounterBlink % 2 == 0) {

      uint8_t carsPassed = player.getCarsPassed();
      arduboy.setRGBled(0, 0, 0);

      Sprites::drawOverwrite(RENDER_CAR_COUNTER_LEFT +  2, RENDER_CAR_COUNTER_TOP + 2, numbers_white, carsPassed / 100);                           
      carsPassed = carsPassed % 100;
      Sprites::drawOverwrite(RENDER_CAR_COUNTER_LEFT +  8, RENDER_CAR_COUNTER_TOP + 2, numbers_white, carsPassed / 10);                           
      Sprites::drawOverwrite(RENDER_CAR_COUNTER_LEFT + 14, RENDER_CAR_COUNTER_TOP + 2, numbers_white, carsPassed % 10);

    }
    else {

      arduboy.fillRect(RENDER_CAR_COUNTER_LEFT + 2, RENDER_CAR_COUNTER_TOP + 2, 18, 8, BLACK);

      if (gameState == GameState::PlayGame) {
        arduboy.setRGBled(32, 0, 0);
      }
      else {
        arduboy.setRGBled(0, 32, 0);
      }

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

      switch (player.getTransmissionType()) {

        case TransmissionType::Automatic:
          {
            switch (gear) {

              case 0:
                Sprites::drawExternalMask(xPos + (drawOnLHS ? 0 : -4), yPos + 2, AutoN, AutoMask, 0, 0);
                break;

              default:
                Sprites::drawExternalMask(xPos + (drawOnLHS ? 0 : -4), yPos + 2, AutoD, AutoMask, 0, 0);
                break;

            }

          }
          break;

        case TransmissionType::Manual:
          {
            Sprites::drawPlusMask(xPos, yPos, gearbox, 0);

            static const uint8_t gearLookup[] PROGMEM = { 2, 3, 4, 3, };
                
            switch (gear) {

              case 0:
                {
                  const uint8_t index = (arduboy.getFrameCount(16) / 4);
                  xPos += pgm_read_byte(&gearLookup[index]);
                  yPos += 6;
                }
                break;
              
              case 1:                                      break;
              case 2:                           yPos+= 11; break;
              case 3:               xPos+= 6;              break;
              case 4:               xPos+= 6;   yPos+= 11; break;

            }

            Sprites::drawPlusMask(xPos, yPos, gearbox_knob, 0);
          }
          break;

      }


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



  // Display start of day logo?

  if (gameState == GameState::PlayGame_StartOfDay) {

    Sprites::drawPlusMask(16, 15, StartOfDay, 0);

    // font4x6.setCursor(18, 26);
    // font4x6.print(F("Day 00 Target 050"));

  }

  if (gameState == GameState::GameOver) {

    Sprites::drawOverwrite(0, 14, GameOverBanner, 0);

    if (!fadeInEffect.isComplete()) {

      fadeInEffect.draw(arduboy);
      fadeInEffect.update();

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
	
	const SQ7x8 xRatio = SQ7x8(dx02) / SQ7x8(dy);
	const SQ7x8 yRatio = SQ7x8(dx13) / SQ7x8(dy);
	
	SQ7x8 sb = 0;
	SQ7x8 sc = 0;

	for (int16_t y = y01; y <= y23; ++y) {

		if (y >= 64) break;
	
		const int8_t a = x0 + static_cast<int8_t>(sb);
		const int8_t d = x1 + static_cast<int8_t>(sc);
		sb += xRatio;
		sc += yRatio;

		arduboy.drawFastHLine(a, y, 2, WHITE);  
		arduboy.drawFastHLine(a + 2, y, d - a - 3, BLACK);  
		arduboy.drawFastHLine(d - 1, y, 2, WHITE); 
		
	}

}
