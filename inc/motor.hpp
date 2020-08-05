#pragma once

class Motor
{

public:
    Motor(const int *pins);
    ~Motor();
    void moveFoward(int distance);
    void moveBackward(int distance);
    void rotateForward(int angle);
    void rotateBackward(int angle);
    void stop();
private:
    int m_type;
    const int *m_pins;
};
