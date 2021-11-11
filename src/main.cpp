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
Animator animator(20, 100);
WebServer server(80);

int count = 0;

void parseData();

void setup()
{
	Serial.begin(9600);
	server.begin();
	animator.begin(Palettes::spainFlag);
}

void loop()
{
	conn.checkConnection();

	if (server.anyData != "")
	{
		parseData();
	}

	animator.run();
}

void parseData()
{
	if (server.anyData == "json")
	{
		server.anyData = "";
		JsonObject json = server.json;
		String s = json.getMember("data");
		Serial.println(s);
	}
}