#ifndef __WEB_SERVER_H__

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

#include "AppData.h"
#include "Palettes.h"

class WebServer
{
private:
    AsyncWebServer server;

public:
    bool anyReq;
    Params params;
    WebServer(int);
    ~WebServer();
    void routing();
    void begin();
    String getCurrentJson();
};

WebServer::WebServer(int port) : server(port), params()
{
}

WebServer::~WebServer()
{
}

void WebServer::begin()
{
    this->routing();
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    this->server.begin();
}

void WebServer::routing()
{
    this->server.onNotFound([](AsyncWebServerRequest *request)
                            {
                                if (request->method() == HTTP_OPTIONS)
                                {
                                    request->send(200);
                                }
                                else
                                {
                                    request->send(404);
                                }
                            });

    this->server.on("/", [&](AsyncWebServerRequest *req)
                    { req->send(200, "text/html", "<h1>Hello, World</h1>"); });
    this->server.on("/current", [&](AsyncWebServerRequest *req)
                    {
                        if (!req->hasParam("pw"))
                        {
                            req->send(400, "text/plain", "Access Denied");
                            return;
                        }

                        String pw = req->getParam("pw")->value();
                        if (pw != "1234")
                        {
                            req->send(400, "text/plain", "Auth Failed");
                            return;
                        }

                        // Json Constructor
                        String json = this->getCurrentJson();

                        // params.print();
                        req->send(200, "application/json", json);
                    });

    this->server.on("/strip", HTTP_GET, [this](AsyncWebServerRequest *req)
                    {
                        if (!req->hasParam("pw"))
                        {
                            req->send(400, "text/plain", "Access Denied");
                        }
                        else
                        {
                            String pw = req->getParam("pw")->value();
                            if (pw != "1234")
                            {
                                req->send(400, "text/plain", "Auth Failed");
                                return;
                            }

                            this->params.setAllStatus(false);
                            this->anyReq = false;

                            if (req->hasParam("p"))
                            {
                                int val = req->getParam("p")->value().toInt();
                                this->params.setStatus("p", true);
                                this->params.setValue("p", val);
                                this->anyReq = true;
                            }

                            if (req->hasParam("b"))
                            {
                                int val = req->getParam("b")->value().toInt();
                                this->params.setStatus("b", true);
                                this->params.setValue("b", val);
                                this->anyReq = true;
                            }

                            if (req->hasParam("s"))
                            {
                                int val = req->getParam("s")->value().toInt();
                                this->params.setStatus("s", true);
                                this->params.setValue("s", val);
                                this->anyReq = true;
                            }

                            if (req->hasParam("d"))
                            {
                                int val = req->getParam("d")->value().toInt();

                                this->params.setStatus("d", true);
                                this->params.setValue("d", val);
                                this->anyReq = true;
                            }

                            if (req->hasParam("l"))
                            {
                                int val = req->getParam("l")->value().toInt();
                                this->params.setStatus("l", true);
                                this->params.setValue("l", val);
                                this->anyReq = true;
                            }
                            // params.print();
                            req->send(200, "text/plain", "ok");
                        }
                    });
}

String WebServer::getCurrentJson()
{
    String brightness = String(this->params.getValue("b"));
    String palette = String(this->params.getValue("p"));
    String speed = String(this->params.getValue("s"));

    String dynamic;
    if (this->params.getValue("d") == 1)
        dynamic = "on";
    else
        dynamic = "off";

    String direction;
    if (this->params.getValue("l") == 1)
        direction = "left";
    else
        direction = "right";

    int n = sizeof(palettesName) / sizeof(palettesName[0]);
    String names = "[";
    for (size_t i = 0; i < n; i++)
    {
        if (i != n - 1)
            names += "\"" + palettesName[i] + "\",";
        else
            names += "\"" + palettesName[i] + "\"";
    }
    names += "]";

    String json = "{\"dyn\":{\"dynamic\":\"" + dynamic + "\",";
    json += "\"speed\":" + speed + ",";
    json += "\"direction\":\"" + direction + "\"},";
    json += "\"pal\":{\"palette\":" + palette + ",";
    json += "\"brightness\":" + brightness + ",";
    json += "\"palettes\":" + names + "}}";

    return json;
}

#endif