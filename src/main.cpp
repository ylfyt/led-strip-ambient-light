#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "Connection.h"
#include "WebServer.h"
#include "Animator.h"
#include "Palettes.h"

Connection conn("ya", "12345678y");
Animator animator(20, 100);
WebServer server(80);

int count = 0;

void setup()
{
	Serial.begin(9600);
	server.begin();
	animator.begin(Palettes::spainFlag);
}

void loop()
{
	conn.checkConnection();

	// if (gs.changePalette)
	// {
	// 	// GlobalState::stopSwitch();
	// 	if (gs.paletteIdx == 0)
	// 	{
	// 		animator.setPalette(Palettes::spainFlag);
	// 	}
	// 	else if (gs.paletteIdx == 1)
	// 	{
	// 		animator.setPalette(Palettes::alarm);
	// 	}
	// 	else
	// 	{
	// 		animator.setPalette(Palettes::realSunset);
	// 	}
	// }

	animator.run();
}