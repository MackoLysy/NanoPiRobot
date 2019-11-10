#pragma once
#include <stdint.h>
#include <algorithm>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include "logger.hpp"
#include <math.h>

#define MPU6050_ADDR 0x68
#define MPU6050_SMPLRT_DIV 0x19
#define MPU6050_CONFIG 0x1a
#define MPU6050_GYRO_CONFIG 0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_WHO_AM_I 0x75
#define MPU6050_PWR_MGMT_1 0x6b
#define MPU6050_TEMP_H 0x41
#define MPU6050_TEMP_L 0x42
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47

class MEMS
{
private:
    int fd;
    int rawAccX;
    int rawAccY;
    int rawAccZ;

    int rawGyroX;
    int rawGyroY;
    int rawGyroZ;

    float gyroXoffset, gyroYoffset, gyroZoffset;

    float accX;
    float accY;
    float accZ;

    float gyroX;
    float gyroY;
    float gyroZ;

    float angleGyroX;
    float angleGyroY;
    float angleGyroZ;

    float angleAccX;
    float angleAccY;

    float angleX, angleY, angleZ;

    float interval;
    long preInterval;

    float accCoef, gyroCoef;

    // int16_t m_rawAccPos[3];
    // int16_t m_rawGyrPos[3];
    // int16_t m_rawMagPos[3];

    // float m_MagDes[3];
    // float m_magMax[3];
    // float m_magMin[3];
    // float m_magAvg[3];
    // float m_magScale[3];
    // float m_avgDelta;
    // void getMaxAtIndex(int i);
    // void getMinAtIndex(int i);
    // void calcualteDeltaAtIndex(int i);
    // void calculateScaleAtIndex(int i);
    // void setInitialState();
    void readAccelData();
    void readGyroData();
    char readByte(uint8_t address, uint8_t subAddress);
    void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t *dest);
    int16_t readRawData(int addr);

public:
    void calcGyroOffsets();
    float getAccAngleX() { return angleAccX; };
    float getAccAngleY() { return angleAccY; };
    void update();
    MEMS(/* args */);
    ~MEMS();
};
