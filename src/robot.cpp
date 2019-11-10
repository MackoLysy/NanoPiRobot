#include "robot.hpp"

Robot::Robot(/* args */)
{

    m_display = make_shared<HD44780_I2C>(DISPLAY_I2C_ADDR);
    getWlanAddress();
    auto f = std::bind(&Robot::setEspIPcallback, this, std::placeholders::_1);
    m_esp8266.SetIpCallback(f);
    m_distance.getDistance(90);
}

Robot::~Robot()
{
    Logger::log("Destorying!");
}

void Robot::Start()
{
    if (m_serial.Open() != 0)
    {
        Logger::log("Zjebalo sie w serialu!");
        return;
    }
    m_esp8266.Init(&m_serial);
    while (1)
    {
        //std::cout << "Waiting for Data..." << std::endl;
        auto data = m_serial.ReadString(m_success);
        std::cout << data;
        if (m_success)
        {
            m_esp8266.HandleInputData(data);
        }
    }
}

void Robot::setEspIPcallback(std::string &ip)
{
    m_display->setEspIP(ip);
}

void Robot::getWlanAddress()
{
    std::thread([&] {
        std::string temp;
        int iter = 0;
        while (temp.empty())
        {
            temp = getIPAddress();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            iter++;
            if (iter == 10)
            {
                temp = "No WiFi :(";
                break;
            }
        }
        this->m_display->setWlanIP(temp);
    })
        .detach();
}