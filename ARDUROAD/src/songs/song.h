#ifndef SONG_H
#define SONG_H

#define Song const uint8_t PROGMEM

Song music1[] = {
0x0f,      // Number of tracks
0x00, 0x00,   // Address of track 0
0x0d, 0x00,   // Address of track 1
0x1a, 0x00,   // Address of track 2
0x2d, 0x00,   // Address of track 3
0x36, 0x00,   // Address of track 4
0x3c, 0x00,   // Address of track 5
0x43, 0x00,   // Address of track 6
0x74, 0x00,   // Address of track 7
0xa5, 0x00,   // Address of track 8
0xa8, 0x00,   // Address of track 9
0xab, 0x00,   // Address of track 10
0xc2, 0x00,   // Address of track 11
0xc5, 0x00,   // Address of track 12
0xe1, 0x00,   // Address of track 13
0xe4, 0x00,   // Address of track 14
0x00,     // Channel 0 entry track
0x01,     // Channel 1 entry track
0x02,     // Channel 2 entry track
0x03,     // Channel 3 entry track
//"Track channel 0"
0x40, 60,   // FX: SET VOLUME: volume = 60
0x50, 4, 1,   // FX: SET VIBRATO: 4 1
0x9D, 18,   // FX: SET TEMPO: tempo = 18
0xFC, 13,   // GOTO track 13
0xFD, 10, 6,    // REPEAT: count = 10 + 1 / track = 6
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 1"
0x40, 56,   // FX: SET VOLUME: volume = 56
0x4C, 3,    // FX: SET TRANSPOSITION: 3
0xFC, 13,   // GOTO track 13
0xFD, 1, 11,    // REPEAT: count = 1 + 1 / track = 11
0xFD, 8, 7,   // REPEAT: count = 8 + 1 / track = 7
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 2"
0x40, 48,   // FX: SET VOLUME: volume = 48
0x4C, -12,    // FX: SET TRANSPOSITION: -12
0xFC, 13,   // GOTO track 13
0xFD, 1, 11,    // REPEAT: count = 1 + 1 / track = 11
0xFD, 3, 6,   // REPEAT: count = 3 + 1 / track = 6
0xFD, 1, 11,    // REPEAT: count = 1 + 1 / track = 11
0xFD, 2, 6,   // REPEAT: count = 2 + 1 / track = 6
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 3"
0xFC, 12,   // GOTO track 12
0xFD, 1, 14,    // REPEAT: count = 1 + 1 / track = 14
0xFD, 8, 10,    // REPEAT: count = 8 + 1 / track = 10
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track tick"
0x40, 32,   // FX: SET VOLUME: volume = 32
0x9F + 1,   // DELAY: ticks = 1
0x40, 0,    // FX: SET VOLUME: volume = 0
0xFE,     // RETURN
//"Track snare"
0x40, 32,   // FX: SET VOLUME: volume = 32
0x41, -16,    // FX: VOLUME SLIDE ON: steps = -16
0x9F + 2,   // DELAY: ticks = 2
0x43,     // FX: VOLUME SLIDE OFF
0xFE,     // RETURN
//"Track Track 1"
0x00 + 18,    // NOTE ON: note = 18
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 18,    // NOTE ON: note = 18
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 18,    // NOTE ON: note = 18
0x9F + 6,   // DELAY: ticks = 6
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 16,    // NOTE ON: note = 16
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 16,    // NOTE ON: note = 16
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 16,    // NOTE ON: note = 16
0x9F + 5,   // DELAY: ticks = 5
0x00 + 0,   // NOTE ON: note = 0
0x9F + 3,   // DELAY: ticks = 3
0x00 + 21,    // NOTE ON: note = 21
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 21,    // NOTE ON: note = 21
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 23,    // NOTE ON: note = 23
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 25,    // NOTE ON: note = 25
0x9F + 8,   // DELAY: ticks = 8
0x00 + 0,   // NOTE ON: note = 0
0x9F + 8,   // DELAY: ticks = 8
0x00 + 25,    // NOTE ON: note = 25
0x9F + 1,   // DELAY: ticks = 1
0x00 + 0,   // NOTE ON: note = 0
0x9F + 1,   // DELAY: ticks = 1
0x00 + 25,    // NOTE ON: note = 25
0x9F + 1,   // DELAY: ticks = 1
0x00 + 0,   // NOTE ON: note = 0
0x9F + 1,   // DELAY: ticks = 1
0xFE,     // RETURN
//"Track Track 2"
0x00 + 22,    // NOTE ON: note = 22
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 22,    // NOTE ON: note = 22
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 22,    // NOTE ON: note = 22
0x9F + 4,   // DELAY: ticks = 4
0x00 + 0,   // NOTE ON: note = 0
0x9F + 4,   // DELAY: ticks = 4
0x00 + 20,    // NOTE ON: note = 20
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 20,    // NOTE ON: note = 20
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 20,    // NOTE ON: note = 20
0x9F + 4,   // DELAY: ticks = 4
0x00 + 0,   // NOTE ON: note = 0
0x9F + 4,   // DELAY: ticks = 4
0x00 + 22,    // NOTE ON: note = 22
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 22,    // NOTE ON: note = 22
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 25,    // NOTE ON: note = 25
0x9F + 2,   // DELAY: ticks = 2
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 30,    // NOTE ON: note = 30
0x9F + 7,   // DELAY: ticks = 7
0x00 + 0,   // NOTE ON: note = 0
0x9F + 9,   // DELAY: ticks = 9
0x00 + 30,    // NOTE ON: note = 30
0x9F + 1,   // DELAY: ticks = 1
0x00 + 0,   // NOTE ON: note = 0
0x9F + 1,   // DELAY: ticks = 1
0x00 + 30,    // NOTE ON: note = 30
0x9F + 1,   // DELAY: ticks = 1
0x00 + 0,   // NOTE ON: note = 0
0x9F + 1,   // DELAY: ticks = 1
0xFE,     // RETURN
//"Track Track 3"
0x00 + 0,   // NOTE ON: note = 0
0x9F + 64,    // DELAY: ticks = 64
0xFE,     // RETURN
//"Track Track 4"
0x00 + 0,   // NOTE ON: note = 0
0x9F + 64,    // DELAY: ticks = 64
0xFE,     // RETURN
//"Track Track 5"
0x9F + 8,   // DELAY: ticks = 8
0xFC, 4,    // GOTO track 4
0x9F + 7,   // DELAY: ticks = 7
0xFC, 5,    // GOTO track 5
0x9F + 6,   // DELAY: ticks = 6
0xFC, 4,    // GOTO track 4
0x9F + 7,   // DELAY: ticks = 7
0xFC, 5,    // GOTO track 5
0x9F + 6,   // DELAY: ticks = 6
0xFC, 4,    // GOTO track 4
0x9F + 7,   // DELAY: ticks = 7
0xFC, 5,    // GOTO track 5
0x9F + 6,   // DELAY: ticks = 6
0xFC, 4,    // GOTO track 4
0x9F + 7,   // DELAY: ticks = 7
0xFE,     // RETURN
//"Track empty"
0x00 + 0,   // NOTE ON: note = 0
0x9F + 64,    // DELAY: ticks = 64
0xFE,     // RETURN
//"Track intro"
0xFC, 4,    // GOTO track 4
0x9F + 3,   // DELAY: ticks = 3
0xFC, 4,    // GOTO track 4
0x9F + 3,   // DELAY: ticks = 3
0xFC, 5,    // GOTO track 5
0x9F + 2,   // DELAY: ticks = 2
0xFC, 4,    // GOTO track 4
0x9F + 3,   // DELAY: ticks = 3
0xFC, 4,    // GOTO track 4
0x9F + 3,   // DELAY: ticks = 3
0xFC, 4,    // GOTO track 4
0x9F + 3,   // DELAY: ticks = 3
0xFC, 5,    // GOTO track 5
0x9F + 2,   // DELAY: ticks = 2
0xFC, 4,    // GOTO track 4
0x9F + 1,   // DELAY: ticks = 1
0xFC, 4,    // GOTO track 4
0x9F + 1,   // DELAY: ticks = 1
0xFE,     // RETURN
//"Track empty32"
0x00 + 0,   // NOTE ON: note = 0
0x9F + 32,    // DELAY: ticks = 32
0xFE,     // RETURN
//"Track drum65"
0x9F + 64,    // DELAY: ticks = 64
0xFE,     // RETURN

};


