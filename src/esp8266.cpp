#include "esp8266.hpp"
#include "config.hpp"
#include <iostream>
#include "logger.hpp"

Esp8266::Esp8266()
{
    m_status = Status::EMPTY;
}

Esp8266::~Esp8266()
{
}

void Esp8266::Init(ce::ceSerial *serial)
{
    m_serial = serial;
    m_status = Status::RESET;
    WrtieCmd("AT+RST");
}

void Esp8266::WrtieCmd(std::string &data)
{
    std::string value = data + "\r\n";
    m_serial->Write(value.c_str());
}

void Esp8266::WrtieCmd(const char *data)
{
    std::string value(data);
    this->WrtieCmd(value);
}

void Esp8266::HandleInputData(std::string &data)
{
    switch (m_status)
    {
    case Status::RESET:
        HandleReset(data);
        break;
    case Status::SETCWMODE:
        HandleCWMODE(data);
        break;
    case Status::HANDLEWIFICONNECTED:
        HandleWifiConneted(data);
        break;
    case Status::GETIP:
        ParseIP(data);
        break;
    case Status::SETUDPSERVER:
        HanldeCPDInfo(data);
        break;
    case Status::READYTOREAD:
        SetServerIP(data);
    default:
        break;
    }
}

void Esp8266::HandleReset(std::string &data)
{
    if (data.find("ready") != std::string::npos)
    {
        Logger::log("Restaring!");
        m_status = Status::SETCWMODE;
        this->WrtieCmd("AT+CWMODE=1");
    }
}

void Esp8266::HandleCWMODE(std::string &data)
{
    if (isOk(data))
    {
        Logger::log("Connecting to WiFi!");
        std::string cmd = "AT+CWJAP=\"" + std::string(WIFINANE) + "\",\"" + std::string(WIFIPASSWORD) + "\"";
        this->WrtieCmd(cmd);
        m_status = Status::HANDLEWIFICONNECTED;
    }
}

void Esp8266::HandleWifiConneted(std::string &data)
{
    if (isOk(data))
    {
        Logger::log("Getting IP address");
        this->WrtieCmd("AT+CIFSR");
        m_status = Status::GETIP;
    }
}

void Esp8266::ParseIP(std::string &data)
{
    if (data.find("CIFSR:STAIP") != std::string::npos)
    {
        GetValueFromRecivedData(data, m_ip);
        Logger::log("My ip: " + m_ip);
        m_ipCallback(m_ip);
    }
    if (isOk(data))
    {
        std::string cmd = "AT+CIPSTART=\"UDP\",\"" + m_ip + "\"," + std::string(PORT) + "," + std::string(PORT) + ",2";
        this->WrtieCmd(cmd);
        m_status = Status::SETUDPSERVER;
    }
}

bool Esp8266::isOk(std::string &data)
{
    return data.find("OK") != std::string::npos;
}

void Esp8266::GetValueFromRecivedData(std::string data, std::string &stringToSet)
{
    stringToSet.erase();
    bool push = false;
    for (size_t i = 0; i < data.size(); i++)
    {
        if (push)
        {
            if (data.at(i) == '"')
            {
                return;
            }
            stringToSet.push_back(data.at(i));
        }
        if (data.at(i) == '"')
        {
            push = true;
        }
    }
}

void Esp8266::HanldeCPDInfo(std::string &data)
{
    if (isOk(data))
    {
        Logger::log("ESP READY! :D");
        WrtieCmd("AT+CIPDINFO=1");
        m_status = Status::READYTOREAD;
    }
}

void Esp8266::SetIpCallback(std::function<void(std::string &)> callback)
{
    m_ipCallback = callback;
}

void Esp8266::SetServerIP(std::string &data)
{
    if (data.find("+IPD") != std::string::npos)
    {
        auto items = split(data, ',');
        if (items.size() > 2)
        {
            m_serverIp = items.at(2);
            auto port = split(items.at(3), ':');
            m_serverPort = port.at(0);
            WrtieCmd("AT+CIPDINFO=0");
            std::cout << m_serverIp << " " << m_serverPort << std::endl;
        }
    }
}