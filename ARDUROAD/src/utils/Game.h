#pragma once

#include "Arduboy2Ext.h"
#include "Enums.h"

#define EEPROM_START                  EEPROM_STORAGE_SPACE_START + 100
#define EEPROM_START_C1               EEPROM_START
#define EEPROM_START_C2               EEPROM_START + 1 
#define EEPROM_GAME_STATE             EEPROM_START_C2 + 1
    
struct Game {

  const uint8_t letter1 = 'A';
  const uint8_t letter2 = 'R';

  public: 
    
    Game() {};

  private:

    GameState _state = GameState::VSBoot;


  //--------------------------------------------------------------------------------------------------------------------------
  // Methods ..

  public: 

    GameState getState() {
      return _state;
    }

    void setState(GameState val) {
      _state = val;
      saveEEPROM();
    }

   /* ----------------------------------------------------------------------------
    *   Is the EEPROM initialised?
    *
    *   Looks for the characters 'A' and 'R' in the first two bytes of the EEPROM
    *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
    *   it resets the settings ..
    */
    void initEEPROM(bool forceClear) {

      byte c1 = EEPROM.read(EEPROM_START_C1);
      byte c2 = EEPROM.read(EEPROM_START_C2);

      if (forceClear || c1 != letter1 || c2 != letter2) { 

        EEPROM.update(EEPROM_START_C1, letter1);
        EEPROM.update(EEPROM_START_C2, letter2);

        saveEEPROM();

      }

    }

    void saveEEPROM() {

      EEPROM.update(EEPROM_GAME_STATE, static_cast<uint8_t>(_state));

    }

    void loadEEPROM() {

      _state = static_cast<GameState>(EEPROM.read(EEPROM_GAME_STATE));
   
    }
 
};
