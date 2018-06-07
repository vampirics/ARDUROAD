#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"

class Level {

  public: 

    Level() {};

  
    // Properties ..

    int16_t getHorizonX();
    uint8_t getHorizonY();
    uint8_t getBand();
    uint8_t getTurnLength();
    Direction getTurnDirection();
    TimeOfDay getTimeOfDay();

    void setHorizonX(int16_t val);
    void setHorizonY(uint8_t val);
    void setTurn(uint8_t length, Direction direction);
    void setTimeOfDay(TimeOfDay val);


    // Methods ..

    void incHorizonY(int8_t val);
    int8_t getCurve(uint8_t index);
    void turnLeft();
    void turnRight();
    void turnStraight();
    void decTurnLength();
    void move(Arduboy2Ext *arduboy, uint8_t speed);
    void incTime();

  private:

    int16_t _horizonX;
    uint8_t _horizonY;
    uint8_t _band = 0;
    int8_t _curves[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t _turnLength = 0;
    Direction _turnDirection = Direction::Straight;
    uint8_t _turnLengthMin = 10;
    uint8_t _turnLengthMax = 50;
    TimeOfDay _timeOfDay = TimeOfDay::Dusk;
    uint16_t _time = 0;

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

Direction Level::getTurnDirection() {
  return _turnDirection;
}

TimeOfDay Level::getTimeOfDay() {
  return _timeOfDay;
}

void Level::setHorizonX(int16_t val) {
  _horizonX = val;
}

void Level::setHorizonY(uint8_t val) {
  _horizonY = val;
}

void Level::setTimeOfDay(TimeOfDay val) {
  _timeOfDay = val;
}

void Level::setTurn(uint8_t length, Direction direction) {
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

  for (uint8_t i = 0; i < HORIZON_COL_COUNT; i++) {

    if (_curves[i + 1] != prvCurve) {

      prvCurve = _curves[i + 1];
      break;
        
    }

    prvCurve = _curves[i]; 
      
  }

  for (uint8_t i = 0; i < HORIZON_COL_COUNT; i++) {
    
    if (_curves[i] == prvCurve) break;
    _curves[i] = prvCurve;
      
  }

}

void Level::turnLeft() {

  int8_t min = 0;
  uint8_t index = HORIZON_COL_COUNT;

  for (int8_t i = HORIZON_COL_COUNT; i >= 0; i--) {

    if (_curves[i] < min) {
      
      min = _curves[i];
      index = i;

    }

  }

  for (uint8_t i = 0; i < index; i++) {

    if (_curves[i + 1] > -HORIZON_COL_COUNT) _curves[i]--;

  }

}


void Level::turnRight() {

  int8_t max = 0;
  uint8_t index = HORIZON_COL_COUNT;

  for (int8_t i = HORIZON_COL_COUNT; i >= 0; i--) {

    if (_curves[i] > max) {
      
      max = _curves[i];
      index = i;

    }

  }

  for (uint8_t i = 0; i < index; i++) {

    if (_curves[i + 1] < HORIZON_COL_COUNT) _curves[i]++;

  }

}

void Level::decTurnLength() {

  if (_turnLength > 0) _turnLength--;

}

void Level::incTime() {

  _time++;
  if (_time > TICKS_IN_A_PERIOD) {
    _time = 0;
    _timeOfDay++;
  }

}

void Level::move(Arduboy2Ext *arduboy, uint8_t speed) {

  switch (_curves[0]) {

    case -7 ... -6:     _horizonX += 1;  break;
    case -5 ... -4:     if (arduboy->isFrameCount(FRAME_COUNT_HORIZON_X * 2)) { _horizonX += 1;  } break;
    case -3 ... -1:     if (arduboy->isFrameCount(FRAME_COUNT_HORIZON_X * 3)) { _horizonX += 1;  } break;
    case  1 ...  3:     if (arduboy->isFrameCount(FRAME_COUNT_HORIZON_X * 3)) { _horizonX -= 1;  } break;
    case  4 ...  5:     if (arduboy->isFrameCount(FRAME_COUNT_HORIZON_X * 2)) { _horizonX -= 1;  } break;
    case  6 ...  7:     _horizonX -= 1;  break;
    
  }

  if (_horizonX < -128) _horizonX += 128;
  if (_horizonX > 0)    _horizonX -= 128;

  if (speed > 0) {

    if (_turnDirection == Direction::Straight) turnStraight();
    if (_turnDirection == Direction::Left)     turnLeft();
    if (_turnDirection == Direction::Right)    turnRight();

    decTurnLength();

    if (_turnLength == 0) {

      switch (_turnDirection) {

        case Direction::Straight:
          {
          uint8_t turn = random(0, 3);// 2,3// SJH(0, 3);
          _turnDirection = static_cast<Direction>(turn - 1);
          _turnLength = random(_turnLengthMin, _turnLengthMax);
          }
          break;

        case Direction::Left:
          {
          uint8_t turn = random(0, 2); // 0,2
          _turnDirection = static_cast<Direction>(turn - 1);
          _turnLength = random(_turnLengthMin, _turnLengthMax);
          }
          break;

        case Direction::Right:
          {
          uint8_t turn = random(0, 2); 
          _turnDirection = static_cast<Direction>(turn);
          _turnLength = random(_turnLengthMin, _turnLengthMax);
          }
          break;

      }

    }

  }

}