#ifndef __APP_DATA_H__

#include <Arduino.h>

struct AppData
{
    bool status;
    String brightness;
    String idx;
    String speed;
    String dynamic;
    String left;
    String palette;
};

#endif