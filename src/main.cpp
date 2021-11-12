#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include <AsyncJson.h>
#include <ArduinoJson.h>

#include "Connection.h"
#include "WebServer.h"
#include "Animator.h"
#include "Palettes.h"

Connection conn("ya", "12345678y");
Animator animator(100, 100, 20);
WebServer server(80);

int count = 0;
int NUM_PALETTES = sizeof(Palettes) / sizeof(Palettes[0]);

Params params;
bool newData = false;

void parseData();
void updateData();
void changePalette(int idx);

void setup()
{
	Serial.begin(9600);
	server.begin();
	animator.begin(Palettes[2]);
}

void loop()
{
	conn.checkConnection();

	if (newData)
	{
		newData = false;
		updateData();
	}

	if (server.anyReq)
	{
		server.anyReq = false;
		parseData();
	}

	animator.run();
}

void updateData()
{
	if (params.getStatus("p"))
	{
		int val = params.getValue("p");
		changePalette(val);
	}

	if (params.getStatus("b"))
	{
		int val = params.getValue("b");
		animator.setBrightness(val);
	}

	if (params.getStatus("d"))
	{
		bool val = params.getValue("d");
		animator.setDynamic(val);
	}

	if (params.getStatus("l"))
	{
		bool val = params.getValue("l");
		animator.setDirection(val);
	}

	if (params.getStatus("s"))
	{
		int val = params.getValue("s");
		animator.setSpeed(val);
	};
}

void changePalette(int idx)
{
	if (idx < 0)
		idx = 0;
	else if (idx > NUM_PALETTES - 1)
		idx = NUM_PALETTES - 1;

	animator.setPalette(Palettes[idx]);
}

void parseData()
{
	params = server.params;
	newData = true;
}