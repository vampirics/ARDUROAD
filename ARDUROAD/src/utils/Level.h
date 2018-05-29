#pragma once

#include "Arduboy2Ext.h"

class Level {

  public: 

    Level() {};

  
    // Properties ..

    int16_t getHorizonX();
    uint8_t getHorizonY();
    uint8_t getBand();
    uint8_t getTurnLength();
    uint8_t getTurnDirection();

    void setHorizonX(int16_t val);
    void setHorizonY(uint8_t val);
    void setTurn(uint8_t length, uint8_t direction);


    // Methods ..

    void incHorizonY(int8_t val);
    int8_t getCurve(uint8_t index);
    void turnLeft();
    void turnRight();
    void turnStraight();
    void decTurn();
    void move(Arduboy2Ext *arduboy);

  private:

    int16_t _horizonX;
    uint8_t _horizonY;
    uint8_t _band = 0;
    int8_t _curves[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t _turnLength = 0;
    uint8_t _turnDirection = 0;

    uint8_t _turnLengthMin = 10;
    uint8_t _turnLengthMax = 50;
//    int8_t _curves[8] = { -14, -14, -14, -8, -4, -2, -1, 0 };

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..


int16_t Level::getHorizonX() {
  return _horizonX;
}

uint8_t Level::getHorizonY() {
  return _horizonY;
}

uint8_t Level::getBand() {
  return _band;
}

uint8_t Level::getTurnLength() {
  return _turnLength;
}

uint8_t Level::getTurnDirection() {
  return _turnDirection;
}

void Level::setHorizonX(int16_t val) {
  _horizonX = val;
}

void Level::setHorizonY(uint8_t val) {
  _horizonY = val;
}

void Level::setTurn(uint8_t length, uint8_t direction) {
  _turnLength = length;
  _turnDirection = direction;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Level::incHorizonY(int8_t val) {

  _horizonY = (_horizonY + val);
  if (_horizonY >= HORIZON_ROW_COUNT) _band = (_band == 0 ? 1 : 0);
  _horizonY = _horizonY % HORIZON_ROW_COUNT;

}

int8_t Level::getCurve(uint8_t index) {
  return _curves[index];
}

void Level::turnStraight() {

  int8_t prvCurve = _curves[0];

  for (uint8_t x = 0; x < HORIZON_COL_COUNT; x++) {

    if (_curves[x + 1] != prvCurve) {

      prvCurve = _curves[x + 1];
      break;
        
    }

    prvCurve = _curves[x]; 
      
  }

  for (uint8_t x = 0; x < HORIZON_COL_COUNT; x++) {
    
    if (_curves[x] == prvCurve) break;
    _curves[x] = prvCurve;
      
  }

}

void Level::turnLeft() {

  int8_t min = 0;
  uint8_t index = HORIZON_COL_COUNT;

  for (uint8_t x = HORIZON_COL_COUNT; x > 0; x--) {

    if (_curves[x] < min) {
      
      min = _curves[x];
      index = x;

    }

  }

  for (uint8_t x = 0; x < index; x++) {

    switch (_curves[x + 1]) {

      case -22:  _curves[x] = -32;    break;
      case -14:  _curves[x] = -22;    break;
      case -8:   _curves[x] = -14;    break;
      case -4:   _curves[x] = -8;     break;
      case -2:   _curves[x] = -4;     break;
      case -1:   _curves[x] = -2;     break;
      case 0:    _curves[x] = -1;     break;

      case 1:    _curves[x] = 0;      break;
      case 2:    _curves[x] = 1;      break;
      case 4:    _curves[x] = 2;      break;
      case 8:    _curves[x] = 4;      break;
      case 14:   _curves[x] = 8;      break;
      case 22:   _curves[x] = 14;     break;
      case 32:   _curves[x] = 22;     break;


    }

  }

}


void Level::turnRight() {
  
  int8_t max = 0;
  uint8_t index = HORIZON_COL_COUNT;

  for (uint8_t x = HORIZON_COL_COUNT; x > 0; x--) {

    if (_curves[x] > max) {
      
      max = _curves[x];
      index = x;

    }

  }

  for (uint8_t x = 0; x < index; x++) {

    switch (_curves[x + 1]) {

      case 22:    _curves[x] = 32;    break;
      case 14:    _curves[x] = 22;    break;
      case 8:     _curves[x] = 14;    break;
      case 4:     _curves[x] = 8;     break;
      case 2:     _curves[x] = 4;     break;
      case 1:     _curves[x] = 2;     break;
      case 0:     _curves[x] = 1;     break;

      case -1:    _curves[x] = 0;     break;
      case -2:    _curves[x] = -1;    break;
      case -4:    _curves[x] = -2;    break;
      case -8:    _curves[x] = -4;    break;
      case -14:   _curves[x] = -8;    break;
      case -22:   _curves[x] = -14;   break;
      case -32:   _curves[x] = -22;   break;


    }

  }

}
//    int8_t _curves[8] = { 32, 22, 14, 8, 4, 2, 1, 0 };



void Level::decTurn() {

  if (_turnLength > 0) _turnLength--;

}

void Level::move(Arduboy2Ext *arduboy) {

//Serial.println(_curves[0]);
  switch (_curves[0]) {

    case -32 ... -22:     _horizonX += 1;  break;
    case -14 ...  -8:     if (arduboy->isFrameCount(FRAME_COUNT_HORIZON_X * 2)) { _horizonX += 1;  } break;
    case  -4 ...  -1:     if (arduboy->isFrameCount(FRAME_COUNT_HORIZON_X * 3)) { _horizonX += 1;  } break;
    case   1 ...   4:     if (arduboy->isFrameCount(FRAME_COUNT_HORIZON_X * 3)) { _horizonX -= 1;  } break;
    case   8 ...  14:     if (arduboy->isFrameCount(FRAME_COUNT_HORIZON_X * 2)) { _horizonX -= 1;  } break;
    case  22 ...  32:     _horizonX -= 1;  break;
    
  }

  if (_horizonX < -128) _horizonX += 128;
  if (_horizonX > 0)    _horizonX -= 128;

  if (_turnDirection == DIRECTION_STRAIGHT) turnStraight();
  if (_turnDirection == DIRECTION_LEFT)     turnLeft();
  if (_turnDirection == DIRECTION_RIGHT)    turnRight();

  decTurn();

  if (_turnLength == 0) {

    switch (_turnDirection) {

      case DIRECTION_STRAIGHT:
        _turnDirection = random(DIRECTION_STRAIGHT, DIRECTION_LEFT + 1);
        _turnLength = random(_turnLengthMin, _turnLengthMax);
        break;

      case DIRECTION_LEFT:
        _turnDirection = random(DIRECTION_STRAIGHT, DIRECTION_RIGHT + 1);
        _turnLength = random(_turnLengthMin, _turnLengthMax);
        break;

      case DIRECTION_RIGHT:
        _turnDirection = random(DIRECTION_STRAIGHT, DIRECTION_LEFT + 1);
        if (_turnDirection == DIRECTION_LEFT) _turnDirection++; 
        _turnLength = random(_turnLengthMin, _turnLengthMax);
        break;

    }

  }

}