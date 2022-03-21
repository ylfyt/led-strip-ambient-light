#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__

#include <FastLED.h>

class Animator
{
private:
    CRGB *leds;
    CRGBPalette16 palette;
    CRGBPalette16 targetPalette;
    int num;
    int maxBrightness;
    int brightness;
    bool dynamic;
    bool leftDir;
    int speed;
    byte paletteIndex;
    long prev;

public:
    Animator(int, int, int, bool);
    ~Animator();
    void setBrightness(int);
    void run();
    void setPalette(CRGBPalette16);
    void setDirection(bool);
    void refresh();
    int getSpeed();
    void setDynamic(bool dynamic);
    void setSpeed(int speed);
    void begin(CRGBPalette16);
};

void Animator::setSpeed(int speed)
{
    this->speed = speed;
}

void Animator::setDynamic(bool dynamic)
{
    this->dynamic = dynamic;
}

int Animator::getSpeed()
{
    return this->speed;
}

void Animator::setDirection(bool left)
{
    this->leftDir = left;
}

Animator::Animator(int num, int maxBrightness, int brightness = 50, bool dynamic = false) : leds(new CRGB[num])
{
    this->num = num;
    this->maxBrightness = maxBrightness;
    this->brightness = (int)255 * ((float)brightness / 100);
    this->dynamic = dynamic;
    this->leftDir = true;
    this->paletteIndex = 0;
    this->speed = 10;
    this->prev = 0;
}

Animator::~Animator()
{
}

void Animator::begin(CRGBPalette16 defaultPalette)
{
    this->palette = defaultPalette;
    this->targetPalette = defaultPalette;
    FastLED.addLeds<WS2812B, D2, GRB>(this->leds, this->num);
    FastLED.setBrightness(this->maxBrightness);
    this->refresh();
}

void Animator::setBrightness(int val)
{
    if (val > 100)
        val = 100;
    else if (val < 0)
        val = 0;
    float persen = (float)val / 100;
    this->brightness = (int)255 * persen;
    this->refresh();
}

void Animator::setPalette(CRGBPalette16 pal)
{
    this->targetPalette = pal;
    this->refresh();
}

void Animator::run()
{
    if (dynamic)
    {
        long curr = millis();
        if (curr - this->prev >= this->speed)
        {
            this->prev = curr;
            if (this->leftDir)
                this->paletteIndex--;
            else
                this->paletteIndex++;
        }
    }
    else
    {
        if (this->paletteIndex != 0)
        {
            long curr = millis();
            if (curr - this->prev >= this->speed)
            {
                this->prev = curr;
                if (this->leftDir)
                    this->paletteIndex--;
                else
                    this->paletteIndex++;
            }
        }
    }
    this->refresh();
}

void Animator::refresh()
{

    nblendPaletteTowardPalette(this->palette, this->targetPalette, 10);
    fill_palette(this->leds, this->num, this->paletteIndex, 255 / this->num, this->palette, this->brightness, LINEARBLEND);
    FastLED.show();
}

#endif