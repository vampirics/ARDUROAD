#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Enums.h"
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

class Base {

  public: 

    Base(uint8_t id) { _id = id; };
    
  
    // Properties ..

    int8_t getX();
    uint8_t getId();
    SQ7x8 getY();

    void setX(int8_t val);
    void setY(SQ7x8 val);

  protected:

    uint8_t _id;
    int8_t _x;
    SQ7x8 _y;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

uint8_t Base::getId() {
  return _id;
}

int8_t Base::getX() {
  return _x;
}

SQ7x8 Base::getY() {
  return _y;
}

void Base::setX(int8_t val) {
  _x = val;
}

void Base::setY(SQ7x8 val) {
  _y = val;
}
