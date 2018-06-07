#include "src/utils/Arduboy2Ext.h"

#ifdef GEARBOX
bool allowChangeGears = true;
#endif

void playGame() {


    // Update the ground's position ..

    const uint8_t speedLookup[] = {12, 6, 4, 2, 1};
    uint8_t playerYDelta = player.getYDelta();


//  if (gameState != GameState::Paused) {

    uint8_t gear = speedLookup[absT(playerYDelta)];


    if (gear > 1 || (gear == 1 && arduboy.pressed(A_BUTTON))) { 

      if (horizonIncrement == gear) {

        if (playerYDelta >= 1)  level.incHorizonY(1);
        horizonIncrement = 0;
        
      }

      horizonIncrement++;

    }

    if (arduboy.isFrameCount(3, 0)) {

      otherCars.updatePositions(playerYDelta);

    }

  // Turn ?



    RenderScreen(playerYDelta);

    if (arduboy.isFrameCount(FRAME_COUNT_HORIZON_X)) {
      level.move(&arduboy);
    }




  // Launch another car?

  if (random(0, 10) == 0 && otherCars.getActiveCars() < 1){//NUMBER_OF_OTHER_CARS) {

    if (horizonIncrement > 3) {

      OtherCar *otherCar = otherCars.getInactiveCar();
      otherCar->setActive(true);
//      otherCar->setX(random(-20,20));
      otherCar->setX(70);
      otherCar->setYDelta(randomSFixed<7,8>(1, 3));
      otherCar->setY(DIST_6_BEGIN);

    }
    else {

      OtherCar *otherCar = otherCars.getInactiveCar();
      otherCar->setActive(true);
//      otherCar->setX(random(-20,20));
      otherCar->setX(70);
      otherCar->setYDelta(randomSFixed<7,8>(1, 3));
      otherCar->setY(80);

    }




  }



  //if (player.getStatus() == PlayerStatus::Active && gameState != GameState::Paused) {

    #ifndef GEARBOX
    if (arduboy.pressed(B_BUTTON))     { if (player.decYDelta()) horizonIncrement = 0; }
    if (arduboy.pressed(A_BUTTON))     { 
                                          if (player.incYDelta()) horizonIncrement = 0; 
                                          if (arduboy.everyXFrames(2)) {// when running at 60fps
                                            mainCarFrame = !mainCarFrame;
                                          }
                                        }
    if (arduboy.pressed(LEFT_BUTTON))      { player.decX(); }
    if (arduboy.pressed(RIGHT_BUTTON))    { player.incX(); }
    if (arduboy.justPressed(UP_BUTTON))    { if (player.incYDelta()) horizonIncrement = 0; }
    if (arduboy.justPressed(DOWN_BUTTON))  { if (player.decYDelta()) horizonIncrement = 0; }

    if (!arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(FRAME_RATE_16)) { player.decelerate(); }
    #endif

    #ifdef GEARBOX

    if (arduboy.pressed(A_BUTTON))     { 
                                          if (arduboy.everyXFrames(2)) {// when running at 60fps
                                            mainCarFrame = !mainCarFrame;
                                          }
                                          allowChangeGears = true;
                                        }
    if (arduboy.pressed(LEFT_BUTTON))     { player.decX(); }
    if (arduboy.pressed(RIGHT_BUTTON))    { player.incX(); }
    if (allowChangeGears && !arduboy.pressed(A_BUTTON) && arduboy.justPressed(UP_BUTTON))    { if (player.incYDelta()) horizonIncrement = 0; allowChangeGears = false; }
    if (allowChangeGears && !!arduboy.pressed(A_BUTTON) && arduboy.justPressed(DOWN_BUTTON))  { if (player.decYDelta()) horizonIncrement = 0; allowChangeGears = false; }

    if (!arduboy.pressed(A_BUTTON) && !arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(FRAME_RATE_16)) { player.decelerate(); }

    #endif
  //}



//  }

}
