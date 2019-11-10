#include "HD44780_I2C.hpp"

HD44780_I2C::HD44780_I2C(int _address) : IDisplay(_address)
{
    
    Init();
    Draw();
}

HD44780_I2C::~HD44780_I2C()
{
}

void HD44780_I2C::Draw()
{
    lcdPosition(fd, 0, 0);
    lcdPuts(fd, getWlanIP().c_str());
    lcdPosition(fd, 0, 1);
    lcdPuts(fd, getEspIP().c_str());
}

void HD44780_I2C::Init()
{
    pcf8574Setup(0x64, getAddress());
    wiringPiSetup();
    pinMode(LCDOFS(1), OUTPUT);
    pinMode(LCDOFS(3), OUTPUT);
    digitalWrite(LCDOFS(1), 0);
    digitalWrite(LCDOFS(3), 1);
    fd = lcdInit(4, 20, 4, LCDOFS(0), LCDOFS(2),
                 LCDOFS(4), LCDOFS(5), LCDOFS(6), LCDOFS(7), 0, 0, 0, 0);
    lcdHome(fd);
    lcdClear(fd);
}
