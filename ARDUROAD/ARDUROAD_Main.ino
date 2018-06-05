#include "src/utils/Arduboy2Ext.h"

void playGame() {


    // Update the ground's position ..

#if GROUND_SPEED == 1
  const uint8_t speedLookup[] = {0, 16, 8, 0, 4};
#endif
#if GROUND_SPEED == 2
  const uint8_t speedLookup[] = {0, 12, 6, 0, 3};
#endif
#if GROUND_SPEED == 3
  const uint8_t speedLookup[] = {0, 8, 4, 0, 2};
#endif

//  if (gameState != GameState::Paused) {

    uint8_t speed = speedLookup[absT(player.getYDelta())];

    if (horizonIncrement == speed) {

      level.incHorizonY(player.getYDelta() > 0 ? 1 : -1);
      horizonIncrement = 0;
      
    }

    horizonIncrement++;



  // Turn ?



    RenderScreen();

    if (arduboy.isFrameCount(FRAME_COUNT_HORIZON_X)) {
      level.move(&arduboy);
    }




  // Launch another car?

  if (random(0, 12) == 0 && otherCars.getActiveCars() < NUMBER_OF_OTHER_CARS) {

    OtherCar *otherCar = otherCars.getInactiveCar();
//Serial.println("launch");
    otherCar->setActive(true);
    otherCar->setX(random(-20,20));
    otherCar->setY(0);
    otherCar->setYDelta(randomSFixed<7,8>(1, 2));

  }



  //if (player.getStatus() == PlayerStatus::Active && gameState != GameState::Paused) {

    if (arduboy.pressed(B_BUTTON))     { if (player.decYDelta()) horizonIncrement = 0; }
    if (arduboy.pressed(A_BUTTON))     { 
                                          if (player.incYDelta()) horizonIncrement = 0; 
                                          if (arduboy.everyXFrames(2)) {// when running at 60fps
                                            mainCarFrame = !mainCarFrame;
                                          }
                                        }
    if (arduboy.pressed(LEFT_BUTTON))      { player.decX(); }
    if (arduboy.pressed(RIGHT_BUTTON))    { player.incX(); }

    if (!arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(FRAME_RATE_16)) { player.decelerate(); }

  //}



//  }

}
