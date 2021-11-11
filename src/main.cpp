#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
// #include <FastLED.h>

#include "Connection.h"
#include "Animator.h"
#include "Palettes.h"

Connection conn("ya", "12345678y");
Animator animator(60, 100, Palettes::realSunset);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	conn.checkConnection();
	animator.run();
}