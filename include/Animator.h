#ifndef __ANIMATOR_H__

#include <FastLED.h>

class Animator
{
private:
    CRGB *leds;
    CRGBPalette16 palette;
    int num;
    int maxBrightness;
    float brightness;
    bool dynamic;
    bool leftDir;
    int speed;
    byte paletteIndex;

public:
    Animator(int, int, CRGBPalette16);
    ~Animator();
    void setBrightness(float);
    void run();
    void setPalette(CRGBPalette16);
    void refresh();
};

Animator::Animator(int num, int maxBrightness, CRGBPalette16 defaultPalette) : leds(new CRGB[num])
{
    this->num = num;
    this->maxBrightness = maxBrightness;
    this->brightness = 0.1;
    this->dynamic = true;
    this->leftDir = true;
    this->paletteIndex = 0;
    this->palette = defaultPalette;
    this->speed = 10;

    FastLED.addLeds<WS2812B, D2, GRB>(leds, num);
    FastLED.setBrightness(this->maxBrightness * this->brightness);
    this->setPalette(defaultPalette);
}

Animator::~Animator()
{
}

void Animator::setBrightness(float brightness)
{
    this->brightness = brightness;
    FastLED.setBrightness(this->maxBrightness * brightness);
}

void Animator::setPalette(CRGBPalette16 pal)
{
    this->palette = pal;
    fill_palette(this->leds, this->num, this->paletteIndex, 255 / this->num, this->palette, this->maxBrightness * this->brightness, LINEARBLEND);
    FastLED.show();
}

void Animator::run()
{
    if (dynamic)
    {
        EVERY_N_MILLISECONDS(this->speed)
        {
            this->refresh();
        }
    }
}

void Animator::refresh()
{
    // Serial.println(this->maxBrightness * this->brightness);
    fill_palette(this->leds, this->num, this->paletteIndex, 255 / this->num, this->palette, this->maxBrightness * this->brightness, LINEARBLEND);
    if (this->leftDir)
        this->paletteIndex--;
    else
        this->paletteIndex++;
    FastLED.show();
}

#endif