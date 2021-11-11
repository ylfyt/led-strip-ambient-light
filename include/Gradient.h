#ifndef __GRADIENT_H__

#include <FastLED.h>

DEFINE_GRADIENT_PALETTE(Sunset_Real_gp){
    0, 120, 0, 0,
    22, 179, 22, 0,
    51, 255, 104, 0,
    85, 167, 22, 18,
    135, 100, 0, 103,
    198, 16, 0, 130,
    255, 0, 0, 160};

// Gradient palette "alarm_p2_1_0_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/dca/tn/alarm.p2.1.0.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 84 bytes of program space.

DEFINE_GRADIENT_PALETTE(alarm_p2_1_0_gp){
    0, 182, 255, 168,
    12, 171, 255, 138,
    25, 169, 255, 114,
    38, 177, 255, 91,
    51, 192, 255, 72,
    63, 222, 255, 54,
    76, 255, 246, 40,
    89, 255, 201, 28,
    102, 255, 156, 19,
    114, 255, 109, 11,
    127, 255, 68, 6,
    140, 255, 33, 3,
    153, 255, 10, 1,
    165, 255, 10, 1,
    178, 255, 1, 21,
    191, 255, 1, 103,
    204, 237, 1, 255,
    216, 80, 1, 255,
    229, 12, 1, 255,
    242, 1, 1, 255,
    255, 1, 39, 255};

#endif