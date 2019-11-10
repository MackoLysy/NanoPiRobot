#include "robot.hpp"
#include "wiringPi.h"
#include "MEMS.hpp"
#include "motor.hpp"

int main(int argc, char const *argv[])
{
    if (wiringPiSetup() < 0)
    {
        fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
        return 1;
    }
    Motor motor;
    motor.setMoveValue(3);
    Robot robot;
    robot.Start();

    return 0;
}