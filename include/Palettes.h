#ifndef __PALETTE_H__
#define __PALETTE_H__

#include <FastLED.h>
#include "Gradient.h"

CRGBPalette16 Palettes[] = {
    Sunset_Real_gp,
    bhw3_54_gp,
    bhw1_01_gp,
    bhw1_13_gp,
    bhw1_hello_gp,
    Yellow_Orange_gp,
    alarm_p2_1_0_gp,
};

String palettesName[] = {
    "Real Sunset",
    "bhw3 54",
    "bhw1 01",
    "bhw1 13",
    "bhw1 hello",
    "Yellow Orange",
    "Alarm",
};

#endif