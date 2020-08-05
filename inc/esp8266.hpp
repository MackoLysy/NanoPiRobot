#pragma once
#include "Serial/ceSerial.h"
#include "helpers.hpp"
#include <functional>

class Esp8266
{
private:
    enum class Status
    {
        EMPTY,
        RESET,
        SETCWMODE,
        HANDLEWIFICONNECTED,
        GETIP,
        SETUDPSERVER,
        READYTOREAD
    };
    Status m_status;
    std::string m_ip;
    std::string m_port;
    std::string m_serverIp;
    std::string m_serverPort;
    ce::ceSerial *m_serial;
    std::function<void(std::string &)> m_ipCallback;
    void HandleReset(std::string &data);
    void HandleCWMODE(std::string &data);
    void HandleWifiConneted(std::string &data);
    void HanldeCPDInfo(std::string &data);
    void ParseIP(std::string &data);
    bool isOk(std::string &data);
    void GetValueFromRecivedData(std::string data, std::string &stringToSet);
    void SetServerIP(std::string &data);
    void SetUdpServer();
    void WrtieCmd(std::string &data);
    void WrtieCmd(const char *data);
    
public:
    Esp8266(/* args */);
    void Init(ce::ceSerial *serial);
    void HandleInputData(std::string &data);
    
    void SetIpCallback(std::function<void(std::string &)> callback);
    bool isReady()
    {
        return m_status == Status::READYTOREAD;
    }
    ~Esp8266();
};
