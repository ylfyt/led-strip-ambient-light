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

	if (!toogle)
	{
		if (millis() > 15000)
		{
			CRGBPalette16 cusPalette;
			byte cus[] =
				{0, 0, 255, 0,
				 255, 255, 0, 0};

			cusPalette.loadDynamicGradientPalette(cus);
			animator.setPalette(cusPalette);
			toogle = true;

			Serial.print("ESP.getBootMode(); ");
			Serial.println(ESP.getBootMode());
			Serial.print("ESP.getSdkVersion(); ");
			Serial.println(ESP.getSdkVersion());
			Serial.print("ESP.getBootVersion(); ");
			Serial.println(ESP.getBootVersion());
			Serial.print("ESP.getChipId(); ");
			Serial.println(ESP.getChipId());
			Serial.print("ESP.getFlashChipSize(); ");
			Serial.println(ESP.getFlashChipSize());
			Serial.print("ESP.getFlashChipRealSize(); ");
			Serial.println(ESP.getFlashChipRealSize());
			Serial.print("ESP.getFlashChipSizeByChipId(); ");
			Serial.println(ESP.getFlashChipSizeByChipId());
			Serial.print("ESP.getFlashChipId(); ");
			Serial.println(ESP.getFlashChipId());
			Serial.print("ESP.getFreeHeap(); ");
			Serial.println(ESP.getFreeHeap());
		}
	}
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