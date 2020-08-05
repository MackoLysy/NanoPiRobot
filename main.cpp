#include "robot.hpp"
#include "wiringPi.h"

int main(int argc, char const *argv[])
{
    if (wiringPiSetup() < 0)
    {
        fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
        return 1;
    }
    Robot robot;
    robot.Start();
    return 0;
}