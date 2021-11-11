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
Animator animator(20, 100);
WebServer server(80);

int count = 0;

AppData data;

void parseData();
void explode(String temp, char del, int *data, int n);
int countN(String temp, char del);

void setup()
{
	Serial.begin(9600);
	server.begin();
	animator.begin(Palettes::spainFlag);
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

		String temp = data.palette;
		temp = temp.substring(1, temp.length() - 1);

		int n = countN(temp, ',');
		int data[n];
		explode(temp, ',', data, n);
	}

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
		data = {true, server.brightness, server.idx, server.speed, server.dynamic, server.left, server.palette};
	}
}

int countN(String temp, char del)
{
	if (temp.length() == 0)
		return 0;
	else
	{
		int n = 1;
		for (size_t i = 0; i < temp.length(); i++)
		{
			if (temp[i] == del)
			{
				n++;
			}
		}
		return n;
	}
}

void explode(String temp, char del, int *data, int n)
{
	int idx = 0;
	String a = "";
	for (size_t i = 0; i < temp.length(); i++)
	{
		if (temp[i] == del)
		{
			int aa = a.toInt();
			a = "";
			data[idx++] = aa;
		}
		else
		{
			a += temp[i];
		}
	}
	data[idx++] = a.toInt();
}

CRGBPalette16 makePalette(int *data)
{
	CRGB::Magenta;
}
