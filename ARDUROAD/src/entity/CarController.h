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
    void updateCarPosition(Player *player, OtherCar *carToUpdate, uint8_t speed);
    bool collide(Rect rect1, Rect rect2);

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

void CarController::sortCars() {

  for (uint8_t i = 0 ; i < NUMBER_OF_CARS_INC_PLAYER; ++i) {
    _order[i] = i;
  }

  constexpr uint8_t n = NUMBER_OF_CARS_INC_PLAYER;

  for (uint8_t i = 1; i < n; ++i) {
  
    for(uint8_t j = i; j > 0 && _allCars[_order[j]]->getY() <= _allCars[_order[j - 1]]->getY(); --j) {

      swap(_order[j], _order[j - 1]);

    }

  }

}

void CarController::updatePositions(Player *player, uint8_t speed) {

  // Use the sorted positions to move the cars ..

  if (speed < 2) {

    for (uint8_t x = 0 ; x < NUMBER_OF_CARS_INC_PLAYER; x++) {

      Base *baseCar = _allCars[_order[x]];

      if (baseCar->getCarType() == CarType::OtherCar) {

        OtherCar *otherCar = (OtherCar *)baseCar;

        if (otherCar->isActive()) { 
          
          updateCarPosition(player, otherCar, speed);

        }

      }

    }

  }
  else {

    for (uint8_t x = NUMBER_OF_CARS_INC_PLAYER; x > 0; x--) {

      Base *baseCar = _allCars[_order[x]];

      if (baseCar->getCarType() == CarType::OtherCar) {

        OtherCar *otherCar = (OtherCar *)baseCar;

        if (otherCar->isActive()) { 
          
          updateCarPosition(player, otherCar, speed);

        }

      }

    }

  }

}

void CarController::updateCarPosition(Player *player, OtherCar *carToUpdate, uint8_t speed) {


  // Update Y position ..

  SQ7x8 oldY = carToUpdate->getY();
  SQ7x8 newY = carToUpdate->getY() + (speed / 2) - carToUpdate->getYDelta();

  bool crash = false;

  Rect rectCarToUpdate = { carToUpdate->getX(), newY.getInteger(), OTHER_CAR_MAX_WIDTH, 10 }; 

Serial.println("");
Serial.println("--------------------------------------");
Serial.print("updateCarPosition (");
Serial.print(carToUpdate->getId());
Serial.println(")");

  for (uint8_t x = 0 ; x < NUMBER_OF_CARS_INC_PLAYER; x++) {

    Base *compareCar = _allCars[x];

    if (carToUpdate->getId() != compareCar->getId()) {

      Rect rectCarToCompare = { compareCar->getX(), compareCar->getY().getInteger(), OTHER_CAR_MAX_WIDTH, 10 }; 

Serial.print("Compare (");
Serial.print(carToUpdate->getId());
Serial.print(":");
Serial.print(rectCarToUpdate.x);
Serial.print(",");
Serial.print(rectCarToUpdate.y);
Serial.print(",");
Serial.print(rectCarToUpdate.width);
Serial.print(",");
Serial.print(rectCarToUpdate.height);
Serial.print(") (");
Serial.print(compareCar->getId());
Serial.print(":");
Serial.print(rectCarToCompare.x);
Serial.print(",");
Serial.print(rectCarToCompare.y);
Serial.print(",");
Serial.print(rectCarToCompare.width);
Serial.print(",");
Serial.print(rectCarToCompare.height);
Serial.print(")");

      if (collide(rectCarToUpdate, rectCarToCompare)) {
Serial.println(" ******* Crash!");
        crash = true;
        break;

      }
Serial.println(" ");
    }

  }

  if (!crash) {

    carToUpdate->setY(newY);
    SQ7x8 playerY = player->getY();

    if ((oldY < playerY) && (newY >= playerY)) {
      player->incCarsPassed();
    }

    if ((oldY >= playerY) && (newY < playerY)) {
      player->decCarsPassed();
    }

  }



  // Update X position ..

  uint8_t turnLength = carToUpdate->getTurnLength();

  if (turnLength == 0) {

    carToUpdate->setXDelta(static_cast<Direction>(random(static_cast<int8_t>(Direction::Left), static_cast<int8_t>(Direction::Right) + 1)));
    carToUpdate->setTurnLength(random(0, OTHER_CAR_TURN_LENGTH_MAX + 1));

  }
  else {

    switch (carToUpdate->getXDelta()) {

      case Direction::Left:
        carToUpdate->decX();
        break;

      case Direction::Right:
        carToUpdate->incX();
        break;

      default:
        break;

    }

  }

}

bool CarController::collide(Rect rect1, Rect rect2) {

  return !(rect2.x                >= rect1.x + rect1.width  ||
           rect2.x + rect2.width  <= rect1.x                ||
           rect2.y                >= rect1.y + rect1.height ||
           rect2.y + rect2.height <= rect1.y);
           
}

