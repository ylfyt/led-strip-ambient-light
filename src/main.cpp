#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "Connection.h"
#include "Animator.h"
#include "Palettes.h"

Connection conn("ya", "12345678y");
Animator animator(40, 100);

int count = 0;

long prev = 0;

void setup()
{
	Serial.begin(9600);
	animator.begin(Palettes::realSunset);
}

void loop()
{
	conn.checkConnection();
	animator.run();
}