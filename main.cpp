#include "robot.hpp"
#include "wiringPi.h"
#include "MEMS.hpp"

static volatile int a = 0;
void Stop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
void Start()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    // digitalWrite(IN3, LOW);
    // digitalWrite(IN4, HIGH);

}
int main(int argc, char const *argv[])
{
    if (wiringPiSetup() < 0)
    {
        fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
        return 1;
    }
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(10, INPUT);
    Stop();
    Start();
    auto watek = std::thread([&] {
        int value = 0;
        int counter = 0;
        while (1)
        {
            auto readed = digitalRead(10);
            if (readed == 0 && value == 1)
            {
                Logger::log("Zmienilo sie");
                Logger::log(value);
                Logger::log(counter);
                counter++;
            }
            value = readed;
            if(counter == 100)
            {
                Logger::log("Zatrzymuje!");
                Stop();
            }
        }
    });
    watek.detach();
    Robot robot;
    robot.Start();

    return 0;
}