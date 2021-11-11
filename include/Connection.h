#ifndef __CONNECTION_H__

#include <ESP8266WiFi.h>

class Connection
{
private:
    char *ssid = "ssid";
    char *password = "password";

public:
    Connection(char *ssid, char *password);
    ~Connection();
    void connect();
};

Connection::Connection(char *ssid, char *password)
{
    this->ssid = ssid;
    this->password = password;
}

Connection::~Connection()
{
}

void Connection::connect()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid, this->password);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.print(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
    Serial.println();
    Serial.print("Connected http://");
    Serial.println(WiFi.localIP());
}

#endif