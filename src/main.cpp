#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include <AsyncJson.h>
#include <ArduinoJson.h>

#include "Connection.h"
#include "WebServer.h"
#include "Animator.h"
#include "Palettes.h"
#include "AppData.h"

Connection conn("ya", "12345678y");
Animator animator(100, 100, 40);
WebServer server(80);

int count = 0;
int NUM_PALETTES = sizeof(Palettes) / sizeof(Palettes[0]);

AppData data;

void parseData();
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

	if (data.status)
	{
		data.status = false;
		int val = data.brightness.toInt();
		animator.setBrightness(val);

		bool dynamic = data.dynamic.toInt() == 1;
		animator.setDynamic(dynamic);

		bool left = data.left.toInt() == 1;
		animator.setDirection(left);

		int speed = data.speed.toInt();
		animator.setSpeed(speed);

		int idx = data.idx.toInt();
		changePalette(idx);
	}

	if (server.anyData != "")
	{
		parseData();
	}

	animator.run();
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
	if (server.anyData == "json")
	{
		server.anyData = "";
		data = {true, server.brightness, server.idx, server.speed, server.dynamic, server.left, server.palette};
	}
}