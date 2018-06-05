#pragma once

#include "../utils/Enums.h"
#include "FixedPoints.h"
#include "FixedPointsCommon.h"

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

    ImageSize getImageSize();
    uint8_t getImageWidth();


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
}

void OtherCar::setYDelta(SQ7x8 val) {
  _yDelta = val;
}

void OtherCar::setActive(bool val) {
  _active = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

ImageSize OtherCar::getImageSize() {

  switch (_y.getInteger()) {

    case  0 ... 20:   return ImageSize::Small;
    case 21 ... 40:   return ImageSize::Medium;
    default:          return ImageSize::Large;

  }

}

uint8_t OtherCar::getImageWidth() {

  switch (_y.getInteger()) {

    case  0 ... 20:   return 11;
    case 21 ... 40:   return 16;
    default:          return 20;

  }

}
