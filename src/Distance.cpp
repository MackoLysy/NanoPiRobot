#include "Distance.hpp"

Distance::Distance(/* args */)
{
    wiringPiSetup();
    pinMode(SERVO_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);
}

Distance::~Distance()
{
}

float Distance::getDistance(int angle)
{
    moveServo(angle);
    delay(200);
}

void Distance::moveServo(int angle)
{
     int pwmVal = angle*2.1 + 110;
     pwmWrite(SERVO_PIN, pwmVal);
}