#include "src/utils/Arduboy2Ext.h"

bool allowChangeGears = true;
uint8_t clutchCounter = 0;

void playGame() {


    // Update the ground's position ..

    // const uint8_t speedLookup[] = {12, 6, 4, 2, 1};
    uint8_t speed = player.getYDelta();


//  if (gameState != GameState::Paused) {

    uint8_t frameDelay = player.getGear();

Serial.print(speed);
Serial.print(" ");
Serial.print(frameDelay);
Serial.print(" ");
Serial.print(clutchCounter);
Serial.print(" ");
Serial.print(arduboy.pressed(A_BUTTON));
Serial.print(" ");
    if (clutchCounter > 0 || speed > 1 || (speed == 1 && arduboy.pressed(A_BUTTON))) { 

      if (horizonIncrement == frameDelay) {
Serial.print("xxxx");

        /*if (speed >= 1)  */level.incHorizonY(1);
        horizonIncrement = 0;
        
      }

      horizonIncrement++;

    }
Serial.println(" ");
    if (arduboy.isFrameCount(3, 0)) {

      otherCars.updatePositions(&player, speed);

    }

 


    RenderScreen(speed);


    // Move road and horizon scenery ..

    if (arduboy.isFrameCount(FRAME_COUNT_HORIZON_X * (4 - speed))) {
      level.move(&arduboy, speed);
    }




  // Launch another car?

  if (random(0, 10) == 0 && otherCars.getActiveCars() < 1){//NUMBER_OF_OTHER_CARS) {

    if (frameDelay > 3) {

      OtherCar *otherCar = otherCars.getInactiveCar();
      otherCar->setActive(true);
      otherCar->setX(random(-70, 70));
      otherCar->setX(70);
      otherCar->setYDelta(randomSFixed<7,8>(1, 3));
      otherCar->setY(DIST_6_BEGIN);

    }
    else {

      OtherCar *otherCar = otherCars.getInactiveCar();
      otherCar->setActive(true);
      otherCar->setX(random(-70, 70));
      otherCar->setYDelta(randomSFixed<7,8>(1, 3));
      otherCar->setY(80);

    }




  }

    if (arduboy.pressed(A_BUTTON) && speed > 0)     { 
                                          if (arduboy.everyXFrames(2)) {// when running at 60fps
                                            mainCarFrame = !mainCarFrame;
                                          }
                                          allowChangeGears = true;
                                        }
    if (arduboy.pressed(LEFT_BUTTON) && speed > 0)     { player.decX(); }
    if (arduboy.pressed(RIGHT_BUTTON) && speed > 0)    { player.incX(); }
    if (allowChangeGears && !arduboy.pressed(A_BUTTON) && arduboy.justPressed(UP_BUTTON))    { if (player.incYDelta()) horizonIncrement = 0; allowChangeGears = false; clutchCounter = 30; }
    if (allowChangeGears && !!arduboy.pressed(A_BUTTON) && arduboy.justPressed(DOWN_BUTTON))  { if (player.decYDelta()) horizonIncrement = 0; allowChangeGears = false; clutchCounter = 30;  }

//    if ((arduboy.justReleased(UP_BUTTON) || arduboy.justReleased(DOWN_BUTTON)) && clutchCounter == 

    if (!arduboy.pressed(A_BUTTON) && clutchCounter == 0  /*&& !arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON)*/ && arduboy.everyXFrames(FRAME_RATE_16)) { if (!player.decelerate()) allowChangeGears = true; }

    if (clutchCounter > 0) clutchCounter--;


  // Increase time of day ..

  level.incTime();

}
