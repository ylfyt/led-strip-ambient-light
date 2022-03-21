#ifndef __GRADIENT_H__
#define __GRADIENT_H__

#include <FastLED.h>

// Gradient palette "bhw3_54_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_54.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw3_54_gp){
    0, 72, 117, 123,
    40, 117, 168, 182,
    101, 167, 176, 149,
    158, 220, 231, 95,
    216, 234, 103, 166,
    255, 173, 99, 135};

// Gradient palette "bhw1_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_01_gp){
    0, 227, 101, 3,
    117, 194, 18, 19,
    255, 92, 8, 192};

// Gradient palette "bhw1_13_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_13.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_13_gp){
    0, 255, 255, 45,
    255, 157, 57, 197};

// Gradient palette "bhw1_hello_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_hello.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_hello_gp){
    0, 237, 156, 197,
    35, 244, 189, 230,
    56, 255, 255, 255,
    79, 244, 189, 230,
    109, 237, 156, 197,
    160, 121, 255, 255,
    196, 255, 255, 255,
    255, 121, 255, 255};

// Gradient palette "Yellow_Orange_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ggr/tn/Yellow_Orange.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Yellow_Orange_gp){
    0, 255, 199, 0,
    34, 255, 121, 0,
    144, 255, 63, 0,
    241, 222, 51, 1,
    255, 194, 39, 1};

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