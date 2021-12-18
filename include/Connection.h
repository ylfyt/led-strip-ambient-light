#ifndef __CONNECTION_H__

#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <HTTPSRedirect.h>
#include "EEPROM.h"
#include "credential.h"

struct IPDevice
{
    byte x1;
    byte x2;
    byte x3;
    byte x4;
    byte isIpDBUptodate;
};

String getString(IPDevice ip)
{
    return String(ip.x1) + "." + String(ip.x2) + "." + String(ip.x3) + "." + String(ip.x4);
}

class Connection
{
private:
    String ssid;
    String password;
    IPDevice prevIP;
    int connectionState;
    HTTPSRedirect client;
    bool isIpEEPROMUptodate;

public:
    Connection(String, String);
    ~Connection();
    void connect();
    void reconnect();
    bool isConnect();
    void checkConnection();
    void begin();
    void updateIPEEPROM();
    bool checkPrevIP(IPAddress ip);
    void pushIpToDB();
};

Connection::Connection(String ssid, String pass) : client(443)
{
    this->ssid = ssid;
    this->password = pass;
    this->connectionState = 0;
    WiFi.mode(WIFI_STA);
    client.setInsecure();
}

Connection::~Connection()
{
}

void Connection::begin()
{
    EEPROM.begin(512);

    IPDevice ip;
    EEPROM.get(0, ip);

    this->prevIP = ip;
    this->isIpEEPROMUptodate = true;
    Serial.println();
    Serial.println("Get IP from EEPROM: " + getString(ip) + " DB:" + String(ip.isIpDBUptodate));
}

void Connection::connect()
{
    if (this->connectionState == 0)
    {
        this->connectionState = 1;

        // IPAddress local_ip(192, 168, 50, 100);
        // IPAddress gateway(192, 168, 5, 244);
        // IPAddress subnet(255, 255, 0, 0);
        // IPAddress primaryDNS(8, 8, 8, 8);
        // IPAddress secondaryDNS(8, 8, 4, 4);
        // if (!WiFi.config(local_ip, gateway, subnet, primaryDNS, secondaryDNS))
        // {
        //     Serial.println("STA Failed to configure");
        // }

        WiFi.begin(this->ssid.c_str(), this->password.c_str());
        Serial.println();
        Serial.print("Connecting to ");
        Serial.print(ssid);
        Serial.print("...");
    }

    EVERY_N_MILLISECONDS(100)
    {
        Serial.print(".");
    }
}

void Connection::reconnect()
{
    if (this->connectionState == 2)
    {
        this->connectionState = 0;
        WiFi.disconnect();
        Serial.println("Connection Lost!!");
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
            IPAddress ip = WiFi.localIP();
            Serial.println(WiFi.localIP());
            Serial.println();

            this->isIpEEPROMUptodate = this->checkPrevIP(ip);
        }

        if (!this->isIpEEPROMUptodate)
        {
            this->updateIPEEPROM();
        }

        if (this->isIpEEPROMUptodate)
        {
            if (!this->prevIP.isIpDBUptodate)
            {
                this->pushIpToDB();
            }
        }
    }
}

void Connection::updateIPEEPROM()
{
    Serial.println("Updating IP to EEPROM ...");
    EEPROM.put(0, this->prevIP);
    if (EEPROM.commit())
    {
        Serial.println("IP Updated to EEPROM: " + getString(this->prevIP) + " DB:" + String(this->prevIP.isIpDBUptodate));
        this->isIpEEPROMUptodate = true;
    }
    else
    {
        Serial.println("Failed to update IP in EEPROM");
    }
}

bool Connection::checkPrevIP(IPAddress ip)
{
    if (
        ip[0] == prevIP.x1 &&
        ip[1] == prevIP.x2 &&
        ip[2] == prevIP.x3 &&
        ip[3] == prevIP.x4)
    {
        Serial.println("IP Address is up to date");
        return true;
    }

    this->prevIP = {ip[0], ip[1], ip[2], ip[3], false};
    return false;
}

void Connection::pushIpToDB()
{
    Serial.println("Updating IP to DB");
    const char *host = "script.google.com";
    String url = GAPI_URL;

    String ip = getString(this->prevIP);
    String dataIP = "{\"name\":\"IPNODE\",\"email\":\"NODE\",\"message\":\"" + ip + "\"}";

    int conn = client.connect(host, 443);
    client.setContentTypeHeader("text/plain");
    int status = client.POST(url, host, dataIP);
    bool body = client.getResponseBody();

    if (body == true)
    {
        Serial.println("IP Updated to DB: " + ip);
        this->prevIP.isIpDBUptodate = true;
        this->isIpEEPROMUptodate = false;
    }
    else
    {
        Serial.println("DB Update Failed: " + ip);
    }
}

#endif