#pragma once

#include "Arduboy2Ext.h"

// How fast should the ground move ?  1 = Slow, 2 = Medium, 3 = Fast - I think 2 is the most appropriate.

//#define DEBUG_CURVES
#define _USE_ATMLIB
#define USE_ARDUBOYTONES
#define GEARBOX

static const uint8_t HORIZON_COL_COUNT            = 7;
static const uint8_t HORIZON_ROW_COUNT            = 5;
static const uint8_t HORIZON_OFFSET               = 8;

static const uint8_t NUMBER_OF_OTHER_CARS         = 5;


static const uint8_t FRAME_RATE_1                 = 1;
static const uint8_t FRAME_RATE_2                 = 2;
static const uint8_t FRAME_RATE_3                 = 3;
static const uint8_t FRAME_RATE_4                 = 4;
static const uint8_t FRAME_RATE_8                 = 8;
static const uint8_t FRAME_RATE_12                = 12;
static const uint8_t FRAME_RATE_16                = 16;

static const uint8_t FRAME_COUNT_HORIZON_X        = 3;


static const int8_t DIST_6_BEGIN                  = -5;
static const int8_t DIST_6_END                    = -2;
static const int8_t DIST_5_BEGIN                  = -1;
static const int8_t DIST_5_END                    = 4;
static const int8_t DIST_4_BEGIN                  = 5;
static const int8_t DIST_4_END                    = 11;
static const int8_t DIST_3_BEGIN                  = 12;
static const int8_t DIST_3_END                    = 17;
static const int8_t DIST_2_BEGIN                  = 18;
static const int8_t DIST_2_END                    = 32;

static const int8_t OTHER_CAR_Y_MIN               = -50;
static const int8_t OTHER_CAR_Y_MAX               = 100;


// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}


// ----------------------------------------------------------------------------
//  Enumerations .. 
//
enum class GameState : uint8_t {

  VSBoot,
  SplashScreen,
  PlayGame,

};

enum class TimeOfDay : uint8_t {

  Dawn,
  Day,
  Night,

};

enum class ImageSize : uint8_t {

  Large,
  Medium,
  Small,
  Tiny,
  Minute,
  Disappearing

};

enum class Direction : int8_t {

  Left = -1,
  Straight = 0,
  Right = 1,

};

