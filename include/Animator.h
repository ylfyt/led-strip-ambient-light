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

#endif