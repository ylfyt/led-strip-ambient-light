#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "Connection.h"
#include "Animator.h"
#include "Palettes.h"

Connection conn("ya", "12345678y");
Animator animator(40, 100, true);

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

	// EVERY_N_MILLISECONDS(1000)
	// {
	// 	if (count == 0)
	// 	{
	// 		count = 1;
	// 		animator.setPalette(Palettes::alarm);
	// 	}
	// 	else
	// 	{
	// 		count = 0;
	// 		animator.setPalette(Palettes::spainFlag);
	// 	}
	// }

	animator.run();
}