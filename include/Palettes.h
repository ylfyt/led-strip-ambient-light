#ifndef __PALETTE_H__

#include <FastLED.h>
#include "Gradient.h"

class Palettes
{
private:
    /* data */
public:
    static CRGBPalette16 realSunset;
    static CRGBPalette16 alarm;
    static CRGBPalette16 spainFlag;
};

CRGBPalette16 Palettes::realSunset = Sunset_Real_gp;
CRGBPalette16 Palettes::alarm = alarm_p2_1_0_gp;
CRGBPalette16 Palettes::spainFlag = spanish_flag_gp;

#endif