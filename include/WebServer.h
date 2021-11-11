#ifndef __WEB_SERVER_H__

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

class WebServer
{
private:
    AsyncWebServer server;

public:
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
    this->server.on("/", [](AsyncWebServerRequest *req)
                    { req->send(200, "text/html", "<h1>hello, World</h1>"); });
    this->server.on("/switch", [](AsyncWebServerRequest *req)
                    {
                        if (req->hasParam("palette"))
                        {
                            AsyncWebParameter *param = req->getParam("palette");
                            String index = param->value();
                            int paletteIndex = index.toInt();
                            // TODO: Notify change palette
                        }
                        req->send(200, "text/plain", "Success");
                    });
}

#endif