#pragma once
#include "config.hpp"
#include <wiringPi.h>

class Distance
{
private:
    void moveServo(int angle);

public:
    float getDistance(int angle);
    Distance();
    ~Distance();
};
