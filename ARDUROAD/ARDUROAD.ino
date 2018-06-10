#include "src/utils/Arduboy2Ext.h"
#include "src/images/Images.h"
#include "src/fonts/Font4x6.h"
#include "src/utils/Enums.h"
#include "src/utils/Level.h"
#include "src/entity/Entities.h"
#include "src/utils/Utils.h"
#include "src/utils/EEPROM_Utils.h"
#include <FixedPoints.h>
#include <FixedPointsCommon.h>
#include "src/utils/FadeEffects.h"

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
uint8_t alternate = 0;

GameState gameState = GameState::VSBoot;

Level level;
Player player;
OtherCar car0;
OtherCar car1;
OtherCar car2;
OtherCar car3;
OtherCar *otherCarsOnly[] = { &car0, &car1, &car2, &car3 };
Base *allCars[] = { &car0, &car1, &car2, &car3, &player };

FadeInEffect fadeInEffect;
HighScore highScore;
uint8_t horizonIncrement = 0;
OtherCars otherCars(otherCarsOnly, allCars);

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
  arduboy.setFrameRate(50);

  player.setY(39);

  EEPROM_Utils::initEEPROM(false);
  
}

void loop() {

  if (!arduboy.nextFrameDEV()) return;

  arduboy.pollButtons();

  switch (gameState) {

    case GameState::VSBoot:
      vsBoot();
      break;

    case GameState::SplashScreen:
      splashScreen();
      break;

    case GameState::Credits:
      Credits();
      break;

    case GameState::PlayGame:
      playGame();
      
      break;

    case GameState::GameOver_Init:
      gameState = GameState::GameOver;
      fadeInEffect.reset();
//      sound.tones(end_of_game);
//      arduboy.setRGBled(0, 0, 0);
      // break; Fall-through intentional.
   
    case GameState::GameOver:
      GameOver();
      break;

    case GameState::SaveScore:
      highScore.reset();
      highScore.setSlotNumber(EEPROM_Utils::saveScore(player.getOdometer(), player.getCarsPassed()));
      gameState = GameState::HighScore;
      fadeInEffect.reset();
      // break; Fall-through intentional.

    case GameState::HighScore:
      HighScore();
      break;

  }

  if (gameState == GameState::PlayGame) {
    arduboy.displayWithBackground(level.getTimeOfDay(), level.getHorizonY(), level.getBand());
  }
  else {
    arduboy.display(true);
  }

}
