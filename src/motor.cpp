#include "motor.hpp"

Motor::Motor(/* args */)
{
    m_counter = 0;
    m_valueToMove = 0;
    m_IsCounting = false;
    Init();
    Stop();
    Interrupt();
}

Motor::~Motor()
{
}

void Motor::Start()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

void Motor::Stop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void Motor::Interrupt()
{
    std::thread([&] {
        while (1)
        {
            if (!m_IsCounting)
            {
                continue;
            }
            m_currVal = digitalRead(INTERRUPT_PIN);
            if (m_currVal == 1 && m_prevVal == 0)
            {
                Logger::log("Couting: " + std::to_string(m_counter));
                m_counter++;
            }
            m_prevVal = m_currVal;
            if (m_counter == m_valueToMove)
            {
                Logger::log("Zatrzymuje");
                m_counter = 0;
                m_valueToMove = 0;
                m_IsCounting = false;
                Stop();
            }
        }
    })
        .detach();
}

void Motor::Init()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(INTERRUPT_PIN, INPUT);
    if (softPwmCreate(7, 0, 100))
    {
        Logger::log("Zjebalo sie w PWM :(");
    }
    softPwmWrite(7, 20);
    m_currVal = digitalRead(INTERRUPT_PIN);
}

void Motor::setMoveValue(int val)
{
    m_valueToMove = val;
    m_IsCounting = true;
    Start();
}