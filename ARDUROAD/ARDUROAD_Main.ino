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

      level.incHorizon(player.getYDelta() > 0 ? 1 : -1);
      horizonIncrement = 0;
      
    }

    horizonIncrement++;



  // Turn ?

  if (level.getTurn() == 0) {

    level.setTurn(random(12, 60), random(0, 3));

  }


    RenderScreen();
    level.turn();

  //if (player.getStatus() == PlayerStatus::Active && gameState != GameState::Paused) {

    if (arduboy.pressed(DOWN_BUTTON))     { if (player.decYDelta()) horizonIncrement = 0; }
    if (arduboy.pressed(UP_BUTTON))       { if (player.incYDelta()) horizonIncrement = 0; }
    if (arduboy.pressed(LEFT_BUTTON))     { player.decX(); }
    if (arduboy.pressed(RIGHT_BUTTON))    { player.incX(); }

    if (!arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(UP_BUTTON) && arduboy.everyXFrames(FRAME_RATE_16)) { player.decelerate(); }

  //}



//  }

}