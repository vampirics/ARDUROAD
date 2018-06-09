#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Enums.h"
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

class OtherCar {

  public: 

    OtherCar() {};
  
    // Properties ..

    int8_t getX();
    SQ7x8 getY();
    SQ7x8 getYDelta();
    bool isActive();

    void setX(int8_t val);
    void setY(SQ7x8 val);
    void setYDelta(SQ7x8 val);
    void setActive(bool val);


    // Methods ..

    bool isVisible(TimeOfDay timeOfDay);
    ImageSize getImageSize();
    uint8_t getImageWidthHalf();
    uint8_t getYOffset();
    uint8_t getYDisplay();
    int8_t incY(SQ7x8 val);

  private:

    int8_t _x;
    SQ7x8 _y;
    SQ7x8 _yDelta;
    bool _active;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

int8_t OtherCar::getX() {
  return _x;
}

SQ7x8 OtherCar::getY() {
  return _y;
}

SQ7x8 OtherCar::getYDelta() {
  return _yDelta;
}

bool OtherCar::isActive() {
  return _active;
}

void OtherCar::setX(int8_t val) {
  _x = val;
}

void OtherCar::setY(SQ7x8 val) {

  _y = val;

  int8_t y = _y.getInteger();

  if (y < OTHER_CAR_Y_MIN || y > OTHER_CAR_Y_MAX) {
    _active = false;
  }

}

void OtherCar::setYDelta(SQ7x8 val) {
  _yDelta = val;
}

void OtherCar::setActive(bool val) {
  _active = val;
}

int8_t OtherCar::incY(SQ7x8 val) {

  _y = _y + val;

  int8_t y = _y.getInteger();

  if (y < OTHER_CAR_Y_MIN || y > OTHER_CAR_Y_MAX) {
    _active = false;
  }

  return y;

}

//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

ImageSize OtherCar::getImageSize() {

  switch (_y.getInteger()) {

    case DIST_6_BEGIN ... DIST_6_END:   return ImageSize::Disappearing;
    case DIST_5_BEGIN ... DIST_5_END:   return ImageSize::Minute;
    case DIST_4_BEGIN ... DIST_4_END:   return ImageSize::Tiny;
    case DIST_3_BEGIN ... DIST_3_END:   return ImageSize::Small;
    case DIST_2_BEGIN ... DIST_2_END:   return ImageSize::Medium;
    default:                            return ImageSize::Large;

  }

}

uint8_t OtherCar::getImageWidthHalf() {

  switch (_y.getInteger()) {

    case DIST_6_BEGIN ... DIST_6_END:   return 4;
    case DIST_5_BEGIN ... DIST_5_END:   return 6;
    case DIST_4_BEGIN ... DIST_4_END:   return 8;
    case DIST_3_BEGIN ... DIST_3_END:   return 12;
    case DIST_2_BEGIN ... DIST_2_END:   return 15;
    default:                            return 20;

  }

}

uint8_t OtherCar::getYOffset() {

  switch (_y.getInteger()) {

    case DIST_6_BEGIN ... DIST_6_END:   return 8;
    case DIST_5_BEGIN ... DIST_5_END:   return 7;
    case DIST_4_BEGIN ... DIST_4_END:   return 6;
    case DIST_3_BEGIN ... DIST_3_END:   return 5;
    case DIST_2_BEGIN ... DIST_2_END:   return 3;
    default:                            return 0;

  }

}


uint8_t OtherCar::getYDisplay() {

  return _y.getInteger() + getYOffset();

}

bool OtherCar::isVisible(TimeOfDay timeOfDay) {
//return (_y.getInteger() > DIST_6_BEGIN && _y.getInteger() < 64);
  switch (timeOfDay) {

    case TimeOfDay::Dawn:
    case TimeOfDay::Dusk:
      return (_y.getInteger() > DIST_6_BEGIN_DUSK && _y.getInteger() < 64);

    case TimeOfDay::Day:
      return (_y.getInteger() > DIST_6_BEGIN_DAY && _y.getInteger() < 64);
    
    case TimeOfDay::Night:
      return (_y.getInteger() > DIST_6_BEGIN_NIGHT && _y.getInteger() < 64);

  }

  return true;

}