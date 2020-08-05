#include "motor.hpp"
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

Motor::Motor(const int *pins) : m_pins(pins)
{
    for (int i = 0; i < 4; i++)
    {
        pinMode(m_pins[i], OUTPUT);
        digitalWrite(m_pins[i], LOW);
    }
}

void Motor::stop()
{
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(m_pins[i], LOW);
    }
}

void Motor::moveFoward(int distance)
{
    for (int i = 0; i < disnace_multiplayer * distance; i++)
    {
        for (int step = 0; step < 8; step++)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                digitalWrite(m_pins[pin], halfstep_seq[step][pin]);
                delayMicroseconds(500);
            }
        }
    }
}

void Motor::moveBackward(int distance)
{
    for (int i = 0; i < disnace_multiplayer * distance; i++)
    {
        for (int step = 8; step > 0; --step)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                digitalWrite(m_pins[pin], halfstep_seq[step][pin]);
                delayMicroseconds(500);
            }
        }
    }
    stop();
}

void Motor::rotateForward(int angle)
{
    for (int i = 0; i < angle_multiplayer * angle; i++)
    {
        for (int step = 0; step < 8; step++)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                digitalWrite(m_pins[pin], halfstep_seq[step][pin]);
                delayMicroseconds(500);
            }
        }
    }
    stop();
}

void Motor::rotateBackward(int angle)
{
    for (int i = 0; i < angle_multiplayer * angle; i++)
    {
        for (int step = 8; step > 0; --step)
        {
            for (int pin = 0; pin < 4; pin++)
            {
                digitalWrite(m_pins[pin], halfstep_seq[step][pin]);
                delayMicroseconds(500);
            }
        }
    }
    stop();
}

Motor::~Motor()
{
    stop();
}

// 20,41