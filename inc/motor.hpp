#include "config.hpp"
#include "logger.hpp"

#include <thread>
#include <wiringPi.h>
#include <softPwm.h>
class Motor
{
private:
    bool m_IsCounting;
    int m_counter;
    int m_valueToMove;
    int m_prevVal;
    int m_currVal;
    void Interrupt();
    void Init();
public:
    Motor(/* args */);
    ~Motor();
    void Stop();
    void Start();
    void setMoveValue(int val);
};

