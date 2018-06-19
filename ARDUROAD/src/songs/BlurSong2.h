#pragma once

#include "../utils/Arduboy2Ext.h"

const uint16_t song2small[] PROGMEM = {
 NOTE_REST,230, NOTE_C6,230, NOTE_C6,230, NOTE_C6,24, NOTE_REST,91, NOTE_F5,24, NOTE_REST,91, NOTE_AS5,230,
 NOTE_AS5,230, NOTE_AS5,230, NOTE_AS5,24, NOTE_REST,91, NOTE_DS5,24, NOTE_REST,91, NOTE_DS6,230, NOTE_DS6,230,
 NOTE_F6,230, NOTE_REST,5, NOTE_G6,438, NOTE_REST,17, NOTE_C7,230, NOTE_C7,230, NOTE_C7,230, NOTE_REST,230,
 NOTE_C6,230, NOTE_C6,230, NOTE_C6,24, NOTE_REST,91, NOTE_F5,24, NOTE_REST,91, NOTE_AS5,230, NOTE_AS5,230,
 NOTE_AS5,230, NOTE_AS5,24, NOTE_REST,91, NOTE_DS5,24, NOTE_REST,91, NOTE_GS6,230, NOTE_GS6,230, NOTE_AS6,230,
 NOTE_REST,5, NOTE_C7,438, NOTE_REST,17, NOTE_C7,230, NOTE_C7,230, NOTE_C7,230,
 TONES_REPEAT
};

