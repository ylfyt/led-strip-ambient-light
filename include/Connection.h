#ifndef __CONNECTION_H__

#include <FastLED.h>
#include <ESP8266WiFi.h>

class Connection
{
private:
    String ssid;
    String password;
    int connectionState;

public:
    Connection(String, String);
    ~Connection();
    void connect();
    void reconnect();
    bool isConnect();
    void checkConnection();
};

Connection::Connection(String ssid, String pass)
{
    this->ssid = ssid;
    this->password = pass;
    this->connectionState = 0;
    WiFi.mode(WIFI_STA);
}

Connection::~Connection()
{
}

void Connection::connect()
{
    if (this->connectionState == 0)
    {
        this->connectionState = 1;
        WiFi.begin(this->ssid.c_str(), this->password.c_str());
        Serial.println();
        Serial.print("Connecting to ");
        Serial.print(ssid);
        Serial.print("...");
    }
}

void Connection::reconnect()
{
    if (this->connectionState == 2)
    {
        this->connectionState = 0;
        WiFi.disconnect();
        Serial.println("Connection Disconnect!");
    }

    this->connect();
}

bool Connection::isConnect()
{
    return WiFi.status() == WL_CONNECTED;
}

void Connection::checkConnection()
{
    if (!this->isConnect())
    {
        this->reconnect();
    }
    else
    {
        if (this->connectionState == 1)
        {
            this->connectionState = 2;
            Serial.println();
            Serial.print("Connected http://");
            Serial.println(WiFi.localIP());
        }
    }
}

#endif