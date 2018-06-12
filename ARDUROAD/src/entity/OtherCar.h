#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Enums.h"
#include "Base.h"
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

class OtherCar : public Base {

  public: 

    OtherCar(uint8_t id) : Base(id) {};
  

    // Properties ..

    bool isActive();
    uint8_t getTurnLength();
    Direction getXDelta();

    void setY(SQ7x8 val);
    void setXDelta(Direction val);
    void setActive(bool val);
    void setTurnLength(uint8_t val);
    void incX();
    void decX();


    // Methods ..

    bool isVisible(TimeOfDay timeOfDay);
    ImageSize getImageSize();
    uint8_t getImageWidthHalf();
    uint8_t getYOffset();
    uint8_t getYDisplay();
    int8_t incY(SQ7x8 val);
    uint8_t decTurnLength();

  private:

    bool _active;
    uint8_t _turnLength;
    Direction _xDelta;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

bool OtherCar::isActive() {
  return _active;
}

uint8_t OtherCar::getTurnLength() {
  return _turnLength;
}

Direction OtherCar::getXDelta() {
  return _xDelta;
}

void OtherCar::setTurnLength(uint8_t val) {
  _turnLength = val;
}

void OtherCar::setXDelta(Direction val) {
  _xDelta = val;
}

void OtherCar::setY(SQ7x8 val) {

  _y = val;

  int8_t y = _y.getInteger();

  if (y < OTHER_CAR_Y_MIN || y > OTHER_CAR_Y_MAX) {
    _active = false;
  }

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

void OtherCar::incX() {
  if (_x < OTHER_CAR_X_MAX) _x++;
}

void OtherCar::decX() {
  if (_x > OTHER_CAR_X_MIN) _x--;
}

uint8_t OtherCar::decTurnLength() {
  return --_turnLength;
}

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