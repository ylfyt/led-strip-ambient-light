#ifndef __ANIMATOR_H__

#include <FastLED.h>

class Animator
{
private:
    CRGB *leds;
    CRGBPalette16 palette;
    int num;
    int maxBrightness;
    int brightness;
    bool dynamic;
    bool leftDir;
    int speed;
    byte paletteIndex;

public:
    Animator(int, int, bool);
    ~Animator();
    void setBrightness(float);
    void run();
    void setPalette(CRGBPalette16);
    void setDirection(bool);
    void refresh();
    int getSpeed();
    void begin(CRGBPalette16);
};

int Animator::getSpeed()
{
    return this->speed;
}

void Animator::setDirection(bool left)
{
    this->leftDir = left;
}

Animator::Animator(int num, int maxBrightness, bool dynamic) : leds(new CRGB[num])
{
    this->num = num;
    this->maxBrightness = maxBrightness;
    this->brightness = (int)255 * 0.5;
    this->dynamic = dynamic;
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
    FastLED.setBrightness(this->maxBrightness);
    this->refresh();
}

void Animator::setBrightness(float persen)
{
    this->brightness = (int)255 * persen;
    this->refresh();
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