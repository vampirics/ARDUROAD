#pragma once

#include "../utils/Enums.h"
#include "OtherCar.h"

class OtherCars {

  public: 

    OtherCars() {
      // _otherCars[0].setActive(true);
      // _otherCars[0].setX(0);
      // _otherCars[0].setY(12);
    };

  
    // Properties ..

    OtherCar *getCar(uint8_t index);
    uint8_t getSortedIndex(uint8_t index);

    void setCar(uint8_t index, OtherCar val);


    // Methods ..

    void sortCars();
    uint8_t getActiveCars();
    OtherCar* getInactiveCar();

  private:

    OtherCar _otherCars[NUMBER_OF_OTHER_CARS];
    uint8_t _order[NUMBER_OF_OTHER_CARS] = { 0, 1, 2, 3, 4 };

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

OtherCar *OtherCars::getCar(uint8_t index) {
  return &_otherCars[index];
}

uint8_t OtherCars::getSortedIndex(uint8_t index) {
  return _order[index];
}

void OtherCars::setCar(uint8_t index, OtherCar val) {
  _otherCars[index] = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

uint8_t OtherCars::getActiveCars() {

  uint8_t active = 0;

  for (uint8_t x = 0 ; x < NUMBER_OF_OTHER_CARS; x++) {
    if (_otherCars[x].isActive()) active++;
  }

  return active;

}

OtherCar* OtherCars::getInactiveCar() {

  for (uint8_t x = 0 ; x < NUMBER_OF_OTHER_CARS; x++) {
    if (!_otherCars[x].isActive()) return &_otherCars[x];
  }

  return nullptr;

}

void OtherCars::sortCars() {

  for (uint8_t x = 0 ; x < NUMBER_OF_OTHER_CARS; x++) {
    _order[x] = x;
  }

  uint8_t n = NUMBER_OF_OTHER_CARS;

  for (uint8_t c = 0 ; c < ( n - 1 ); c++) {
  
    for (uint8_t d = 0 ; d < n - c - 1; d++) {
  
      if (_otherCars[d].getY() > _otherCars[d+1].getY()) {
        uint8_t swap = _order[d];
        _order[d]   = _order[d+1];
        _order[d+1] = swap;
      }
  
    }
  
  }

}

