#pragma once
#include "config.hpp"
#include <wiringPi.h>
#include <sys/time.h>

class Distance
{

public:
    float getDistance(int angle);
    Distance();
    ~Distance();

private:
    void sendPulse();
    void moveServo(int angle);
    int pulseIn(int pin, int level);
};
