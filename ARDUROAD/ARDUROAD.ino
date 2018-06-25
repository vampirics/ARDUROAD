#include "src/utils/Arduboy2Ext.h"
#include "src/images/Images.h"
//#include "src/fonts/Font4x6.h"
#include "src/fonts/Fonts.h"
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
#include "src/songs/song.h"
#include <ATMlib.h>
#endif

#include "src/songs/Songs.h"


Arduboy2Ext arduboy;
//Font4x6 font4x6 = Font4x6();
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
Player player(PLAYER_INDEX);
OtherCar car0(1);
OtherCar car1(2);
OtherCar car2(3);
OtherCar car3(4);
OtherCar *carControllerOnly[] = { &car0, &car1, &car2, &car3 };
Base *allCars[] = { &car0, &car1, &car2, &car3, &player };

FadeOutEffect fadeOutEffect;
FadeInEffect fadeInEffect;
HighScore highScore;
//uint8_t horizonIncrement = 0;
UQ8x8 horizonIncrement = 0;
CarController carController(carControllerOnly, allCars);
uint8_t carCounterBlink = 0;

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
  arduboy.setFrameRate(75);

  player.setY(39);
  player.setTransmissionType(TransmissionType::Automatic);

  EEPROM_Utils::initEEPROM(false);
  
  fadeOutEffect.reset(0, HEIGHT, 1);
  

}

void loop() {

  if (!arduboy.nextFrameDEV()) return;

  arduboy.pollButtons();

  switch (gameState) {

    case GameState::VSBoot:
      vsBoot();
      break;

    case GameState::SplashScreen_Init:
      arduboy.setFrameRate(75);
      gameState = GameState::SplashScreen;
      fadeInEffect.reset(0, HEIGHT, 1);
      // break; Fall-through intentional.

    case GameState::SplashScreen:
      splashScreen();
      break;

    case GameState::Credits:
      Credits();
      break;

    case GameState::PlayGame_Init:
      arduboy.setFrameRate(50);
      gameState = GameState::PlayGame_StartOfDay;
      player.reset();
      player.setX(64 - PLAYER_WIDTH_HALF);
      player.setXOffset(0);
      player.setCarsPassedInit(50);
      carCounterBlink = 0;
      // break; Fall-through intentional.

    case GameState::PlayGame_StartOfDay:
    case GameState::PlayGame:
    case GameState::PlayGame_EndOfPlay:
      playGame();
      break;

     case GameState::GameOver_Init:
      gameState = GameState::GameOver;
      arduboy.setRGBled(0, 0, 0);
      fadeInEffect.reset(14, 38, 2);
      // break; Fall-through intentional.
   
    case GameState::GameOver:
      playGame();
      break;

    case GameState::SaveScore:
      highScore.reset();
      highScore.setSlotNumber(EEPROM_Utils::saveScore(player.getOdometer(), level.getDayCount()));
      gameState = GameState::HighScore;
      fadeInEffect.reset(0, HEIGHT, 1);
      // break; Fall-through intentional.

    case GameState::HighScore:
      HighScore();
      break;

  }

  switch (gameState) {

    case GameState::PlayGame:
    case GameState::PlayGame_StartOfDay:
    case GameState::PlayGame_EndOfPlay:
    case GameState::GameOver_Init:
    case GameState::GameOver:
      arduboy.displayWithBackground(level.getTimeOfDay(), level.getHorizonY(), level.getBand());
      break;

    default:
      arduboy.display(true);
      break;

  }

}
