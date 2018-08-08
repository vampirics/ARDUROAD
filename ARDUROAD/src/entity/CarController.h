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


Serial.print("Speed: ");
Serial.print(speed);
Serial.print(", Sort Order: ");
for (uint8_t x = 0 ; x < NUMBER_OF_CARS_INC_PLAYER; x++) {

  Base *baseCar = _allCars[_order[x]];
  Serial.print(baseCar->getId());
  if (baseCar->isActive()) {
    Serial.print("*");
  }
  Serial.print(" ");

}



// ----------------------------------------------------------

  int8_t testCarIdx = 0;
  bool dec = false;

  if (speed > 2) {
    testCarIdx = NUMBER_OF_CARS_INC_PLAYER - 1;
    dec = true;
  }

Serial.print(", dec: ");
Serial.print(dec);
Serial.println(" ");


  while ((testCarIdx >= 0 && dec) || (testCarIdx <= NUMBER_OF_CARS_INC_PLAYER - 1 && !dec)) {

    Base *testCar = _allCars[_order[testCarIdx]];



    // If this is not the player's car ..

    if (testCar->isActive() && testCar->getId() != 0) {

      OtherCar *otherTestCar = (OtherCar *)testCar;

      Serial.print("testCarIdx: ");
      Serial.print(testCarIdx);
      Serial.print(" = ");
      Serial.print(otherTestCar->getId());

      Serial.print(" - test cars ");



        // Loop the remaining cars ..

//        int8_t yIncrement = (speed / 2) - otherTestCar->getYDelta().getInteger();
        //Rect testCarRect = testCar->getRect(0, 0);
  // Serial.print(" testCarRect {");
  // Serial.print(testCarRect.x);
  // Serial.print(",");
  // Serial.print(testCarRect.y);
  // Serial.print(",");
  // Serial.print(testCarRect.width);
  // Serial.print(",");
  // Serial.print(testCarRect.height);
  // Serial.print("} ");
        //testCarRect = testCar->getRect(0, yIncrement);
  // Serial.print(" testCarRect {");
  // Serial.print(testCarRect.x);
  // Serial.print(",");
  // Serial.print(testCarRect.y);
  // Serial.print(",");
  // Serial.print(testCarRect.width);
  // Serial.print(",");
  // Serial.print(testCarRect.height);
  // Serial.println("} ");

        int8_t nextCarIdx = testCarIdx + (dec ? 1 : -1);

        while ((nextCarIdx >= 0 && !dec) || (nextCarIdx <= NUMBER_OF_CARS_INC_PLAYER - 1 && dec)) {
        
           Base *nextCar = _allCars[_order[nextCarIdx]];

           if (nextCar->isActive()) {


            //Rect nextCarRect = nextCar->getRect();


              Serial.print("(");
              Serial.print(nextCarIdx);
              Serial.print(") ");
              Serial.print(nextCar->getId());
              Serial.print(", ");

            


           }

          nextCarIdx = nextCarIdx + (dec ? 1 : -1);

        }

        Serial.println(" ");










      // Move the car ..

//      if (!collision) {

        // Update Y position ..

        SQ7x8 oldY = otherTestCar->getY();
        SQ7x8 newY = otherTestCar->incY((speed / 2) - otherTestCar->getYDelta());
        SQ7x8 playerY = player->getY();

        if ((oldY < playerY) && (newY >= playerY)) {
          player->decCarsPassed();
        }

        if ((oldY >= playerY) && (newY < playerY)) {
          player->incCarsPassed();
        }

//      }



      // Update X position ..

      uint8_t turnLength = otherTestCar->getTurnLength();

      if (turnLength == 0) {

        otherTestCar->setXDelta(static_cast<Direction>(random(static_cast<int8_t>(Direction::Left), static_cast<int8_t>(Direction::Right) + 1)));
        otherTestCar->setTurnLength(random(0, OTHER_CAR_TURN_LENGTH_MAX + 1));

      }
      else {

        switch (otherTestCar->getXDelta()) {

          case Direction::Left:
            otherTestCar->decX();
            break;

          case Direction::Right:
            otherTestCar->incX();
            break;

          default:
            break;

        }

      }




    }
    else {
      Serial.println(" Players car.");
    }

    testCarIdx = testCarIdx + (dec ? -1 : 1);
    Serial.println(testCarIdx);

  }


  Serial.println("------------------------------------------------------");

}

