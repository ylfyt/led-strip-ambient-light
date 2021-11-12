#ifndef __WEB_SERVER_H__

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

#include "AppData.h"

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
    this->server.begin();
}

void WebServer::routing()
{
    this->server.on("/", [&](AsyncWebServerRequest *req)
                    { req->send(200, "text/html", "<h1>hello, World</h1>"); });

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

#endif