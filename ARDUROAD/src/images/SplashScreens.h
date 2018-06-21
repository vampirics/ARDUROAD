#pragma once

#include "../utils/Arduboy2Ext.h"
const unsigned char PROGMEM bootlogo[] = {
35, 35,
0x04, 0x14, 0x54, 0x51, 0x47, 0x1f, 0x7f, 0xff, 0xff, 0xfc, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x05, 0x15, 0x14, 0x51, 0x47, 0x0f, 0x3f, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xe0, 0xf0, 0xf8, 0xfc, 0x0c, 0x46, 0x16, 0x0f, 0x0f, 0x7f, 0x1f, 0x47, 0x11, 0x04, 0x01, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x14, 0x50, 0x43, 0x0f, 0x3f, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xe3, 0xe7, 0xe7, 0xc7, 0xc6, 0x45, 0x64, 0x3c, 0x40, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x90, 0x10, 0x11, 0x95, 0x14, 0x90, 0x91, 0x10, 0x10, 0x93, 0x13, 0x11, 0x95, 0x90, 0x12, 0x90, 0x91, 0x90, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x01, 0x00, 0x05, 0x06, 0x06, 0x00, 0x03, 0x04, 0x03, 0x00, 0x07, 0x02, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM SplashScreen[] = {
128, 64,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0x20, 0xc0, 0x00, 0xc0, 0x20, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xa0, 0x40, 0xc0, 0x20, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xa0, 0x40, 0x80, 0xc0, 0x20, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0x20, 0x20, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x08, 0xe4, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 
0xfc, 0xec, 0xfc, 0xec, 0xfc, 0xec, 0xfc, 0x3c, 0xc3, 0xfc, 0xff, 0xff, 0x7f, 0x03, 0x7f, 0xff, 0xff, 0xfc, 0xc3, 0x3c, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xff, 0xff, 0xff, 0x7f, 0x9e, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x03, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xef, 0xa0, 0xaf, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0x20, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0x20, 0xa0, 0xa0, 0xa0, 0x20, 0xa0, 0xa0, 0x20, 0xa0, 0x20, 0xa0, 0xa0, 0xa0, 0x20, 0x20, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 
0xef, 0xd7, 0xef, 0xd7, 0xef, 0x3f, 0xc3, 0xfc, 0xff, 0xff, 0xff, 0x7f, 0x1e, 0x5e, 0x1e, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0xc3, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x81, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0x7f, 0x3f, 0x4f, 0x70, 0x60, 0x1f, 0x7f, 0x7f, 0xff, 0xff, 0xe0, 0xe0, 0xff, 0xff, 0x7f, 0x7f, 0x1f, 0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0x03, 0x83, 0xc1, 0xe0, 0xf0, 0xf0, 0x78, 0x38, 0x38, 0x38, 0x38, 0x38, 0x78, 0xf0, 0xf0, 0xe0, 0xc0, 0x80, 0x01, 0x03, 0x07, 0x8c, 0x88, 0x8b, 0x8b, 0x88, 0x8a, 0x88, 0x8b, 0x88, 0x8a, 0x88, 0x8b, 0x8b, 0x8b, 0x88, 0x88, 0x8b, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 
0xaf, 0x5f, 0xaf, 0x5f, 0xae, 0xfe, 0x06, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0x7a, 0x7a, 0xfa, 0xfa, 0xfa, 0xf6, 0xca, 0x32, 0x7a, 0x8e, 0xf6, 0x36, 0xda, 0xea, 0x6a, 0x2a, 0xea, 0xfa, 0xf6, 0xf6, 0x8a, 0x72, 0x82, 0x7a, 0x86, 0xfa, 0xfa, 0xfa, 0x7a, 0xfa, 0xfa, 0xfa, 0x86, 0x7e, 0x86, 0xfa, 0x06, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0x7a, 0x7a, 0x7a, 0xfa, 0xfa, 0xf6, 0xea, 0x92, 0x62, 0x82, 0x01, 0x06, 0x1e, 0x7c, 0x00, 0xff, 0x38, 0xff, 0xff, 0xff, 0xc7, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc6, 0x39, 0xc7, 0xff, 0xff, 0xff, 0x38, 0x00, 0xff, 0x00, 0x40, 0xfe, 0xea, 0x7e, 0x40, 0x7e, 0x6a, 0x7e, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x6e, 0x6a, 0x7e, 0x40, 0x7e, 0x68, 0x78, 0x40, 0x40, 
0x1e, 0x0d, 0x0e, 0x85, 0x42, 0xff, 0x00, 0xff, 0xaf, 0xaf, 0xaf, 0xef, 0x28, 0x28, 0xef, 0xaf, 0xbf, 0xef, 0xd3, 0x3c, 0x00, 0xff, 0xaf, 0xaf, 0xff, 0x00, 0x3c, 0x3c, 0x00, 0xff, 0xaf, 0xaf, 0xff, 0x00, 0x87, 0xf8, 0xaf, 0xaf, 0xff, 0xcf, 0xc0, 0xcf, 0xff, 0xaf, 0xaf, 0xf8, 0x87, 0x7f, 0x00, 0xff, 0xaf, 0xaf, 0xaf, 0xff, 0x00, 0x00, 0x00, 0xff, 0xaf, 0xaf, 0xaf, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1e, 0x3c, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3d, 0x1e, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x87, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x84, 0x04, 0x04, 0x84, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x84, 0x04, 0x04, 0x84, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 
0x02, 0x01, 0x01, 0x20, 0x50, 0x4f, 0xc0, 0x5f, 0x50, 0x50, 0x50, 0x5f, 0x40, 0x40, 0x5f, 0x50, 0x50, 0x50, 0x5f, 0x50, 0x4e, 0x41, 0x4f, 0x48, 0x5d, 0x57, 0x54, 0x56, 0x57, 0x5b, 0x4c, 0x4f, 0x41, 0x58, 0x57, 0x51, 0x50, 0x5c, 0x4e, 0x42, 0x4a, 0x42, 0x4e, 0x5c, 0x50, 0x51, 0x57, 0x58, 0x40, 0x5f, 0x50, 0x50, 0x50, 0x53, 0x52, 0x52, 0x52, 0x53, 0x50, 0x48, 0x46, 0xc9, 0x56, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x01, 0x07, 0x01, 0x00, 0x07, 0x04, 0x07, 0x00, 0x07, 0x02, 0x07, 0x00, 0x07, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x40, 0x40, 0x40, 0x51, 0x5f, 0x50, 0x40, 0x40, 0x40, 0x3f, 0x00, 0x00, 0x3f, 0x40, 0x40, 0x40, 0x5d, 0x55, 0x57, 0x40, 0x40, 0x40, 0x3f, 0x00, 0x00, 0x3f, 0x40, 0x40, 0x40, 0x55, 0x55, 0x5f, 0x40, 0x40, 0x40, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xfe, 0x01, 0x01, 0x21, 0x71, 0xf9, 0x01, 0xf9, 0x71, 0x21, 0x01, 0x01, 0x71, 0x89, 0x01, 0xf9, 0x21, 0xf9, 0x01, 0xf1, 0x29, 0xf1, 0x01, 0xf9, 0x11, 0xf9, 0x01, 0x71, 0x89, 0xc9, 0x01, 0xf9, 0xa9, 0x01, 0x01, 0x01, 0x09, 0xf9, 0x09, 0x01, 0x79, 0x81, 0x79, 0x01, 0xf9, 0x11, 0xf9, 0x01, 0xf9, 0xa9, 0x01, 0x01, 0x01, 0xfe, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0xa8, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x02, 0xe2, 0x12, 0x12, 0x02, 0xe2, 0x52, 0xe2, 0x02, 0x72, 0x52, 0xd2, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x13, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x13, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3c, 0x38, 0x30, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x20, 0x3f, 0x30, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x34, 0x34, 0x35, 0x35, 0x34, 0x35, 0x34, 0x35, 0x34, 0x35, 0x35, 0x35, 
};

const unsigned char PROGMEM RADIOOFF[] =
{
// width, height,
36, 6,
0x3f, 0x01, 0x09, 0x36, 0x00, 0x3e, 0x09, 0x09, 0x3e, 0x00, 0x3f, 0x21, 0x21, 0x1e, 0x00, 0x3f, 0x00, 0x1e, 0x21, 0x21, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x21, 0x21, 0x1e, 0x00, 0x3f, 0x09, 0x01, 0x00, 0x3f, 0x09, 0x01, 
};

const unsigned char PROGMEM ARDXStation[] =
{
// width, height,
37, 6,
0x3e, 0x09, 0x09, 0x3e, 0x00, 0x3f, 0x01, 0x09, 0x36, 0x00, 0x3f, 0x21, 0x21, 0x1e, 0x00, 0x33, 0x0c, 0x0c, 0x33, 0x00, 0x00, 0x00, 0x1a, 0x25, 0x25, 0x1a, 0x00, 0x06, 0x29, 0x29, 0x1e, 0x00, 0x20, 0x06, 0x29, 0x29, 0x1e, 
};

const unsigned char PROGMEM ROCKStation[] =
{
// width, height,
38, 6,
0x3f, 0x01, 0x09, 0x36, 0x00, 0x1e, 0x21, 0x21, 0x1e, 0x00, 0x1e, 0x21, 0x21, 0x12, 0x00, 0x3f, 0x08, 0x0c, 0x33, 0x00, 0x00, 0x00, 0x06, 0x29, 0x29, 0x1e, 0x00, 0x07, 0x08, 0x08, 0x3f, 0x00, 0x20, 0x00, 0x1e, 0x25, 0x25, 0x18, 
};
