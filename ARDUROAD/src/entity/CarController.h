#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "OtherCar.h"

class CarController {

  public: 

    CarController(OtherCar* carController[], Base* allCars[]) {
      
      for (uint8_t x = 0 ; x < NUMBER_OF_CARS_INC_PLAYER; x++) {
        _allCars[x] = allCars[x];
        if (x < NUMBER_OF_OTHER_CARS) _carController[x] = carController[x];
      }

    };

  
    // Properties ..

    OtherCar *getCar(uint8_t index);
    Base *getCarBase(uint8_t index);
    uint8_t getSortedIndex(uint8_t index);

    // void setCar(uint8_t index, OtherCar *val);


    // Methods ..

    void sortCars();
    OtherCar* getInactiveCar();
    void updatePositions(Player *player, uint8_t speed);

  private:

    OtherCar *_carController[NUMBER_OF_OTHER_CARS];
    Base *_allCars[NUMBER_OF_CARS_INC_PLAYER];
    uint8_t _order[NUMBER_OF_CARS_INC_PLAYER];

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

OtherCar *CarController::getCar(uint8_t index) {
  return _carController[index];
}

Base *CarController::getCarBase(uint8_t index) {
  return _allCars[index];
}

uint8_t CarController::getSortedIndex(uint8_t index) {
  return _order[index];
}

// void CarController::setCar(uint8_t index, OtherCar *val) {
//   _carController[index] = val;
// }


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

OtherCar* CarController::getInactiveCar() {

  for (uint8_t x = 0 ; x < NUMBER_OF_OTHER_CARS; x++) {
    if (!_carController[x]->isActive()) return _carController[x];
  }

  return nullptr;

}

void CarController::sortCars()
{
	for (uint8_t i = 0 ; i < NUMBER_OF_CARS_INC_PLAYER; ++i)
		_order[i] = i;

	uint8_t n = NUMBER_OF_CARS_INC_PLAYER;

	for (uint8_t i = 1; i < n; ++i)
		for(uint8_t j = i; j > 0 && _allCars[_order[j]]->getY() <= _allCars[_order[j - 1]]->getY(); --j)
			swap(_order[j], _order[j - 1]);
}

void CarController::updatePositions(Player *player, uint8_t speed) {

  for (uint8_t x = 0 ; x < NUMBER_OF_OTHER_CARS; x++) {

    OtherCar *otherCar = _carController[x];

    if (otherCar->isActive()) {


      // Update Y position ..

      SQ7x8 oldY = otherCar->getY();
      SQ7x8 newY = otherCar->incY((speed / 2) - otherCar->getYDelta());
      SQ7x8 playerY = player->getY();

      if ((oldY < playerY) && (newY >= playerY)) {
        player->incCarsPassed();
      }

      if ((oldY >= playerY) && (newY < playerY)) {
        player->decCarsPassed();
      }

    


      // Update X position ..

      uint8_t turnLength = otherCar->getTurnLength();

      if (turnLength == 0) {

        otherCar->setXDelta(static_cast<Direction>(random(static_cast<int8_t>(Direction::Left), static_cast<int8_t>(Direction::Right) + 1)));
        otherCar->setTurnLength(random(0, OTHER_CAR_TURN_LENGTH_MAX + 1));

      }
      else {

        switch (otherCar->getXDelta()) {

          case Direction::Left:
            otherCar->decX();
            break;

          case Direction::Right:
            otherCar->incX();
            break;

          default:
            break;

        }

      }

    }

  }

}

