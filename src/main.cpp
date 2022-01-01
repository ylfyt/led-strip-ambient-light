#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include <AsyncJson.h>
#include <ArduinoJson.h>

#include "Connection.h"
#include "WebServer.h"
#include "Animator.h"

int count = 0;
int NUM_PALETTES = sizeof(Palettes) / sizeof(Palettes[0]);

bool newData = false;

Connection conn(WIFI_SSID, WIFI_PASSWORD);
WebServer server(80);

Params params(
	DEFAULT_BRIGHTNESS,
	DEFAULT_PALETTE,
	DEFAULT_SPEED,
	DEFAULT_DYNAMIC,
	DEFAULT_LEFT);
Animator animator(100, 100, params.getValue("b"), params.getValue("d"));

void parseData();
void updateData();
void changePalette(int idx);
void stringToPalette(String data);

bool toogle = false;

void setup()
{
	Serial.begin(9600);
	server.begin();
	conn.begin();

	animator.begin(Palettes[params.getValue("p")]);
	server.params = params;
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

	if (params.getStatus("c"))
	{
		String data = params.customColorData;
		stringToPalette(data);
	}
}

void stringToPalette(String data)
{
	int num = 0;
	for (size_t i = 0; i < data.length(); i++)
	{
		if (data[i] == ',')
			num++;
	}

	if (num < 7 || (num + 1) % 4 != 0)
	{
		return;
	}

	byte colors[num];

	char *input = (char *)data.c_str();
	char separator[] = ",";
	char *token;

	token = strtok(input, separator);
	byte idx = 0;
	// Find any more?
	while (token != NULL)
	{
		byte px = atoi(token);
		colors[idx++] = px;
		token = strtok(NULL, separator);
	}

	CRGBPalette16 cusPalette;
	cusPalette.loadDynamicGradientPalette(colors);
	animator.setPalette(cusPalette);
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