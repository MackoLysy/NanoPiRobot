#pragma once
#include "IDisplay.hpp"
#include <pcf8574.h>
#include <lcd.h>

#define LCDOFS(x) (lcdofs + x)


class HD44780_I2C: public IDisplay
{
private:

    void Draw() override;
    void Init() override;
    const int lcdofs = 0x64;
public:
    HD44780_I2C(int _address);
    ~HD44780_I2C();
};

