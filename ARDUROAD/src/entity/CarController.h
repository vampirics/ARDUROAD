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
        if (x < NUMBER_OF_OTHER_CARS) _otherCars[x] = carController[x];
      }

    };

  
    // Properties ..

    OtherCar *getCar(uint8_t index);
    Base *getCarBase(uint8_t index);
    uint8_t getSortedIndex(uint8_t index);


    // Methods ..

    void sortCars();
    OtherCar* getInactiveCar();
    void updatePositions(Arduboy2Ext *arduboy, Player *player, uint8_t speed);
    OtherCar* getActiveCar_LowestY();
    OtherCar* getActiveCar_HighestY();


  private:

    OtherCar *_otherCars[NUMBER_OF_OTHER_CARS];
    Base *_allCars[NUMBER_OF_CARS_INC_PLAYER];
    uint8_t _order[NUMBER_OF_CARS_INC_PLAYER] = { 0, 1, 2, 3, 4 };

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

OtherCar *CarController::getCar(uint8_t index) {
  return _otherCars[index];
}

Base *CarController::getCarBase(uint8_t index) {
  return _allCars[index];
}

uint8_t CarController::getSortedIndex(uint8_t index) {
  return _order[index];
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

OtherCar* CarController::getInactiveCar() {

  for (uint8_t x = 0 ; x < NUMBER_OF_OTHER_CARS; x++) {
    if (!_otherCars[x]->isActive()) return _otherCars[x];
  }

  return nullptr;

}

OtherCar* CarController::getActiveCar_LowestY() {

  for (uint8_t x = NUMBER_OF_CARS_INC_PLAYER; x > 0; x--) {
    if (_allCars[(x - 1)]->getId() != 0) {
      OtherCar *otherCar = (OtherCar *)_allCars[(x - 1)];
      if (otherCar->isActive()) return otherCar;
    }
  }

  return nullptr;

}

OtherCar* CarController::getActiveCar_HighestY() {

  for (uint8_t x = 0; x < NUMBER_OF_CARS_INC_PLAYER; x++) {
    if (_allCars[x]->getId() != 0) {
      OtherCar *otherCar = (OtherCar *)_allCars[x];
      if (otherCar->isActive()) return otherCar;
    }
  }

  return nullptr;

}

void CarController::sortCars() {

  constexpr uint8_t n = NUMBER_OF_CARS_INC_PLAYER;

  for (uint8_t i = 1; i < n; ++i) {
  
    for(uint8_t j = i; j > 0 && _allCars[_order[j]]->getY() <= _allCars[_order[j - 1]]->getY(); --j) {

      swap(_order[j], _order[j - 1]);

    }

  }

}

void CarController::updatePositions(Arduboy2Ext *arduboy, Player *player, uint8_t speed) {

  int8_t i = 0;
  if (speed <= 2) { i = NUMBER_OF_CARS_INC_PLAYER; }

Serial.println(".");
Serial.println(".");
Serial.print("Speed: ");
Serial.print(speed);
Serial.print(", Sort Order: ");
for (uint8_t x = 0 ; x < NUMBER_OF_CARS_INC_PLAYER; x++) {
Serial.print(_order[x]);
Serial.print(" ");
}
Serial.println(" ");

  do {

Serial.print("OC: ");
Serial.print(i);
Serial.print(" -> ");
Serial.print(_order[i]);

    Base *baseCar = _allCars[_order[i]];

Serial.print(", id=");
Serial.print(baseCar->getId());
Serial.print(" ");

    if (baseCar->getId() != 0) {

      OtherCar *otherCar = (OtherCar *)baseCar;

      if (otherCar->isActive()) {
Serial.println("");
        Rect otherCarRect = otherCar->getRect();
        bool collision = false;

        int8_t j = 0;

        if (speed <= 2) j = NUMBER_OF_CARS_INC_PLAYER;

        do {
Serial.print("..");
Serial.print(j);
Serial.print(" -> ");
Serial.print(_order[j]);
Serial.print(" ");

          Rect testRect = { 0, 0, 0, 0 };
          Base *baseCarTest = _allCars[_order[j]];

          if (baseCarTest->getId() != otherCar->getId()) {
            Serial.print("ignore same car");
          }
          else {
              
            if (baseCarTest->getId() == 0) {

              testRect = player->getRect();

            }

            if (baseCarTest->getId() != otherCar->getId()) {

              OtherCar *otherCarTest = (OtherCar *)baseCarTest;
              testRect = otherCarTest->getRect();

            }

  Serial.print(" OCRect {");
  Serial.print(otherCarRect.x);
  Serial.print(",");
  Serial.print(otherCarRect.y);
  Serial.print(",");
  Serial.print(otherCarRect.width);
  Serial.print(",");
  Serial.print(otherCarRect.height);
  Serial.print("} ");
  Serial.print(" OTRect {");
  Serial.print(testRect.x);
  Serial.print(",");
  Serial.print(testRect.y);
  Serial.print(",");
  Serial.print(testRect.width);
  Serial.print(",");
  Serial.print(testRect.height);
  Serial.print("} ");
  Serial.print((arduboy->collide(otherCarRect, testRect) ? "Collision" : " No Collision"));


            if (testRect.x > 0) {

              if (arduboy->collide(otherCarRect, testRect)) {

                collision = true;
                break;

              }

            }

          }

          if (speed <= 2) {
            Serial.print(" incJ");
            j++;
            if (j == i || j == 0) { Serial.print(" break"); break; }
          }
          else {
            Serial.print(" decJ");
            j--;
            if (j == -1) { Serial.print(" break"); break; };
          }

        }
        while (true);

        if (!collision) {

          // Update Y position ..

          SQ7x8 oldY = otherCar->getY();
          SQ7x8 newY = otherCar->incY((speed / 2) - otherCar->getYDelta());
          SQ7x8 playerY = player->getY();

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
      else {
        Serial.print(" not active.");
      }

    }
    else {
        Serial.print(" ignore player car.");
    }

    if (speed > 2) {
      i++;
      if (i == NUMBER_OF_CARS_INC_PLAYER) break;
    }
    else {
      i--; 
      if (i == -1) break;
    }
Serial.println("");

  }
  while (true);

}

