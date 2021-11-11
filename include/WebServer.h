#ifndef __WEB_SERVER_H__

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

class WebServer
{
private:
    AsyncWebServer server;

public:
    String anyData;
    int paletteIdx;
    float brightness;
    JsonObject json;
    WebServer(int);
    ~WebServer();
    void routing();
    void begin();
};

WebServer::WebServer(int port) : server(port)
{
}

WebServer::~WebServer()
{
}

void WebServer::begin()
{
    this->routing();
    this->server.begin();
}

void WebServer::routing()
{
    this->server.on("/", [&](AsyncWebServerRequest *req)
                    { req->send(200, "text/html", "<h1>hello, World</h1>"); });

    this->server.addHandler(new AsyncCallbackJsonWebHandler(
        "/api/endpoint",
        [this](AsyncWebServerRequest *request, JsonVariant &json)
        {
            if (not json.is<JsonObject>())
            {
                request->send(400, "text/plain", "Not an object");
                return;
            }
            auto &&data = json.as<JsonObject>();

            JsonObject js = data;
            this->anyData = "json";
            this->json = js;

            if (not js["name"].is<String>())
            {
                request->send(400, "text/plain", "name is not a string");
                return;
            }
            String name = js["name"].as<String>();
            Serial.println(name);
            request->send(200, "text/plain", "ok");
        }));

    AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/json", [&](AsyncWebServerRequest *request, JsonVariant &json)
                                                                           {
                                                                               JsonObject jsonObj = json.to<JsonObject>();
                                                                               this->json = jsonObj;
                                                                               this->anyData = "json";
                                                                               request->send(200, "text/plain", "success");
                                                                           });

    this->server.addHandler(handler);
}

#endif