#ifndef __APP_DATA_H__
#define __APP_DATA_H__

#include <Arduino.h>

struct AppData
{
  bool status;
  String key;
  int val;
};

class Params
{
private:
  AppData *data;
  size_t num;
  bool newCustomColor;

public:
  String customColorData;
  Params();
  Params(int b, int p, int s, int d, int l);
  ~Params();
  int getValue(String key);
  bool getStatus(String key);
  void setValue(String key, int val);
  void setStatus(String key, bool status);
  void setAllStatus(bool status);
  void print();
  void setCustomColorData(String val);
};

#endif