Song music2[] = {                // total song in bytes = 78 
  //                            // setup bytes 17
  0x06,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0
  0x03, 0x00,                   // Address of track 1
  0x0B, 0x00,                   // Address of track 2
  0x20, 0x00,                   // Address of track 3
  0x24, 0x00,                   // Address of track 4
  0x36, 0x00,                   // Address of track 5
  
  0x01,                         // Channel 0 entry track (PULSE)
  0x00,                         // Channel 1 entry track (SQUARE)
  0x00,                         // Channel 2 entry track (TRIANGLE)
  0x03,                         // Channel 3 entry track (NOISE)

  //"Track 0"                   // ticks = 0 / bytes = 3
  0x40, 0,                      // FX: SET VOLUME: volume = 0
  0x9F,                         // FX: STOP CURRENT CHANNEL

  //"Track 1"                   // ticks = 3072 / bytes = 8
  0x9D, 50,                     // SET song tempo: value = 50
  0x40, 63,                     // FX: SET VOLUME: volume = 63
  0xFD, 31, 2,                  // REPEAT: count = 31 + 1 / track = 2 (32 * 96 ticks)
  0x9F,                         // FX: STOP CURRENT CHANNEL

  //"Track 2"                   // ticks = 96 / bytes = 21
  0x00 + 24,                    // NOTE ON: note = 24
  0x9F + 24,                    // DELAY: 24 ticks
  0x00 + 36,                    // NOTE ON: note = 36
  0x47, 0x43, 0x00 + 0x00 + 0,  // FX: ARPEGGIO ON: notes =  +4 +3 / don't play third note = OFF / ritrigger = OFF / ticks = 0
  0x9F +  8,                    // DELAY: 8 ticks
  0x00,                         // NOTE OFF
  0x48,                         // FX: ARPEGGIO OFF
  0x9F + 16,                    // DELAY: 16 ticks
  0x00 + 22,                    // NOTE ON: note = 22
  0x9F + 24,                    // DELAY: 24 ticks
  0x00 + 34,                    // NOTE ON: note = 34
  0x47, 0x43, 0x00 + 0x00 + 0,  // FX: ARPEGGIO ON: notes =  +4 +3 / don't play third note = OFF / ritrigger = OFF / ticks = 0
  0x9F +  8,                    // DELAY: 8 ticks
  0x00,                         // NOTE OFF
  0x48,                         // FX: ARPEGGIO OFF
  0x9F + 16,                    // DELAY: 16 ticks
  0xFE,                         // RETURN

  //"Track 3"                   // ticks = 3072 / bytes = 4
  0xFD, 31, 4,                  // REPEAT: count = 31 + 1 / track = 4  (32 * 96 ticks)
  0x9F,                         // FX: STOP CURRENT CHANNEL

  //"Track 4"                   // ticks = 96 / bytes = 18
  0xFD, 1, 5,                   // REPEAT: count = 1 + 1 / track = 5  (24 ticks)
  0x9F + 12,                    // DELAY: 12 ticks
  0xFD, 1, 5,                   // REPEAT: count = 1 + 1 / track = 5  (24 ticks)
  0x9F + 12,                    // DELAY: 12 ticks
  0x49, 4 + 0,                  // FX: RETRIG NOISE: point = 1 (*4) / speed = 0 (fastest)
  0x40, 48,                     // FX: SET VOLUME: volume = 63
  0x42, -8, 1,                  // FX: VOLUME SLIDE ON: steps = -8
  0x9F + 24,                    // DELAY:  24 ticks
  0x4A,                         // FX: RETRIG: off
  0xFE,                         // RETURN

  //"Track 5"                   // ticks = 12 / bytes = 7
  0x40, 48,                     // FX: SET VOLUME: volume = 48
  0x42, -16, 1,                 // FX: VOLUME SLIDE ON: steps = -16 / every 1 ticks
  0x9F + 12,                    // DELAY: 12 ticks
  0xFE,                         // RETURN

};


#endif
