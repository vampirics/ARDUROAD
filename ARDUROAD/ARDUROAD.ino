#include "src/utils/Arduboy2Ext.h"
#include "src/images/Images.h"
#include "src/fonts/Font4x6.h"
#include "src/utils/Game.h"
#include "src/utils/Enums.h"
#include "src/utils/Level.h"
#include "src/entity/Player.h"
#include <ArduboyTones.h>
 
Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Font4x6 font4x6 = Font4x6();
Sprites sprite;

uint8_t fadeWidth;
uint8_t radioStation = 0;
uint8_t mainCarFrame = 0;

Level level;
Game game;
Player player;

uint8_t horizonIncrement = 0;

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

  game.setState(GameState::VSBoot);

}



void loop() {

  if (!arduboy.nextFrameDEV()) return;

  arduboy.clear();
  arduboy.pollButtons();

  switch (game.getState()) {

    case GameState::VSBoot:
      vsBoot();
      break;

    case GameState::SplashScreen:
      splashScreen();
      break;

    case GameState::PlayGame:
      playGame();
      break;

  }

  arduboy.display();

}
