#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>
// #include <ESP8266WiFi.h>

#include "Gradient.h"
#include "Connection.h"

#define NUM_LEDS 60
#define LED_PIN D2

CRGB leds[NUM_LEDS];
Connection conn("ya", "12345678y");

CRGBPalette16 palettes[] = {
	Sunset_Real_gp,
	alarm_p2_1_0_gp,
};

uint8_t paletteIndex = 0;

void setup()
{
	Serial.begin(9600);
	conn.connect();

	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness(50);
}

void loop()
{
	// fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, testPalette, 50, LINEARBLEND);

	// EVERY_N_MILLISECONDS(10)
	// {
	// 	paletteIndex++;
	// }

	// FastLED.show();
}