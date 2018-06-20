#include "src/utils/Arduboy2Ext.h"


bool allowChangeGears = true;
bool showGauges = true;
uint8_t clutchCounter = 0;

void playGame() {

  uint8_t speed = player.getYDelta();
  uint8_t frameDelay = player.getFrameDelay();

  if (frameDelay != PLAYER_NO_MOVEMENT && (player.getTransmissionType() == TransmissionType::Automatic || clutchCounter > 0 || speed > 1 || (speed == 1 && arduboy.pressed(A_BUTTON)))) { 

    if (horizonIncrement >= frameDelay) {

      level.incHorizonY(&player);
      horizonIncrement = horizonIncrement - frameDelay;
      
    }

    horizonIncrement = horizonIncrement + 10;


    // Move car to outside of curve ..
    
    if (arduboy.isFrameCount(frameDelay / 3, 0)) {

      int8_t curve0 = level.getCurve(0);
      int8_t curve6 = level.getCurve(6);

      if (curve0 != 0 && curve6 != 0) {

        if (curve0 > 0) player.decX();
        if (curve0 < 0) player.incX();

      }

    }

  }


  // Update positions of other cars ..

  if (arduboy.isFrameCount(3, 0)) {

    carController.updatePositions(&player, speed);

  }


  RenderScreen(speed);


  // Move road and horizon scenery horizontally .. 

  if (arduboy.isFrameCount(FRAME_COUNT_HORIZON_X * (5 - speed))) {
    level.moveHorizontally(&arduboy, speed);
  }


  // Launch another car?
  
  if (gameState == GameState::PlayGame) {

    OtherCar *otherCar = carController.getInactiveCar();

    if (otherCar != nullptr) {

      if (frameDelay < 20) {
        
        OtherCar *otherCarLowestY = carController.getActiveCar_LowestY();

        if (otherCarLowestY == nullptr || otherCarLowestY->getY() > 20) {
          
          otherCar->setActive(true);
          otherCar->setX(random(OTHER_CAR_X_MIN, OTHER_CAR_X_MAX + 1));
          otherCar->setYDelta(randomSFixed<7,8>(LAUNCH_SLOWER_SPEED, LAUNCH_FASTER_SPEED));
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
          otherCar->setYDelta(randomSFixed<7,8>(LAUNCH_SLOWER_SPEED, LAUNCH_FASTER_SPEED));
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
  

  // Handle player's keypresses ..

  if (gameState == GameState::PlayGame || gameState == GameState::PlayGame_StartOfDay) {
    
    if (arduboy.pressed(A_BUTTON) && speed > 0) { 

      if (arduboy.everyXFrames(2)) {
        mainCarFrame = !mainCarFrame;
      }

      if (player.getTransmissionType() == TransmissionType::Manual) allowChangeGears = true;

    }

    if (arduboy.pressed(LEFT_BUTTON) && speed > 0)     { player.decX(); }
    if (arduboy.pressed(RIGHT_BUTTON) && speed > 0)    { player.incX(); }

    bool onRoadsEdge = player.onRoadsEdge() & (frameDelay < PLAYER_MAX_SPEED_ON_EDGE);

    if (player.getTransmissionType() == TransmissionType::Automatic) {

      if (!onRoadsEdge) {

        if (allowChangeGears && arduboy.pressed(A_BUTTON)) { 
          if (player.incSpeed(false)) horizonIncrement = 0;
          allowChangeGears = false; 
          clutchCounter = TRANS_AUTO_COUNTDOWN; 
        }

        if (arduboy.justPressed(B_BUTTON)) { 
          if (player.decSpeed()) horizonIncrement = 0;
          allowChangeGears = false; 
          clutchCounter = 0;  
        }

      }

      if ((onRoadsEdge || (!arduboy.pressed(A_BUTTON) && !arduboy.pressed(B_BUTTON))) && arduboy.everyXFrames(FRAME_RATE_16)) { 
        if (player.decSpeed()) horizonIncrement = 0; 
        allowChangeGears = false; 
        clutchCounter = TRANS_AUTO_COUNTDOWN_SHORT;  
      }

      if (clutchCounter > 0)    clutchCounter--; 
      if (clutchCounter == 0)   allowChangeGears = true;

    }
    else {

      if (clutchCounter == 0) {

        if (!onRoadsEdge) {
  
          if (arduboy.pressed(B_BUTTON) && arduboy.justPressed(UP_BUTTON) && !arduboy.pressed(A_BUTTON)) {
            if (player.incSpeed(true)) horizonIncrement = 0;
            clutchCounter = TRANS_MANUAL_COUNTDOWN;
          }

          if (arduboy.pressed(B_BUTTON) && arduboy.justPressed(DOWN_BUTTON) && !arduboy.pressed(A_BUTTON)) {
            if (player.decSpeed()) horizonIncrement = 0;
            clutchCounter = TRANS_MANUAL_COUNTDOWN;
          }

          if (speed > 0 && arduboy.pressed(A_BUTTON) && !arduboy.pressed(B_BUTTON)) {
            if (player.incSpeed(false)) horizonIncrement = 0;
            clutchCounter = TRANS_MANUAL_COUNTDOWN;
          }

        }

        if ((onRoadsEdge || !arduboy.pressed(A_BUTTON)) && arduboy.everyXFrames(FRAME_RATE_16)) { 
          if (player.decSpeed()) horizonIncrement = 0; 
        }

      }

      if (clutchCounter > 0)  {
        clutchCounter--;
      }

    }

  }
  else {


    // Decelerate if end of game ..

    if (arduboy.everyXFrames(FRAME_RATE_16)) { 
      
      // player.decYDelta();
      player.decSpeed();
      
    }

    if (gameState == GameState::GameOver && arduboy.justPressed(A_BUTTON)) { gameState = GameState::SaveScore; }

  }



  // Increase start of day counter ..

  if (arduboy.isFrameCount(24, 0)) {

    if (gameState == GameState::PlayGame && level.getTimeLow()) {
     
      carCounterBlink++;

    }

    if (gameState == GameState::PlayGame_StartOfDay) {
     
      carCounterBlink++;
      if (carCounterBlink == 10) gameState = GameState::PlayGame;

    }

    if (gameState == GameState::PlayGame_EndOfPlay) {

      carCounterBlink++;
      if (carCounterBlink == 20) {
        
        gameState = GameState::GameOver_Init;

      }

    }

  }


  // Increase time of day ..  if a new day has

  if (gameState != GameState::PlayGame_EndOfPlay && level.incTime()) {

    if (player.getCarsPassed() > 0) {
      
      gameState = GameState::PlayGame_EndOfPlay;

    }

  }

}
