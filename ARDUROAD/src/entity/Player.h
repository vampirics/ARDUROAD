#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Enums.h"
#include "Base.h"

const uint8_t PROGMEM speedLookup[] = {255, 5, 3, 2, 1};

class Player : public Base {

  public: 

    Player(uint8_t id) : Base(id) {};


    // Properties ..

    int8_t getXCentered();
    int8_t getXOffset();
    uint16_t getCarsPassedInit();
    uint16_t getCarsPassed();
    uint16_t getOdometer();
    uint8_t getDirtCloud();

    void setXOffset(int8_t val);
    void setCarsPassedInit(uint16_t val);
    void setCarsPassed(uint16_t val);
    uint8_t getFrameDelay();


    // Methods ..

    void incX();
    void decX();
    void incCarsPassed();
    void decCarsPassed();
    void incOdometer();
    void resetOdometer();
    void decDirtCloud();
    void setDirtCloud();
    
    boolean incYDelta();
    boolean decYDelta();
    boolean decelerate();

  private:

    int8_t _xOffset;
    uint16_t _carsPassedInit;
    uint16_t _carsPassed;
    uint16_t _odometer;
    uint8_t _dirtCloud;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

int8_t Player::getXOffset() {
  return _xOffset;
}

uint8_t Player::getFrameDelay() {
  return pgm_read_byte(&speedLookup[absT(_yDelta.getInteger())]);
}

uint16_t Player::getCarsPassed() {
  return _carsPassed;
}

uint16_t Player::getCarsPassedInit() {
  return _carsPassedInit;
}

uint16_t Player::getOdometer() {
  return _odometer;
}

uint8_t Player::getDirtCloud() {
  return _dirtCloud / DIRT_CLOUD_DIVISOR;
}

void Player::setXOffset(int8_t val) {
  _xOffset = val;
}

void Player::setCarsPassed(uint16_t val) {
  _carsPassed = val;
}

void Player::setCarsPassedInit(uint16_t val) {
  _carsPassedInit = val;
  _carsPassed = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

#define OFFSET_LHS 15
#define OFFSET_LHS_MIN 5
#define OFFSET_RHS 70
#define OFFSET_RHS_MAX 80

int8_t Player::getXCentered() {
  return  _x - 64 + PLAYER_WIDTH_HALF;
}

void Player::incX() {

  if (_x < OFFSET_RHS_MAX) _x++;

  if (_x < OFFSET_LHS) _xOffset = OFFSET_LHS - _x;
  else if (_x > OFFSET_RHS) _xOffset = -(_x - OFFSET_RHS);
  else _xOffset = 0;

}

void Player::decX() {

  if (_x > OFFSET_LHS_MIN) _x--;

  if (_x < OFFSET_LHS) _xOffset = OFFSET_LHS - _x;
  else if (_x > OFFSET_RHS) _xOffset = -(_x - OFFSET_RHS);
  else _xOffset = 0;

}

void Player::incCarsPassed() {
  if (_carsPassed < _carsPassedInit) _carsPassed++;
}

void Player::decCarsPassed() {
  if (_carsPassed > 0) _carsPassed--;
}

void Player::incOdometer() {
  _odometer++;
}

void Player::resetOdometer() {
  _odometer++;
}

void Player::decDirtCloud() {
  _dirtCloud--;
}

void Player::setDirtCloud() {
  _dirtCloud = DIRT_CLOUD_MAX;
}

// Returns true if the value has changed ..

boolean Player::incYDelta() {

  switch(_yDelta.getInteger()) {
     
    case 0:
      _yDelta = 1;
      _dirtCloud = DIRT_CLOUD_MAX;
      return true;

    case 1:
      _yDelta = 2;
      _dirtCloud = DIRT_CLOUD_MAX;
      return true;

    case 2:
      _yDelta = 3;
      _dirtCloud = DIRT_CLOUD_MAX;
      return true;

    case 3:
      _yDelta = 4;
      _dirtCloud = DIRT_CLOUD_MAX;
      return true;

  }

  return false;

}

// Returns true if the value has changed ..

boolean Player::decYDelta() {

  switch(_yDelta.getInteger()) {

    case 1:
      _yDelta = 0;
      return true;

    case 2:
      _yDelta = 1;
      return true;

    case 3:
      _yDelta = 2;
      return true;

    case 4:
      _yDelta = 3;
      return true;

  }

  return false;

}

boolean Player::decelerate() {

  if (_yDelta > 0) return decYDelta();
  if (_yDelta < 0) return incYDelta();

  return false;

}
