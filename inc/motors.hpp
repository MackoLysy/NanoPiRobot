#pragma once

class Motors
{

public:
    Motors();
    ~Motors();
    void moveFoward(int distance);
    void moveBackward(int distance);
    void rotateLeft(int angle);
    void rotateRight(int angle);
    void stop();

private:
    int reverseStep(int step);
};
