#pragma once

#include "Arduboy2Ext.h"

#define _USE_ATMLIB
#define USE_ARDUBOYTONES
#define _THICK_LINES

static const uint8_t HORIZON_COL_COUNT            = 7;
static const uint8_t HORIZON_ROW_COUNT            = 5;
static const uint8_t HORIZON_OFFSET               = 8;

static const uint8_t NUMBER_OF_OTHER_CARS         = 4;
static const uint8_t NUMBER_OF_CARS_INC_PLAYER    = NUMBER_OF_OTHER_CARS + 1;

static const uint8_t FRAME_RATE_1                 = 1;
static const uint8_t FRAME_RATE_2                 = 2;
static const uint8_t FRAME_RATE_3                 = 3;
static const uint8_t FRAME_RATE_4                 = 4;
static const uint8_t FRAME_RATE_8                 = 8;
static const uint8_t FRAME_RATE_12                = 12;
static const uint8_t FRAME_RATE_16                = 16;

static const uint8_t FRAME_COUNT_HORIZON_X        = 3;

static const uint8_t HORIZON_HEIGHT_DAY           = 10;
static const uint8_t HORIZON_HEIGHT_DUSK          = 9;
static const uint8_t HORIZON_HEIGHT_NIGHT         = 15;

static const int8_t DIST_6_BEGIN                  = HORIZON_HEIGHT_DAY - 15;      // -5
static const int8_t DIST_6_BEGIN_DAY              = HORIZON_HEIGHT_DAY - 15;      // -5
static const int8_t DIST_6_BEGIN_DUSK             = HORIZON_HEIGHT_DUSK - 15;     // -6
static const int8_t DIST_6_BEGIN_NIGHT            = HORIZON_HEIGHT_NIGHT - 15;    // -0
static const int8_t DIST_6_END                    = -2;
static const int8_t DIST_5_BEGIN                  = -1;
static const int8_t DIST_5_END                    = 4;
static const int8_t DIST_4_BEGIN                  = 5;
static const int8_t DIST_4_END                    = 11;
static const int8_t DIST_3_BEGIN                  = 12;
static const int8_t DIST_3_END                    = 17;
static const int8_t DIST_2_BEGIN                  = 18;
static const int8_t DIST_2_END                    = 32;

static const uint8_t PLAYER_WIDTH                 = 44;
static const uint8_t PLAYER_WIDTH_HALF            = PLAYER_WIDTH / 2;

static const int8_t OTHER_CAR_X_MIN               = -37;
static const int8_t OTHER_CAR_X_MAX               = 37;
static const int8_t OTHER_CAR_Y_MIN               = -50;
static const int8_t OTHER_CAR_Y_MAX               = 100;
static const uint8_t OTHER_CAR_MAX_WIDTH          = 20;

static const int8_t LANE_WIDTH                    = 25;
static const int8_t OTHER_CAR_X_LANE_1_START      = -37;
static const int8_t OTHER_CAR_X_LANE_1_END        = OTHER_CAR_X_LANE_1_START + LANE_WIDTH - 1; // -37+25-1 = -13
static const int8_t OTHER_CAR_X_LANE_2_START      = OTHER_CAR_X_LANE_1_END + 1;                // -12
static const int8_t OTHER_CAR_X_LANE_2_END        = OTHER_CAR_X_LANE_2_START + LANE_WIDTH - 1; // -12+25-1 = 12
static const int8_t OTHER_CAR_X_LANE_3_START      = OTHER_CAR_X_LANE_2_END + 1;                // 12+1 = 13
static const int8_t OTHER_CAR_X_LANE_3_END        = OTHER_CAR_X_LANE_3_START + LANE_WIDTH - 1; // 13+25 = 38


static const int16_t TICKS_IN_A_PERIOD            = 500;
static const int16_t DIRT_CLOUD_MAX               = 15;
static const int16_t DIRT_CLOUD_DIVISOR           = 4;

static const uint8_t MAX_NUMBER_OF_SCORES         = 5;
static const uint8_t DO_NOT_EDIT_SLOT             = 255;


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
  SplashScreen_Init,
  SplashScreen,
  Credits,
  PlayGame_Init,
  PlayGame,
  GameOver_Init,  
  GameOver,  
  SaveScore,
  HighScore,

};

enum class CarType : uint8_t {

  Unknown,
  Player,
  OtherCar,

};

enum class TimeOfDay : uint8_t {

  Dawn,
  Day,
  Dusk,
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




// TimeOfDay ..

inline TimeOfDay operator++( TimeOfDay & c ) {

  c = static_cast<TimeOfDay>( (static_cast<uint8_t>(c) + 1) % 4 );
  return c;

}

inline TimeOfDay operator++( TimeOfDay & c, int ) {

  TimeOfDay result = c;
  ++c;
  return result;

}

inline TimeOfDay operator--( TimeOfDay & c ) {
 
  c = static_cast<TimeOfDay>( (static_cast<uint8_t>(c) - 1) % 4 );
  return c;

}

inline TimeOfDay operator--( TimeOfDay & c, int ) {

  TimeOfDay result = c;
  --c;
  return result;

}