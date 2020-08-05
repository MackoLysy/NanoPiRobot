#pragma once

#include "config.hpp"
#include "esp8266.hpp"
#include "Serial/ceSerial.h"
#include "IDisplay.hpp"
#include "HD44780_I2C.hpp"
#include "helpers.hpp"
#include "logger.hpp"
#include "Distance.hpp"
#include "motors.hpp"

#include <iostream>
#include <memory>
#include <functional>
#include <future>

class Robot
{

public:
    Robot(/* args */);
    ~Robot();
    void Start();

private:
    std::shared_ptr<IDisplay> m_display;
    Esp8266 m_esp8266;
    Distance m_distance;
    std::shared_ptr<Motors> m_motors;
    ce::ceSerial m_serial;
    bool m_success;

    void SetEspIPcallback(std::string &ip);
    void GetWlanAddress();
};
