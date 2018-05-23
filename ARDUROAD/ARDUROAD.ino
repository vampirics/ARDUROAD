#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Name.h"
#include "src/utils/Utils.h"
#include "Images.h"
#include "src/fonts/Font4x6.h"
#include "src/utils/Game.h"
#include <ArduboyTones.h>
 
Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Font4x6 font4x6 = Font4x6();
Sprites sprite;
Name name;

uint8_t state = 0;
uint8_t fadeWidth;
uint8_t radioStation = 0;

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

  name.clear();

}

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


void loop()
{

  if (!arduboy.nextFrame()) return;

  arduboy.clear();
  arduboy.pollButtons();
  arduboy.clear();

if (state == 0)  { vsBoot(); }
  else if (state == 1)  { splashScreen(); }
  
  
  arduboy.display();
}

void vsBoot()
{

  // Vsoft logo display
  arduboy.drawBitmap(0, 0, bootlogo, 128, 64, WHITE);

  if (fadeOut())
  {
    resetFade();
    resetFadeIn();
    state = 1;
  }
}

void splashScreen()
{

  arduboy.drawBitmap(0, 0, SplashScreen, 128, 64, WHITE);
  fadeIn();
  font4x6.setCursor(74, 5);
  if (radioStation == 0)
  { 
    font4x6.print("ARDX 89.9");
    arduboy.drawLine(103, 25, 103, 28, WHITE);
  }
    else if (radioStation == 1)
    { 
      font4x6.print("ROCK 94.6");
      arduboy.drawLine(113, 25, 113, 28, WHITE);;
    }
      else if (radioStation == 2)
      { 
        font4x6.print("RADIO OFF");
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
}
