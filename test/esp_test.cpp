#include <gtest/gtest.h>
#include <iostream>

#define protected public
#define private public
#include "esp8266.hpp"
#include "Serial/ceSerial.h"
#undef protected
#undef private

using namespace ce;

class blakUart : public ceSerial
{
private:
    /* data */
public:
    blakUart(/* args */) {}
    ~blakUart() {}
    bool Write(const char *data) {}
};

void dummyCallback(std::string &val)
{
}
static blakUart UartBlank;

Esp8266 createEsp()
{
    Esp8266 esp;
    esp.Init(&UartBlank);
    esp.SetIpCallback(dummyCallback);
    return esp;
}

TEST(ESP, TestEmpty)
{
    Esp8266 esp;
    ASSERT_EQ(esp.m_status, Esp8266::Status::EMPTY);
}

TEST(ESP, InitTest)
{
    Esp8266 esp;
    esp.Init(&UartBlank);
    ASSERT_EQ(esp.m_status, Esp8266::Status::RESET);
}

TEST(ESP, ParseIP_Simple)
{
    std::string data = "+CIFSR:STAIP,\"192.168.0.183\"";
    auto esp = createEsp();
    esp.ParseIP(data);
    ASSERT_EQ(esp.m_ip, "192.168.0.183");
}

TEST(ESP, ParseIP_Empty)
{
    std::string data = "";
    auto esp = createEsp();
    esp.ParseIP(data);
    ASSERT_EQ(esp.m_ip, "");
}

TEST(ESP, GetValueFromRecivedData_Simple)
{
    std::string data = "asdasddas\"testowa\"";
    auto esp = createEsp();
    std::string valueToGet;
    esp.GetValueFromRecivedData(data, valueToGet);
    ASSERT_EQ("testowa", valueToGet);
}

TEST(ESP, GetValueFromRecivedData_Empty)
{
    std::string data = "";
    auto esp = createEsp();
    std::string valueToGet;
    esp.GetValueFromRecivedData(data, valueToGet);
    ASSERT_EQ("", valueToGet);
}

TEST(ESP, GetSeverIP)
{
    std::string data = "+IPD,12,192.168.0.154,4567:servo=10asd";
    auto esp = createEsp();
    esp.SetServerIP(data);
    ASSERT_EQ(esp.m_serverIp, "192.168.0.154");
    ASSERT_EQ(esp.m_serverPort, "4567");
}