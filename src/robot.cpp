#include "robot.hpp"

Robot::Robot(/* args */)
{
    Logger::log("Creating");
    m_display = make_shared<HD44780_I2C>(DISPLAY_I2C_ADDR);
    GetWlanAddress();
    m_esp8266.SetIpCallback(std::bind(&Robot::SetEspIPcallback, this, std::placeholders::_1));
    m_motors = make_shared<Motors>();
}

Robot::~Robot()
{
    Logger::log("Destorying!");
}

void Robot::Start()
{
    Logger::log("Starting Main loop!");
    if (m_serial.Open() != 0)
    {
        Logger::log("Zjebalo sie w huj wie co !");
        return;
    }
    m_esp8266.Init(&m_serial);
    while (1)
    {
        auto data = m_serial.ReadString(m_success);
        std::string dataToRead;
        if (m_success)
        {
            m_esp8266.HandleInputData(data);
        }
        if (m_esp8266.isReady() && GetDataFromServer(data, dataToRead) && m_parser.isValidJson(dataToRead))
        {
            auto type = m_parser.getString("type");
            Logger::log("type");
        }
    }
}

void Robot::SetEspIPcallback(std::string &ip)
{
    if (m_display != nullptr)
    {
        m_display->setEspIP(ip);
    }
}

void Robot::GetWlanAddress()
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
        Logger::log("Wifi:");
        Logger::log(temp);
        if (this->m_display != nullptr)
        {
            this->m_display->setWlanIP(temp);
        }
    })
        .detach();
}