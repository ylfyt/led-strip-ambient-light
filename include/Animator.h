#ifndef __ANIMATOR_H__

#include <FastLED.h>

class Animator
{
private:
    CRGB leds[20];
    CRGBPalette16 palette;
    int num;
    int maxBrightness;
    int brightness;
    bool dynamic;
    bool leftDir;
    int speed;
    byte paletteIndex;

public:
    Animator(int, int);
    ~Animator();
    void setBrightness(float);
    void run();
    void setPalette(CRGBPalette16);
    void refresh();
    int getSpeed();
    void begin(CRGBPalette16);
};

int Animator::getSpeed()
{
    return this->speed;
}

Animator::Animator(int num, int maxBrightness)
{
    this->num = num;
    this->maxBrightness = maxBrightness;
    this->brightness = (int)maxBrightness * 0.1;
    this->dynamic = true;
    this->leftDir = true;
    this->paletteIndex = 0;
    this->speed = 10;
}

Animator::~Animator()
{
}

void Animator::begin(CRGBPalette16 defaultPalette)
{
    this->palette = defaultPalette;
    FastLED.addLeds<WS2812B, D2, GRB>(this->leds, this->num);
    // FastLED.setBrightness(this->brightness);
    this->refresh();
}

void Animator::setBrightness(float persen)
{
    this->brightness = (int)this->maxBrightness * persen;
    FastLED.setBrightness(this->brightness);
}

void Animator::setPalette(CRGBPalette16 pal)
{
    this->palette = pal;
    this->refresh();
}

void Animator::run()
{
    if (dynamic)
    {
        EVERY_N_MILLISECONDS(this->speed)
        {
            if (this->leftDir)
                this->paletteIndex--;
            else
                this->paletteIndex++;
            this->refresh();
        }
    }
}

void Animator::refresh()
{
    fill_palette(this->leds, this->num, this->paletteIndex, 255 / this->num, this->palette, this->brightness, LINEARBLEND);
    FastLED.show();
}

#endif