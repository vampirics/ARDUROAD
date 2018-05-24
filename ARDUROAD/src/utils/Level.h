#pragma once

#include "Arduboy2Ext.h"

class Level {

  public: 

    Level() {};

  
    // Properties ..

    uint8_t getHorizon();
    uint8_t getBand();

    void setHorizon(uint8_t val);


    // Methods ..

    void incHorizon(int8_t val);

  private:

    uint8_t _horizon;
    uint8_t _band = 0;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..


uint8_t Level::getHorizon() {
  return _horizon;
}

uint8_t Level::getBand() {
  return _band;
}

void Level::setHorizon(uint8_t val) {
  _horizon = val;
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Level::incHorizon(int8_t val) {

  _horizon = (_horizon + val);
  if (_horizon >= HORIZON_ROW_COUNT) _band = (_band == 0 ? 1 : 0);
  _horizon = _horizon % HORIZON_ROW_COUNT;


//  _horizon = (_horizon + val) % HORIZON_ROW_COUNT;
  //if (_horizon < 0) _horizon = _horizon + HORIZON_ROW_COUNT;


}
