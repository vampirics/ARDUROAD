#pragma once

#include "Arduboy2Ext.h"

class Level {

  public: 

    Level() {};

  
    // Properties ..

    uint8_t getHorizon();
    uint8_t getBand();
    uint8_t getTurn();
    uint8_t getTurnDirection();

    void setHorizon(uint8_t val);
    void setTurn(uint8_t length, uint8_t direction);


    // Methods ..

    void incHorizon(int8_t val);
    int8_t getCurve(uint8_t index);
    void turnLeft();
    void turnRight();
    void turnStraight();
    void decTurn();
    void turn();

  private:

    uint8_t _horizon;
    uint8_t _band = 0;
    int8_t _curves[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t _turn = 0;
    uint8_t _turnDirection = 0;
//    int8_t _curves[8] = { -14, -14, -14, -8, -4, -2, -1, 0 };

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..


uint8_t Level::getHorizon() {
  return _horizon;
}

uint8_t Level::getBand() {
  return _band;
}

uint8_t Level::getTurn() {
  return _turn;
}

void Level::setHorizon(uint8_t val) {
  _horizon = val;
}

void Level::setTurn(uint8_t length, uint8_t direction) {
  _turn = length;
  _turnDirection = direction;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Level::incHorizon(int8_t val) {

  _horizon = (_horizon + val);
  if (_horizon >= HORIZON_ROW_COUNT) _band = (_band == 0 ? 1 : 0);
  _horizon = _horizon % HORIZON_ROW_COUNT;

}

int8_t Level::getCurve(uint8_t index) {
  return _curves[index];
}

void Level::turnStraight() {

  for (uint8_t x = 7; x > 0; x--) {

    int8_t curve = _curves[x];

    if (curve > 0) { turnLeft();    break; }
    if (curve < 0) { turnRight();   break; }

  }

}

void Level::turnLeft() {

  int8_t min = 0;
  uint8_t index = 7;

  for (uint8_t x = 7; x > 0; x--) {

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
      case 22:   _curves[x] = 4;      break;
      case 32:   _curves[x] = 22;     break;


    }

  }

}


void Level::turnRight() {
  
  int8_t max = 0;
  uint8_t index = 7;

  for (uint8_t x = 7; x > 0; x--) {

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

  if (_turn > 0) _turn--;

}

void Level::turn() {
//   Serial.print("Turn: ");
//   Serial.print(_turnDirection);
//   Serial.print(" ");
// for (uint8_t x = 0; x < 8; x++) {
//   Serial.print(_curves[x]);
//   Serial.print(" ");
  
// }
//   Serial.println("");

  


  if (_turnDirection == 0) turnStraight();
  if (_turnDirection == 1) turnLeft();
  if (_turnDirection == 2) turnRight();
  decTurn();

}