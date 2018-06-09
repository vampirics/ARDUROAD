#include "src/utils/Arduboy2Ext.h"

bool allowChangeGears = true;
bool showGauges = true;
uint8_t clutchCounter = 0;

void playGame() {

  uint8_t speed = player.getYDelta();
  uint8_t frameDelay = player.getGear();

  if (clutchCounter > 0 || speed > 1 || (speed == 1 && arduboy.pressed(A_BUTTON))) { 

    if (horizonIncrement >= frameDelay) {

      level.incHorizonY(&player);
      horizonIncrement = 0;
      
    }

    horizonIncrement++;

  }

  if (arduboy.isFrameCount(3, 0)) {

    otherCars.updatePositions(&player, speed);

  }


  RenderScreen(speed);


  // Move road and horizon scenery .. 

  if (arduboy.isFrameCount(FRAME_COUNT_HORIZON_X * (4 - speed))) {
    level.move(&arduboy, speed);
  }


  // Launch another car?

  if (random(0, 10) == 0 && otherCars.getActiveCars() < NUMBER_OF_OTHER_CARS) {
    
    if (frameDelay < 2) {

      OtherCar *otherCar = otherCars.getInactiveCar();
      otherCar->setActive(true);
      otherCar->setX(random(-70, 70));
      otherCar->setX(70);
      otherCar->setYDelta(randomSFixed<7,8>(1, 3));

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
    else {

      OtherCar *otherCar = otherCars.getInactiveCar();
      otherCar->setActive(true);
      otherCar->setX(random(-70, 70));
      otherCar->setYDelta(randomSFixed<7,8>(1, 3));
      otherCar->setY(80);

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

  if (arduboy.justPressed(B_BUTTON)) showGauges = !showGauges;

  if (clutchCounter > 0) clutchCounter--;



  // Increase time of day ..

  level.incTime();

}
