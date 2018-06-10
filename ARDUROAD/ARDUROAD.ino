#include "src/utils/Arduboy2Ext.h"
#include "src/images/Images.h"
#include "src/fonts/Font4x6.h"
#include "src/utils/Game.h"
#include "src/utils/Enums.h"
#include "src/utils/Level.h"
#include "src/entity/Player.h"
#include "src/entity/OtherCars.h"
#include "src/entity/OtherCar.h"
#include "src/utils/Utils.h"
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#ifdef USE_ARDUBOYTONES
#include <ArduboyTones.h>
#endif

#ifdef USE_ATMLIB
#include "song.h"
#include <ATMlib.h>
#endif

Arduboy2Ext arduboy;
Font4x6 font4x6 = Font4x6();
Sprites sprite;

#ifdef USE_ARDUBOYTONES
ArduboyTones sound(arduboy.audio.enabled);
#endif

#ifdef USE_ATMLIB
ATMsynth ATM;
#endif

uint8_t fadeWidth;
uint8_t radioStation = 0;
uint8_t mainCarFrame = 0;
uint8_t previousRadioStation;
uint8_t introDelay = 0;

Level level;
Game game;
Player player;

uint8_t horizonIncrement = 0;
OtherCars otherCars;

void RenderScreen(/*Player *player, Enemy *enemies*/);


// ----------------------------------------------------------------------------
//  Setup
//
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.audio.begin();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(60);

  game.setState(GameState::VSBoot);

}



void loop() {

  if (!arduboy.nextFrameDEV()) return;

  arduboy.pollButtons();

  switch (game.getState()) {

    case GameState::VSBoot:
      arduboy.clear();
      vsBoot();
      arduboy.display();
      break;

    case GameState::SplashScreen:
      arduboy.clear();
      splashScreen();
      arduboy.display();
      break;

    case GameState::Credits:
      arduboy.clear();
      Credits();
      arduboy.display();
      break;

    case GameState::PlayGame:
      playGame();
      arduboy.displayWithBackground(level.getTimeOfDay(), level.getHorizonY(), level.getBand());
      break;

  }


}
