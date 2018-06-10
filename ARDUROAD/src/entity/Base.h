#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Enums.h"
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

class Base {

  public: 

    Base() {};
  
    // Properties ..

    int8_t getX();
    SQ7x8 getY();
    int8_t getXDelta();
    SQ7x8 getYDelta();

    void setX(int8_t val);
    void setY(SQ7x8 val);
    void setXDelta(int8_t val);
    void setYDelta(SQ7x8 val);

  protected:

    int8_t _x;
    SQ7x8 _y;
    int8_t _xDelta;
    SQ7x8 _yDelta;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

int8_t Base::getX() {
  return _x;
}

SQ7x8 Base::getY() {
  return _y;
}

SQ7x8 Base::getYDelta() {
  return _yDelta;
}

int8_t Base::getXDelta() {
  return _xDelta;
}

void Base::setX(int8_t val) {
  _x = val;
}

void Base::setY(SQ7x8 val) {
  _y = val;
}

void Base::setXDelta(int8_t val) {
  _xDelta = val;
}

void Base::setYDelta(SQ7x8 val) {
  _yDelta = val;
}