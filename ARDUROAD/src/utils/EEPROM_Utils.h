#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"
#include "../entity/Slot.h"

#define EEPROM_START                  EEPROM_STORAGE_SPACE_START + 400
#define EEPROM_START_C1               EEPROM_START
#define EEPROM_START_C2               EEPROM_START + 1
#define EEPROM_TOP_START              EEPROM_START + 2
#define EEPROM_ENTRY_SIZE             7

class EEPROM_Utils {

  public: 

    EEPROM_Utils(){};
        
    static void initEEPROM(bool forceClear);
    static void getSlot(uint8_t x, Slot *slot);
    static uint8_t saveScore(uint16_t odometer, uint16_t carsPassed);
    static void writeChars(uint8_t slotIndex, HighScore *highScore);

};


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'A' and 'R' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */

const uint8_t letter1 = 'A'; 
const uint8_t letter2 = 'R'; 

void EEPROM_Utils::initEEPROM(bool forceClear) {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  if (forceClear || c1 != letter1 || c2 != letter2) { 

    uint16_t odometer = 0;
    const uint16_t carsPassed = 0;

    EEPROM.update(EEPROM_START_C1, letter1);
    EEPROM.update(EEPROM_START_C2, letter2);

    for (uint8_t x = 0; x < MAX_NUMBER_OF_SCORES; x++) {

      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x), 0);
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1, 0);
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2, 0);

      odometer = 0; // (MAX_NUMBER_OF_SCORES - x) * 10;
      EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3, odometer);
      EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 5, carsPassed);

    }

  }

}


/* -----------------------------------------------------------------------------
 *   Get slot details. 
 */
void EEPROM_Utils::getSlot(uint8_t x, Slot *slot) {

  slot->setChar0(EEPROM.read(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x)));
  slot->setChar1(EEPROM.read(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1));
  slot->setChar2(EEPROM.read(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2));

  uint16_t odometer = 0;
  EEPROM.get(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3, odometer);
  slot->setOdometer(odometer);

  uint16_t carsPassed = 0;
  EEPROM.get(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 5, carsPassed);
  slot->setCarsPassed(carsPassed);

}


/* -----------------------------------------------------------------------------
 *   Save score and return index.  255 not good enough! 
 */
uint8_t EEPROM_Utils::saveScore(uint16_t odometer, uint16_t carsPassed) {
Serial.print("EEPROM_Utils::saveScore ");
Serial.print(odometer);
Serial.print(" ");
Serial.println(carsPassed);

  uint8_t idx = DO_NOT_EDIT_SLOT;

  for (uint8_t x = 0; x < MAX_NUMBER_OF_SCORES; x++) {

    uint16_t slotOdometer = 0;
    EEPROM.get(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3, slotOdometer);

    if (slotOdometer < odometer) {

      idx = x;
      break;

    }

  }
Serial.println(idx);
  if (idx < 255) {

    for (uint8_t x = MAX_NUMBER_OF_SCORES - 1; x > idx; x--) {

      Slot slot;
      getSlot(x - 1, &slot);

      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x), slot.getChar0());
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1, slot.getChar1());
      EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2, slot.getChar2());
      EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3, slot.getOdometer());
      EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 5, slot.getCarsPassed());

    }
Serial.print("ododo ");
Serial.print(odometer);
Serial.print(" ");
Serial.println(carsPassed);

    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx), 0);
    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 1, 0);
    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 2, 0);
    EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 3, odometer);
    EEPROM.put(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 5, carsPassed);

  uint16_t xx = 0;
  EEPROM.get(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 3, xx);
Serial.print("xx ");
Serial.println(xx);

  }

  for (uint8_t x = 0; x < MAX_NUMBER_OF_SCORES; x++) {

      Slot slot;
      getSlot(x - 1, &slot);
      Serial.print(x);
      Serial.print(" ");
      Serial.println(slot.getOdometer());
      
  }

  return idx;

}


/* -----------------------------------------------------------------------------
 *   Save score and return index.  255 not good enough! 
 */
void EEPROM_Utils::writeChars(uint8_t slotIndex, HighScore *highscore) {

    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex), highscore->getChar(0));
    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex) + 1, highscore->getChar(1));
    EEPROM.update(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex) + 2, highscore->getChar(2));

}
