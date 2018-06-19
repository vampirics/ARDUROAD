#include "src/utils/Arduboy2Ext.h"

void vsBoot() {

  // Vsoft logo display
  Sprites::drawOverwrite(46, 8, bootlogo, 0);

  if (!fadeOutEffect.isComplete()) {

    fadeOutEffect.draw(arduboy);
    fadeOutEffect.update();

  }

  if (fadeOutEffect.isComplete()) gameState = GameState::SplashScreen_Init;

}

void splashScreen() {

  Sprites::drawOverwrite(0, 0, SplashScreen, 0);

//  font4x6.setCursor(74, 5);
  radioMusic();

  // switch (radioStation) {

  //   case 0:
  //     font4x6.print(F("RADIO OFF"));
  //     break;

  //   case 1:
  //     font4x6.print(F("ARDX 89.9"));
  //     arduboy.drawLine(103, 25, 103, 28, WHITE);
  //     break;

  //   case 2:
  //     font4x6.print(F("ROCK 94.6"));
  //     arduboy.drawLine(113, 25, 113, 28, WHITE);
  //     break;

  // }

  if (!fadeInEffect.isComplete()) {

    fadeInEffect.draw(arduboy);
    fadeInEffect.update();

  }

  if (arduboy.justPressed(LEFT_BUTTON) && radioStation > 0) {
    radioStation--;
    #ifdef USE_ARDUBOYTONES
    sound.tone(NOTE_C3,50, NOTE_D2,50, NOTE_E1,50);
    #endif
  }

  if (arduboy.justPressed(RIGHT_BUTTON) && radioStation < 2) {
    radioStation++;
    #ifdef USE_ARDUBOYTONES
    sound.tone(NOTE_C3,50, NOTE_D2,50, NOTE_E1,50);
    #endif
  }

  if (arduboy.justPressed(A_BUTTON)) { player.setTransmissionType(TransmissionType::Automatic); gameState = GameState::PlayGame_Init; }
  if (arduboy.justPressed(B_BUTTON)) { player.setTransmissionType(TransmissionType::Manual); gameState = GameState::PlayGame_Init;/*gameState = GameState::Credits;*/ }
  
}

void radioMusic() 
{
  if(previousRadioStation != radioStation)
  {
    if (radioStation == 1)
    {
      #ifdef USE_ATMLIB
      ATM.play(music1);
      #endif
      #ifdef USE_ARDUBOYTONES
      sound.tones(song2small); 
      #endif
    }
    if (radioStation == 2)
    {
      #ifdef USE_ATMLIB
      ATM.play(music2);
      #endif
      #ifdef USE_ARDUBOYTONES
      sound.tones(song2); 
      #endif

    }
    if (radioStation == 0)
    {
      #ifdef USE_ATMLIB
      ATM.stop();
      #endif
    }
    previousRadioStation = radioStation;
  }
}

