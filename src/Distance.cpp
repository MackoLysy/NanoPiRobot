#include "Distance.hpp"

Distance::Distance(/* args */)
{
    wiringPiSetup();
    pinMode(SERVO_PIN, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

Distance::~Distance()
{
}

void Distance::sendPulse()
{
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
}

int Distance::pulseIn(int pin, int level)
{
    struct timeval tn, t0, t1;
    long micros;
    gettimeofday(&t0, NULL);
    micros = 0;

    while (digitalRead(pin) != level)
    {
        gettimeofday(&tn, NULL);

        if (tn.tv_sec > t0.tv_sec)
            micros = 1000000L;
        else
            micros = 0;

        micros += (tn.tv_usec - t0.tv_usec);

        if (micros > 10000)
            return 0;
    }

    gettimeofday(&t1, NULL);

    while (digitalRead(pin) == level)
    {
        gettimeofday(&tn, NULL);

        if (tn.tv_sec > t0.tv_sec)
            micros = 1000000L;
        else
            micros = 0;

        micros = micros + (tn.tv_usec - t0.tv_usec);

        if (micros > 10000)
            return 0;
    }

    if (tn.tv_sec > t1.tv_sec)
        micros = 1000000L;
    else
        micros = 0;
    micros = micros + (tn.tv_usec - t1.tv_usec);

    return micros;
}

float Distance::getDistance(int angle)
{
    moveServo(angle);
    delay(100);
    return 10.0;
    // sendPulse();
    // int time = pulseIn(ECHO, HIGH);
    // return time / 58.0;
}

void Distance::moveServo(int angle)
{
    int pwmVal = angle * 2.1 + 110;
    pwmWrite(SERVO_PIN, pwmVal);
}