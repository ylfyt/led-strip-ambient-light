#ifndef __PALETTE_H__

#include <FastLED.h>
#include "Gradient.h"

class Palettes
{
private:
    /* data */
public:
    static CRGBPalette16 realSunset;
};

CRGBPalette16 Palettes::realSunset = Sunset_Real_gp;

#endif