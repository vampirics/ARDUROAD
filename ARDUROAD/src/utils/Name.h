#pragma once

#include <Arduboy2.h>

#define NAME_LENGTH 6
#define NAME_CHARACTER_SPACING 6
#define NAME_UNDERLINE_WIDTH 3

#define ASCII_SPACE 32
#define ASCII_CAPITAL_A 65
#define ASCII_CAPITAL_B 66
#define ASCII_CAPITAL_Y 89
#define ASCII_CAPITAL_Z 90
#define ASCII_LOWER_A 97
#define ASCII_LOWER_B 98
#define ASCII_LOWER_Y 121
#define ASCII_LOWER_Z 122


class Name {

  public: 

    Name() {
      for (uint8_t x=0; x < NAME_LENGTH; x++) _chars[x] = ' ';
    };
  

    // Properties ..

    uint8_t getCharIndex();
    char getChar(uint8_t idx);
    void setCharIndex(uint8_t val);
    void setChar(uint8_t idx, uint8_t val);
    void setChars(char val[NAME_LENGTH]);


    // Methods ..

    void incCharIndex();
    void decCharIndex();
    void incChar(uint8_t idx);
    void decChar(uint8_t idx);
    void clear();
    void clear(uint16_t startingLocation);
    void retrieve(uint16_t startingLocation);
    void save(uint16_t startingLocation);
    char* getString();

  private:
   
    uint8_t _charIndex;
    char _chars[NAME_LENGTH];
    uint16_t _eeprom_start;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

uint8_t Name::getCharIndex() {
  return _charIndex;
}

char Name::getChar(uint8_t idx) {
  return _chars[idx];
}

void Name::setCharIndex(uint8_t val) {
  _charIndex = val;
}

void Name::setChar(uint8_t idx, uint8_t val) {
  _chars[idx] = val;
}

void Name::setChars(char val[NAME_LENGTH]) {
  _charIndex = 0;
  memcpy(_chars, val, NAME_LENGTH);
}


//--------------------------------------------------------------------------------------------------------------------------
// Methods ..

void Name::incCharIndex() {
  if (_charIndex < NAME_LENGTH - 1) _charIndex++;
}

void Name::decCharIndex() {
  if (_charIndex > 0) _charIndex--;
}

void Name::incChar(uint8_t idx) {
  
  switch (_chars[idx]) {

    case ASCII_SPACE:
      _chars[idx] = ASCII_CAPITAL_A;
      break;

    case ASCII_CAPITAL_A ... ASCII_CAPITAL_Y:
      _chars[idx]++;
      break;

    case ASCII_CAPITAL_Z:
      _chars[idx] = ASCII_LOWER_A;
      break;

    case ASCII_LOWER_A ... ASCII_LOWER_Y:
      _chars[idx]++;
      break;

    case ASCII_LOWER_Z:
      _chars[idx] = ASCII_SPACE;
      break;
    
  }

}

void Name::decChar(uint8_t idx) {

  switch (_chars[idx]) {

    case ASCII_SPACE:
      _chars[idx] = ASCII_LOWER_Z;
      break;

    case ASCII_CAPITAL_A:
      _chars[idx] = ASCII_SPACE;
      break;

    case ASCII_CAPITAL_B ... ASCII_CAPITAL_Z:
      _chars[idx]--;
      break;

    case ASCII_LOWER_A:
      _chars[idx] = ASCII_CAPITAL_Z;
      break;

    case ASCII_LOWER_B ... ASCII_LOWER_Z:
      _chars[idx]--;
      break;
    
  }

}

void Name::clear() {

  _charIndex = 0;
      
  for (uint8_t x = 0; x < NAME_LENGTH; x++) {
    
    _chars[x] = ASCII_SPACE;

  }

}

void Name::clear(uint16_t startingLocation) {

  _charIndex = 0;
      
  for (uint8_t x = 0; x < NAME_LENGTH; x++) {
    
    _chars[x] = ASCII_SPACE;

  }

  Name::save(startingLocation);

}

void Name::retrieve(uint16_t startingLocation) {

  _charIndex = 0;
      
  for (uint8_t x = 0; x < NAME_LENGTH; x++) {
    
    _chars[x] = EEPROM.read(startingLocation + x);

  }

  // Has it been initialised ?  If not clear it ..

  if (_chars[0] != ASCII_SPACE    &&                     
      (_chars[0] < ASCII_CAPITAL_A || _chars[0] > ASCII_CAPITAL_Z) &&     
      (_chars[0] < ASCII_LOWER_A   || _chars[0] > ASCII_LOWER_Z)       
      ) { clear(startingLocation); }

}

void Name::save(uint16_t startingLocation) {

  for (uint8_t x = 0; x < NAME_LENGTH; x++) {
    
    EEPROM.update(startingLocation + x, getChar(x));

  }

}

char* Name::getString() {
  return _chars;

}
