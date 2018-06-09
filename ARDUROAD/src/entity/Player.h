#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Enums.h"

const uint8_t speedLookup[] = {12, 6, 4, 2, 1};

class Player {

  public: 

    Player() {};
  
    // Properties ..

    uint8_t getX();
    uint8_t getY();
    int8_t getXDelta();
    int8_t getYDelta();
    int8_t getXOffset();
    uint8_t getCarsPassed();
    uint16_t getOdometer();
    uint8_t getDirtCloud();

    void setX(uint8_t val);
    void setXDelta(int8_t val);
    void setYDelta(int8_t val);
    void setXOffset(int8_t val);
    void setCarsPassed(uint8_t val);
    uint8_t getGear();


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

    uint8_t _x;
    int8_t _xOffset;
    int8_t _xDelta;
    int8_t _yDelta;
    uint8_t _carsPassed;
    uint16_t _odometer;
    uint8_t _dirtCloud;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

uint8_t Player::getX() {
  return _x;
}

uint8_t Player::getY() {
  return 48;
}

int8_t Player::getXDelta() {
  return _xDelta;
}

int8_t Player::getXOffset() {
  return _xOffset;
}

int8_t Player::getYDelta() {
  return _yDelta;
}

uint8_t Player::getGear() {
  return speedLookup[absT(_yDelta)];
}

uint8_t Player::getCarsPassed() {
  return _carsPassed;
}

uint16_t Player::getOdometer() {
  return _odometer;
}

uint8_t Player::getDirtCloud() {
  return _dirtCloud / DIRT_CLOUD_DIVISOR;
}

void Player::setX(uint8_t val) {
  _x = val;
}

void Player::setXDelta(int8_t val) {
  _xDelta = val;
}

void Player::setXOffset(int8_t val) {
  _xOffset = val;
}

void Player::setYDelta(int8_t val) {
  _yDelta = val;
}

void Player::setCarsPassed(uint8_t val) {
  _carsPassed = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Player::incX() {

  if (_x < 82) _x++;
  if (_x > 67) _xOffset = -(92-_x);
  else _xOffset = 0;

}

void Player::decX() {

  if (_x > 5) _x--;
  if (_x < 15) _xOffset = 15-_x;
  else _xOffset = 0;

}

void Player::incCarsPassed() {
  _carsPassed++;
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

  switch(_yDelta) {
     
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

  switch(_yDelta) {

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
