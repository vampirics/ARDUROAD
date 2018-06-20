#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Enums.h"
#include "Base.h"

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
    uint8_t getYDelta();
    TransmissionType getTransmissionType();

    void setXOffset(int8_t val);
    void setYDelta(uint8_t val);
    void setCarsPassedInit(uint16_t val);
    void setCarsPassed(uint16_t val);
    void setTransmissionType(TransmissionType val);


    // Methods ..

    void incX();
    void decX();
    void incCarsPassed();
    void decCarsPassed();
    void incOdometer();
    void resetOdometer();
    void decDirtCloud();
    void setDirtCloud();
    uint8_t getFrameDelay();

    bool incSpeed(bool changeGearsManual);
    bool decSpeed();
    void reset();
    bool onRoadsEdge();
//    boolean decelerate();

  private:

    int8_t _xOffset;
    uint16_t _carsPassedInit;
    uint16_t _carsPassed;
    uint16_t _odometer;
    uint8_t _dirtCloud;
    TransmissionType _transmissionType;
    uint8_t _frameDelay;
    uint8_t _yDelta;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

int8_t Player::getXOffset() {
  return _xOffset;
}

uint8_t Player::getFrameDelay() {
  return _frameDelay;
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

TransmissionType Player::getTransmissionType() {
  return _transmissionType;
}

uint8_t Player::getYDelta() {
  return _yDelta;
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

void Player::setTransmissionType(TransmissionType val) {
  _transmissionType = val;
}

void Player::setYDelta(uint8_t val) {
  _yDelta = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

#define OFFSET_LHS 15
#define OFFSET_LHS_GUTTER 5
#define OFFSET_LHS_MIN 0
#define OFFSET_RHS 70
#define OFFSET_RHS_GUTTER 80
#define OFFSET_RHS_MAX 85

int8_t Player::getXCentered() {
  return  _x - 64 + PLAYER_WIDTH_HALF;
}

void Player::incX() {  

  if      (_x < OFFSET_RHS_MAX) _x++;

  if      (_x < OFFSET_LHS) _xOffset = OFFSET_LHS - _x;
  else if (_x > OFFSET_RHS) _xOffset = -(_x - OFFSET_RHS);
  else    _xOffset = 0;

  if (_x > OFFSET_RHS_GUTTER && _dirtCloud < DIRT_CLOUD_DIVISOR) _dirtCloud = DIRT_CLOUD_MAX;

}

void Player::decX() {

  if      (_x > OFFSET_LHS_MIN) _x--;

  if      (_x < OFFSET_LHS) _xOffset = OFFSET_LHS - _x;
  else if (_x > OFFSET_RHS) _xOffset = -(_x - OFFSET_RHS);
  else    _xOffset = 0;

  if (_x < OFFSET_LHS_GUTTER && _dirtCloud < DIRT_CLOUD_DIVISOR) _dirtCloud = DIRT_CLOUD_MAX;

}

bool Player::onRoadsEdge() {// returns true if in gutter

  return (_x < OFFSET_LHS_GUTTER) || (_x > OFFSET_RHS_GUTTER);

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

void Player::reset() {
  _frameDelay = PLAYER_NO_MOVEMENT;
  _yDelta = 0;
}

#define FRAME_DELAY_MAX 30 
#define FRAME_DELAY_MIN 10 
#define FRAME_DELAY_INC 2

#define FRAME_DELAY_GEAR_1_END   30
#define FRAME_DELAY_GEAR_1_START 25 
#define FRAME_DELAY_GEAR_2_END   24
#define FRAME_DELAY_GEAR_2_START 20 
#define FRAME_DELAY_GEAR_3_END   19
#define FRAME_DELAY_GEAR_3_START 15 
#define FRAME_DELAY_GEAR_4_END   14
#define FRAME_DELAY_GEAR_4_START 10 

bool Player::decSpeed() {

  switch (_transmissionType) {

    case TransmissionType::Automatic:

      if (_frameDelay == FRAME_DELAY_MAX) {

        _frameDelay = PLAYER_NO_MOVEMENT;
        _yDelta = 0;

      }
      else if (_frameDelay <= FRAME_DELAY_MAX) {
        
        _frameDelay+=FRAME_DELAY_INC;

        switch (_frameDelay) {

          case FRAME_DELAY_GEAR_4_START ... FRAME_DELAY_GEAR_4_END:
            _yDelta = 4;
            break;

          case FRAME_DELAY_GEAR_3_START ... FRAME_DELAY_GEAR_3_END:
            _yDelta = 3;
            break;

          case FRAME_DELAY_GEAR_2_START ... FRAME_DELAY_GEAR_2_END:
            _yDelta = 2;
            break;

          case FRAME_DELAY_GEAR_1_START ... FRAME_DELAY_GEAR_1_END:
            _yDelta = 1;
            break;

          default:
            _yDelta = 0;
            break;
            
        }

        return true;

      }
      
      return false;

    case TransmissionType::Manual:

      if (_frameDelay <= FRAME_DELAY_GEAR_1_END) {
        
        _frameDelay+=FRAME_DELAY_INC;

        if (_frameDelay > FRAME_DELAY_GEAR_1_END) { _frameDelay = PLAYER_NO_MOVEMENT; }

        switch (_frameDelay) {

          case FRAME_DELAY_GEAR_4_START ... FRAME_DELAY_GEAR_4_END:
            _yDelta = 4;
            break;

          case FRAME_DELAY_GEAR_3_START ... FRAME_DELAY_GEAR_3_END:
            _yDelta = 3;
            break;

          case FRAME_DELAY_GEAR_2_START ... FRAME_DELAY_GEAR_2_END:
            _yDelta = 2;
            break;

          case FRAME_DELAY_GEAR_1_START ... FRAME_DELAY_GEAR_1_END:
            _yDelta = 1;
            break;

          default:
            _yDelta = 0;
            break;
            
        }

        return true;

      }

      return false;

  }

  return false;

}

bool Player::incSpeed(bool changeGearsManual) {

  switch (_transmissionType) {

    case TransmissionType::Automatic:

      if (_frameDelay == PLAYER_NO_MOVEMENT) {

        _frameDelay = FRAME_DELAY_MAX;
        _yDelta = 1;

      } 
      else if (_frameDelay >= FRAME_DELAY_MIN  + FRAME_DELAY_INC) {

        if (_yDelta == 0)  { _dirtCloud = DIRT_CLOUD_MAX; }  

        _frameDelay-=FRAME_DELAY_INC;

        switch (_frameDelay) {

          case FRAME_DELAY_GEAR_4_START ... FRAME_DELAY_GEAR_4_END:
            _yDelta = 4;
            break;

          case FRAME_DELAY_GEAR_3_START ... FRAME_DELAY_GEAR_3_END:
            _yDelta = 3;
            break;

          case FRAME_DELAY_GEAR_2_START ... FRAME_DELAY_GEAR_2_END:
            _yDelta = 2;
            break;

          default:
            _yDelta = 1;
            break;
            
        } 

        return true;
        
      }

      break;

    case TransmissionType::Manual:

      if (changeGearsManual && _yDelta >= 1 && _yDelta < 4) { 
        _yDelta++;
        _dirtCloud = DIRT_CLOUD_MAX;
      }

      if (changeGearsManual && _yDelta == 0) {
        _yDelta = 1;
        _dirtCloud = DIRT_CLOUD_MAX;
        _frameDelay = FRAME_DELAY_GEAR_1_END;
        return true;
      }

      switch (_yDelta) {

        case 4:

          if (_frameDelay >= FRAME_DELAY_GEAR_4_START + FRAME_DELAY_INC) {
            _frameDelay-=FRAME_DELAY_INC;
            return true;
          }

          return false;

        case 3:

          if (_frameDelay >= FRAME_DELAY_GEAR_3_START + FRAME_DELAY_INC) {
            _frameDelay-=FRAME_DELAY_INC;
            return true;
          }

          return false;

        case 2:

          if (_frameDelay >= FRAME_DELAY_GEAR_2_START + FRAME_DELAY_INC) {
            _frameDelay-=FRAME_DELAY_INC;
            return true;
          }

          return false;

        default:
          
          if (_yDelta == 0) {
            _yDelta = 1;
            _frameDelay = FRAME_DELAY_GEAR_1_END;
            return true;
          }
          else if (_frameDelay >= FRAME_DELAY_GEAR_1_START + FRAME_DELAY_INC) {
            _frameDelay-=FRAME_DELAY_INC;
            return true;
          }

          return false;
          
      } 

      return false;

  }

  return false;

}
