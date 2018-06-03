#pragma once

#include "../utils/Enums.h"

class OtherCar {

  public: 

    OtherCar() {};
  
    // Properties ..

    int8_t getX();
    uint8_t getY();
    bool isActive();

    void setX(int8_t val);
    void setY(uint8_t val);
    void setActive(bool val);


    // Methods ..

    ImageSize getImageSize();
    uint8_t getImageWidth();


  private:

    int8_t _x;
    uint8_t _y;
    bool _active;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

int8_t OtherCar::getX() {
  return _x;
}

uint8_t OtherCar::getY() {
  return _y;
}

bool OtherCar::isActive() {
  return _active;
}

void OtherCar::setX(int8_t val) {
  _x = val;
}

void OtherCar::setY(uint8_t val) {
  _y = val;
}

void OtherCar::setActive(bool val) {
  _active = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

ImageSize OtherCar::getImageSize() {

  switch (_y) {

    case  0 ... 20:   return ImageSize::Small;
    case 21 ... 40:   return ImageSize::Medium;
    default:          return ImageSize::Large;

  }

}

uint8_t OtherCar::getImageWidth() {

  switch (_y) {

    case  0 ... 20:   return 11;
    case 21 ... 40:   return 16;
    default:          return 20;

  }

}
