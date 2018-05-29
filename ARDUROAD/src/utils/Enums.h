#pragma once

#include "Arduboy2Ext.h"

// How fast should the ground move ?  1 = Slow, 2 = Medium, 3 = Fast - I think 2 is the most appropriate.

#define _USE_ATMLIB
#define USE_ARDUBOYTONES
#define GROUND_SPEED 3

static const uint8_t HORIZON_COL_COUNT                    = 7;
static const uint8_t HORIZON_ROW_COUNT                    = 5;
static const uint8_t HORIZON_OFFSET                       = 9;


static const uint8_t FRAME_RATE_1                         = 1;
static const uint8_t FRAME_RATE_2                         = 2;
static const uint8_t FRAME_RATE_3                         = 3;
static const uint8_t FRAME_RATE_4                         = 4;
static const uint8_t FRAME_RATE_8                         = 8;
static const uint8_t FRAME_RATE_12                        = 12;
static const uint8_t FRAME_RATE_16                        = 16;

static const uint8_t FRAME_COUNT_HORIZON_X                = 3;



// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}

enum class GameState : uint8_t {

  VSBoot,
  SplashScreen,
  PlayGame,

};