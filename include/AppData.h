#ifndef __APP_DATA_H__

#include <Arduino.h>

struct AppData
{
    bool status;
    String key;
    int val;
};

class Params
{
private:
    AppData *data;
    size_t num;
    bool newCustomColor;

public:
    String customColorData;
    Params();
    Params(int b, int p, int s, int d, int l);
    ~Params();
    int getValue(String key);
    bool getStatus(String key);
    void setValue(String key, int val);
    void setStatus(String key, bool status);
    void setAllStatus(bool status);
    void print();
    void setCustomColorData(String val);
};

Params::Params() : data(new AppData[5])
{
    this->num = 5;
    this->data[0] = {false, "b", 0};
    this->data[1] = {false, "p", 0};
    this->data[2] = {false, "s", 0};
    this->data[3] = {false, "d", 0};
    this->data[4] = {false, "l", 0};
}

Params::Params(int b, int p, int s, int d, int l) : data(new AppData[5])
{
    this->num = 5;
    this->data[0] = {false, "b", b};
    this->data[1] = {false, "p", p};
    this->data[2] = {false, "s", s};
    this->data[3] = {false, "d", d};
    this->data[4] = {false, "l", l};
}

void Params::print()
{
    String data = "";
    for (size_t i = 0; i < this->num; i++)
    {
        String temp = "[";
        temp += this->data[i].key + "," + this->data[i].status + "," + this->data[i].val;
        temp += "]";
        data += temp + " | ";
    }
    Serial.println(data);
}

void Params::setAllStatus(bool status)
{
    for (size_t i = 0; i < this->num; i++)
    {
        this->data[i].status = status;
    }
    this->newCustomColor = false;
}

int Params::getValue(String key)
{
    for (size_t i = 0; i < this->num; i++)
    {
        if (this->data[i].key == key)
            return this->data[i].val;
    }

    return -1;
}

bool Params::getStatus(String key)
{
    for (size_t i = 0; i < this->num; i++)
    {
        if (this->data[i].key == key)
            return this->data[i].status;
    }

    if (key == "c")
    {
        return this->newCustomColor;
    }

    return false;
}

void Params::setValue(String key, int val)
{
    for (size_t i = 0; i < this->num; i++)
    {
        if (this->data[i].key == key)
        {
            this->data[i].val = val;
            return;
        }
    }
}

void Params::setCustomColorData(String val)
{
    customColorData = val;
    this->newCustomColor = true;
}

void Params::setStatus(String key, bool status)
{
    for (size_t i = 0; i < this->num; i++)
    {
        if (this->data[i].key == key)
        {
            this->data[i].status = status;
            return;
        }
    }
}

Params::~Params()
{
}

#endif