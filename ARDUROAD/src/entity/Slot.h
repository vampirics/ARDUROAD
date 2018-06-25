#pragma once

#include "../utils/Arduboy2Ext.h"

class Slot {

  public: 

    Slot() {};
  

    // Properties ..

    uint8_t getChar0();
    uint8_t getChar1();
    uint8_t getChar2();
    uint16_t getOdometer();
    uint16_t getDayCount();

    void setChar0(uint8_t val);
    void setChar1(uint8_t val);
    void setChar2(uint8_t val);
    void setOdometer(uint16_t val);
    void setDayCount(uint16_t val);


  private:
   
    uint8_t _char0;
    uint8_t _char1;
    uint8_t _char2;
    uint16_t _odometer;
    uint16_t _dayCount;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

uint8_t Slot::getChar0() {
  return _char0;
}

uint8_t Slot::getChar1() {
  return _char1;
}

uint8_t Slot::getChar2() {
  return _char2;
}

uint16_t Slot::getOdometer() {
  return _odometer;
}

uint16_t Slot::getDayCount() {
  return _dayCount;
}

void Slot::setChar0(uint8_t val) {
  _char0 = val;
}

void Slot::setChar1(uint8_t val) {
  _char1 = val;
}

void Slot::setChar2(uint8_t val) {
  _char2 = val;
}

void Slot::setOdometer(uint16_t val) {
  _odometer = val;
}

void Slot::setDayCount(uint16_t val) {
  _dayCount = val;
}
