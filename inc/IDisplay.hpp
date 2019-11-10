#pragma once
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <string>

using namespace std;

class IDisplay
{
private:
    int address;
    string wlanIP;
    string espIP;

public:
    int fd;

    int getAddress()
    {
        return address;
    }

    void setWlanIP(string &value)
    {
        wlanIP = "W:" +value;
        Draw();
    }

    void setEspIP(string &value)
    {
        espIP = "E:" + value;
        Draw();
    }

    const string &getEspIP() const
    {
        return espIP;
    }

    const string &getWlanIP() const
    {
        return wlanIP;
    }

    virtual void Draw() {}
    virtual void Init() {}
    IDisplay(int _address);
    virtual ~IDisplay();
};