const uint16_t song2[] PROGMEM = {
 NOTE_C3,153, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76,
 NOTE_C3,153, NOTE_REST,76, NOTE_FS3,115, NOTE_FS3,38, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_FS3,153,
 NOTE_REST,76, NOTE_FS3,76, NOTE_FS3,76, NOTE_REST,76, NOTE_FS3,115, NOTE_FS3,38, NOTE_REST,76, NOTE_FS3,153,
 NOTE_REST,76, NOTE_C3,153, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_C3,153, NOTE_C3,76, NOTE_C3,76,
 /*
 NOTE_REST,76, NOTE_REST,76, NOTE_E3,115, NOTE_E3,38, NOTE_REST,76, NOTE_C3,153, NOTE_REST,76, NOTE_FS3,153,
 NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_C3,153, NOTE_REST,76, NOTE_FS3,115,
 NOTE_FS3,38, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_FS3,76, NOTE_FS3,76,
 NOTE_REST,76, NOTE_FS3,115, NOTE_FS3,38, NOTE_REST,76, NOTE_FS3,153, NOTE_REST,76, NOTE_C3,153, NOTE_REST,76,
 NOTE_FS3,153, NOTE_REST,76, NOTE_C3,153, NOTE_C3,76, NOTE_C3,76, NOTE_REST,76, NOTE_REST,76, NOTE_E3,115,
 NOTE_E3,38, NOTE_REST,76, NOTE_C3,152, NOTE_REST,77, NOTE_FS3,152, NOTE_REST,77, NOTE_F5,230, NOTE_F5,24,
 NOTE_REST,91, NOTE_F5,24, NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24, NOTE_REST,91,
 NOTE_DS5,24, NOTE_REST,91, NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5, NOTE_G6,438, NOTE_REST,17,
 NOTE_C7,230, NOTE_C7,230, NOTE_C7,230, NOTE_REST,230, NOTE_F5,230, NOTE_F5,230, NOTE_F5,24, NOTE_REST,91,
 NOTE_F5,24, NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24, NOTE_REST,91, NOTE_DS5,24,
 NOTE_REST,91, NOTE_GS6,230, NOTE_GS6,230, NOTE_AS6,230, NOTE_REST,5, NOTE_C6,438, NOTE_REST,17, NOTE_C7,230,
 NOTE_C7,230, NOTE_C7,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230,
 NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230,
 NOTE_G5,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230,
 NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230,
 NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230,
 NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_C5,230,
 NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230,
 NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_REST,230, NOTE_C6,230,
 NOTE_F5,230, NOTE_F5,23, NOTE_REST,92, NOTE_F5,23, NOTE_REST,92, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230,
 NOTE_DS5,23, NOTE_REST,92, NOTE_DS5,23, NOTE_REST,92, NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5,
 NOTE_G6,438, NOTE_REST,17, NOTE_C7,230, NOTE_C7,230, NOTE_C7,230, NOTE_REST,230, NOTE_F5,230, NOTE_F5,230,
 NOTE_F5,24, NOTE_REST,91, NOTE_F5,24, NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24,
 NOTE_REST,91, NOTE_DS5,24, NOTE_REST,91, NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5, NOTE_G6,438,
 NOTE_REST,17, NOTE_C7,230, NOTE_C7,230, NOTE_C7,230, NOTE_REST,230, NOTE_F5,230, NOTE_F5,230, NOTE_F5,24,
 NOTE_REST,91, NOTE_F5,24, NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24, NOTE_REST,91,
 NOTE_DS5,24, NOTE_REST,91, NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5, NOTE_G6,438, NOTE_REST,17,

 NOTE_C7,230, NOTE_C7,230, NOTE_C7,230, NOTE_REST,230, NOTE_F5,230, NOTE_F5,230, NOTE_F5,24, NOTE_REST,91,
 NOTE_F5,24, NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24, NOTE_REST,91, NOTE_DS5,24,
 NOTE_REST,91, NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5, NOTE_G6,438, NOTE_REST,17, NOTE_C7,230,
 NOTE_C7,230, NOTE_C7,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230,
 NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230,
 NOTE_G5,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230,
 NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230,
 NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230,
 NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_F4,230,
 NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_DS5,230,
 NOTE_GS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_GS5,230,
 NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230,
 NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_F4,230,
 NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230,
 NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_C5,230, NOTE_F4,230,
 NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230,
 NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_REST,230, NOTE_F5,230, NOTE_F5,230,
 NOTE_F5,24, NOTE_REST,91, NOTE_F5,24, NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24,
 NOTE_REST,91, NOTE_DS5,24, NOTE_REST,91, NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5, NOTE_G6,438,
 NOTE_REST,17, NOTE_C7,230, NOTE_C7,230, NOTE_C7,230, NOTE_REST,230, NOTE_F5,230, NOTE_F5,230, NOTE_F5,24,
 NOTE_REST,91, NOTE_F5,24, NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24, NOTE_REST,91,
 NOTE_DS5,24, NOTE_REST,91, NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5, NOTE_G6,438, NOTE_REST,17,
 NOTE_C7,230, NOTE_C7,230, NOTE_C7,230, NOTE_REST,230, NOTE_F5,230, NOTE_F5,230, NOTE_F5,24, NOTE_REST,91,
 NOTE_F5,24, NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24, NOTE_REST,91, NOTE_DS5,24,
 NOTE_REST,91, NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5, NOTE_G6,438, NOTE_REST,17, NOTE_C7,230,
 NOTE_C7,230, NOTE_C7,230, NOTE_REST,230, NOTE_F5,230, NOTE_F5,230, NOTE_F5,24, NOTE_REST,91, NOTE_F5,24,
 NOTE_REST,91, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,230, NOTE_DS5,24, NOTE_REST,91, NOTE_DS5,24, NOTE_REST,91,
 NOTE_GS5,230, NOTE_GS5,230, NOTE_AS5,230, NOTE_REST,5, NOTE_G6,438, NOTE_REST,17, NOTE_C7,230, NOTE_C7,230,
 NOTE_C7,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230,
 NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230,
 NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230,
 NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_C5,230,
 NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230,
 NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_F4,230, NOTE_F4,230,
 NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_DS5,230, NOTE_GS4,230,
 NOTE_DS5,230, NOTE_GS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_GS5,230, NOTE_GS5,230,
 NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230,
 NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_GS5,230, NOTE_C5,230, NOTE_F4,230,
 NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230,
 NOTE_F5,230, NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230,
 NOTE_F4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230,
 NOTE_G5,461, NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_C5,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230,
 NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461,
 NOTE_G5,230, NOTE_G5,230, NOTE_G5,230, NOTE_F4,230, NOTE_F4,230, NOTE_C5,230, NOTE_F4,230, NOTE_AS4,230,
 NOTE_AS4,230, NOTE_AS4,230, NOTE_AS4,230, NOTE_DS5,230, NOTE_GS4,230, NOTE_F5,230, NOTE_G5,461, NOTE_G5,230,
 NOTE_G5,230, NOTE_G5,230, NOTE_F4,307,*/
 TONES_REPEAT
};