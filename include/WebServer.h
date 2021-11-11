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
    String idx;
    String brightness;
    String speed;
    String dynamic;
    String left;
    String palette;
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

    AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/json", [&](AsyncWebServerRequest *request, JsonVariant &json)
                                                                           {
                                                                               JsonObject jsonObj = json.as<JsonObject>();
                                                                               String palette = jsonObj.getMember("palette");
                                                                               String brightness = jsonObj.getMember("brightness");
                                                                               String speed = jsonObj.getMember("speed");
                                                                               String dynamic = jsonObj.getMember("dynamic");
                                                                               String left = jsonObj.getMember("left");
                                                                               String idx = jsonObj.getMember("idx");

                                                                               this->anyData = "json";
                                                                               this->palette = palette;
                                                                               this->brightness = brightness;
                                                                               this->speed = speed;
                                                                               this->dynamic = dynamic;
                                                                               this->left = left;
                                                                               this->idx = idx;

                                                                               request->send(200, "text/plain", "success");
                                                                           });

    this->server.addHandler(handler);
}

#endif