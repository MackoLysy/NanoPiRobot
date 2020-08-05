#include "motors.hpp"
#include "config.hpp"
#include <wiringPi.h>
#include <iostream>

static const int angle_multiplayer = 15;
static const int disnace_multiplayer = 25;

static const int halfstep_seq[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}};

Motors::Motors()
{
    for (int i = 0; i < 4; i++)
    {
        pinMode(motor_left_pins[i], OUTPUT);
        digitalWrite(motor_left_pins[i], LOW);
        pinMode(motor_right_pins[i], OUTPUT);
        digitalWrite(motor_right_pins[i], LOW);
    }
}

void Motors::stop()
{
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(motor_right_pins[i], LOW);
        digitalWrite(motor_left_pins[i], LOW);
    }
}

void Motors::moveFoward(int distance)
{
    for (int i = 0; i < disnace_multiplayer * distance; i++)
    {
        for (int step = 0; step < 8; step++)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                digitalWrite(motor_left_pins[pin], halfstep_seq[step][pin]);
                digitalWrite(motor_right_pins[pin], halfstep_seq[step][pin]);
                delayMicroseconds(200);
            }
        }
    }
}

void Motors::moveBackward(int distance)
{
    for (int i = 0; i < disnace_multiplayer * distance; i++)
    {
        for (int step = 8; step > 0; --step)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                digitalWrite(motor_left_pins[pin], halfstep_seq[step][pin]);
                digitalWrite(motor_right_pins[pin], halfstep_seq[step][pin]);
                delayMicroseconds(200);
            }
        }
    }
    stop();
}

void Motors::rotateLeft(int angle)
{
    for (int i = 0; i < angle_multiplayer * angle; i++)
    {
        for (int step = 0; step < 8; step++)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                digitalWrite(motor_left_pins[pin], halfstep_seq[step][pin]);
                digitalWrite(motor_right_pins[pin], halfstep_seq[reverseStep(step)][pin]);
                delayMicroseconds(200);
            }
        }
    }
    stop();
}

void Motors::rotateRight(int angle)
{
    for (int i = 0; i < angle_multiplayer * angle; i++)
    {
        for (int step = 0; step < 8; step++)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                digitalWrite(motor_right_pins[pin], halfstep_seq[step][pin]);
                digitalWrite(motor_left_pins[pin], halfstep_seq[reverseStep(step)][pin]);
                delayMicroseconds(200);
            }
        }
    }
    stop();
}

int Motors::reverseStep(int step)
{
    return 7 - step;
}

Motors::~Motors()
{
    stop();
}

// 20,41