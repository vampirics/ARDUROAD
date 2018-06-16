#include "src/utils/Arduboy2Ext.h"

bool allowChangeGears = true;
bool showGauges = true;
uint8_t clutchCounter = 0;

void playGame() {

  uint8_t speed = player.getYDelta().getInteger();
  uint8_t frameDelay = player.getFrameDelay();

  if (clutchCounter > 0 || speed > 1 || (speed == 1 && arduboy.pressed(A_BUTTON))) { 

    if (horizonIncrement >= frameDelay) {

      level.incHorizonY(&player);
      horizonIncrement = 0;
      
    }

    horizonIncrement++;

  }

  if (arduboy.isFrameCount(3, 0)) {

    carController.updatePositions(&player, speed);

  }


  RenderScreen(speed);


  // Move road and horizon scenery .. 

  if (arduboy.isFrameCount(FRAME_COUNT_HORIZON_X * (5 - speed))) {
    level.move(&arduboy, speed);
  }


  // Launch another car?
  
  {
    if (random(0, 10) == 0) {
Serial.print("Launch");
      OtherCar *otherCar = carController.getInactiveCar();

      if (otherCar != nullptr) {
Serial.print(" - car free");
      
        if (frameDelay < 2) {
          
          OtherCar *otherCarLowestY = carController.getActiveCar_LowestY();
Serial.print(" - LowestY ");

          if (otherCarLowestY == nullptr || otherCarLowestY->getY() > 20) {
            
            otherCar->setActive(true);
            otherCar->setX(random(OTHER_CAR_X_MIN, OTHER_CAR_X_MAX + 1));
            otherCar->setYDelta(randomSFixed<7,8>(1, 3));
            otherCar->setXDelta(static_cast<Direction>(random(static_cast<int8_t>(Direction::Left), static_cast<int8_t>(Direction::Right) + 1)));
            otherCar->setTurnLength(random(0, OTHER_CAR_TURN_LENGTH_MAX + 1));

            switch (level.getTimeOfDay()) {
              
              case TimeOfDay::Dusk:
              case TimeOfDay::Dawn:
                otherCar->setY(DIST_6_BEGIN_DUSK);
                break;

              case TimeOfDay::Day:
                otherCar->setY(DIST_6_BEGIN_DAY);
                break;

              case TimeOfDay::Night:
                otherCar->setY(DIST_6_BEGIN_NIGHT);
                break;

            }

          }

        }
        else {

          OtherCar *otherCarHighestY = carController.getActiveCar_HighestY();

          if (otherCarHighestY == nullptr || otherCarHighestY->getY() < 65) {

            OtherCar *otherCar = carController.getInactiveCar();
            otherCar->setActive(true);
            otherCar->setYDelta(randomSFixed<7,8>(1, 3));
            otherCar->setXDelta(static_cast<Direction>(random(static_cast<int8_t>(Direction::Left), static_cast<int8_t>(Direction::Right) + 1)));
            otherCar->setTurnLength(random(0, OTHER_CAR_TURN_LENGTH_MAX + 1));
            otherCar->setY(80);

            int8_t playerXCentered = player.getXCentered();

            int randMin = 0;
            int randMax = 0;

            switch (playerXCentered) {

              case -37 ... -17:
                randMin = -17 + PLAYER_WIDTH;
                randMax = OTHER_CAR_X_MAX;
                break;

              case -16 ... 0:
                randMin = PLAYER_WIDTH;
                randMax = OTHER_CAR_X_MAX;
                break;

              case 1 ... 16:
                randMin = OTHER_CAR_X_MIN;
                randMax = -PLAYER_WIDTH;
                break;

              case 17 ... 37:
                randMin = OTHER_CAR_X_MIN;
                randMax = 17 - PLAYER_WIDTH;
                break;

            }

            otherCar->setX(random(randMin, randMax + 1));

          }

        }

      }

    }

  }
  

  //Handle player's keypresses ..

  if (arduboy.pressed(A_BUTTON) && speed > 0) { 

    if (arduboy.everyXFrames(2)) {
      mainCarFrame = !mainCarFrame;
    }
    allowChangeGears = true;

  }

  if (arduboy.pressed(LEFT_BUTTON) && speed > 0)     { player.decX(); }
  if (arduboy.pressed(RIGHT_BUTTON) && speed > 0)    { player.incX(); }

  if (allowChangeGears && !arduboy.pressed(A_BUTTON) && arduboy.justPressed(UP_BUTTON)) { 
    if (player.incYDelta()) horizonIncrement = 0; 
    allowChangeGears = false; 
    clutchCounter = 30; 
  }

  if (allowChangeGears && !!arduboy.pressed(A_BUTTON) && arduboy.justPressed(DOWN_BUTTON)) { 
    
    if (player.decYDelta()) horizonIncrement = 0; 
    allowChangeGears = false; 
    clutchCounter = 30;  
  
  }

  if (!arduboy.pressed(A_BUTTON) && clutchCounter == 0 && arduboy.everyXFrames(FRAME_RATE_16)) { 
    
    if (!player.decelerate()) allowChangeGears = true; 
    
  }

  if (arduboy.justPressed(B_BUTTON)) /*showGauges = !showGauges;*/ gameState = GameState::GameOver_Init;

  if (clutchCounter > 0) clutchCounter--;



  // Increase time of day ..

  level.incTime();

}
