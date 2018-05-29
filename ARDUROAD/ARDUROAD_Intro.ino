#include "src/utils/Arduboy2Ext.h"


// ----------------------------------------------------------------------------
//  Reset the fade effect .. 
//
void resetFade() {
  fadeWidth = 0;
}

// ----------------------------------------------------------------------------
//  Reset the fade in effect .. 
//
void resetFadeIn() {
  fadeWidth = WIDTH;
}


// ----------------------------------------------------------------------------
//  Fade In function .. 
//
bool fadeIn() {

  for (uint8_t i = 0; i < (HEIGHT / 2); ++i)
  {
    arduboy.drawFastHLine(0, (i * 2), fadeWidth, BLACK);
    arduboy.drawFastHLine((WIDTH - fadeWidth), (i * 2) + 1, fadeWidth, BLACK);
  }

  // If fade isn't complete, decrease the counter
  if (fadeWidth > 0) 
  {
    fadeWidth = fadeWidth - 4;
    return false;
  }
  else 
  {
    return true;
  }

}


// ----------------------------------------------------------------------------
//  Fade Out function .. 
//
bool fadeOut() 
{

  for (uint8_t i = 0; i < (HEIGHT / 2); ++i) 
  {
    arduboy.drawFastHLine(0, (i * 2), fadeWidth, BLACK);
    arduboy.drawFastHLine((WIDTH - fadeWidth), (i * 2) + 1, fadeWidth, BLACK);
  }

  // If fade isn't complete, increase the counter
  if(fadeWidth < WIDTH) 
  {
    ++fadeWidth;
    ++fadeWidth;
    return false;
  }
  else 
  {
    return true;
  }
  
}

void vsBoot() {

  // Vsoft logo display
  arduboy.drawBitmap(0, 0, bootlogo, 128, 64, WHITE);

  if (fadeOut()) {
    resetFade();
    resetFadeIn();
    game.setState(GameState::SplashScreen);
  }
}

void splashScreen() 
{

  arduboy.drawBitmap(0, 0, SplashScreen, 128, 64, WHITE);
  fadeIn();
  font4x6.setCursor(74, 5);
  radioMusic();
  if (radioStation == 0)
  { 
    font4x6.print(F("RADIO OFF"));
    station = 0;
  }
    else if (radioStation == 1)
    { 
      font4x6.print(F("ARDX 89.9"));
      arduboy.drawLine(103, 25, 103, 28, WHITE);
      station = 1;  
    }
      else if (radioStation == 2)
      { 
        font4x6.print(F("ROCK 94.6"));
        arduboy.drawLine(113, 25, 113, 28, WHITE);
        station = 2;
      }

  if (arduboy.justPressed(LEFT_BUTTON) && radioStation > 0)
  {
    radioStation--;
    sound.tone(NOTE_C3,50, NOTE_D2,50, NOTE_E1,50);
  }

  if (arduboy.justPressed(RIGHT_BUTTON) && radioStation < 2)
  {
    radioStation++;
    sound.tone(NOTE_C3,50, NOTE_D2,50, NOTE_E1,50);
  }

  if (arduboy.justPressed(A_BUTTON)) { game.setState(GameState::PlayGame); }
}

void radioMusic() 
{
  if(previousRadioStation != radioStation)
  {
    if (radioStation == 1)
    {
      ATM.play(music1);
    }
    if (radioStation == 2)
    {
      ATM.play(music2);
    }
    if (radioStation == 0)
    {
      ATM.stop();
    }
    previousRadioStation = radioStation;
  }
}

