#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "Connection.h"
#include "Animator.h"
#include "Palettes.h"

Connection conn("ya", "12345678y");
Animator animator(60, 100, Palettes::realSunset);

int count = 0;

long prev = 0;

void setup()
{
	Serial.begin(9600);
	animator.begin();
}

void loop()
{
	conn.checkConnection();

	long curr = millis();
	EVERY_N_MILLISECONDS(1000)
	{
		// if (count % 2 != 0)
		// {
		// 	animator.setPalette(Palettes::alarm);
		// }
		// else
		// {
		// 	animator.setPalette(Palettes::realSunset);
		// }
	}

	animator.run();
}