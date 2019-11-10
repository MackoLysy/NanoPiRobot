#include "MEMS.hpp"
// #include "GY-91/MPU9250.h"

MEMS::MEMS(/* args */)
{
    accCoef = 0.02f;
    gyroCoef = 0.98f;
    fd = wiringPiI2CSetup(MPU6050_ADDR);
    wiringPiI2CWriteReg8(fd, MPU6050_SMPLRT_DIV, 0x00);
    wiringPiI2CWriteReg8(fd, MPU6050_CONFIG, 0x00);
    wiringPiI2CWriteReg8(fd, MPU6050_GYRO_CONFIG, 0x08);
    wiringPiI2CWriteReg8(fd, MPU6050_ACCEL_CONFIG, 0x00);
    wiringPiI2CWriteReg8(fd, MPU6050_PWR_MGMT_1, 0x01);
    update();
    angleGyroX = 0;
    angleGyroY = 0;
    angleX = this->getAccAngleX();
    angleY = this->getAccAngleY();
    preInterval = millis();
    // MPU9250();
    // initMPU9250();
    // initAK8963(m_MagDes);
    // setInitialState();
}

MEMS::~MEMS()
{
}
void MEMS::calcGyroOffsets()
{
    Logger::log("Calculating Gyro! Dont Move Sensor!");
    float x = 0, y = 0, z = 0;
    for (int i = 0; i < 3000; i++)
    {
        Logger::log(i);
        readGyroData();
        x += ((float)rawGyroX) / 65.5;
        y += ((float)rawGyroY) / 65.5;
        z += ((float)rawGyroZ) / 65.5;
    }
    gyroXoffset = x / 3000;
    gyroYoffset = y / 3000;
    gyroZoffset = z / 3000;
    Logger::log("Done!");
    Logger::log("X : " + std::to_string(gyroXoffset));
    Logger::log("Y : " + std::to_string(gyroYoffset));
    Logger::log("Z : " + std::to_string(gyroZoffset));
}

char MEMS::readByte(uint8_t address, uint8_t subAddress)
{
    return wiringPiI2CReadReg8(fd, subAddress);
}

void MEMS::readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t *dest)
{
    char data;
    for (char i = 0; i < count; i++)
    {
        data = readByte(address, subAddress + i);
        dest[i] = data;
    }
}

void MEMS::update()
{
    readAccelData();
    readGyroData();

    accX = ((float)rawAccX) / 16384.0;
    accY = ((float)rawAccY) / 16384.0;
    accZ = ((float)rawAccZ) / 16384.0;

    angleAccX = atan2(accY, sqrt(accZ * accZ + accX * accX)) * 360 / 2.0 / M_PI;
    angleAccY = atan2(accX, sqrt(accZ * accZ + accY * accY)) * 360 / -2.0 / M_PI;

    gyroX = ((float)rawGyroX) / 65.5;
    gyroY = ((float)rawGyroY) / 65.5;
    gyroZ = ((float)rawGyroZ) / 65.5;

    gyroX -= gyroXoffset;
    gyroY -= gyroYoffset;
    gyroZ -= gyroZoffset;

    interval = (millis() - preInterval) * 0.001;

    angleGyroX += gyroX * interval;
    angleGyroY += gyroY * interval;
    angleGyroZ += gyroZ * interval;

    angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
    angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
    angleZ = angleGyroZ;

    preInterval = millis();
    std::cout << "X: " << angleX << std::endl;
    std::cout << "Y: " << angleY << std::endl;
    std::cout << "Z: " << angleZ << std::endl;
}

void MEMS::readAccelData()
{
    rawAccX = readRawData(ACCEL_XOUT_H); // Turn the MSB and LSB into a signed 16-bit value
    rawAccY = readRawData(ACCEL_YOUT_H);
    rawAccZ = readRawData(ACCEL_ZOUT_H);
    // uint8_t rawData[6];                                           // x/y/z accel register data stored here
    // readBytes(MPU6050_ADDR, ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
    // rawAccX = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
    // rawAccY = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
    // rawAccZ = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
}
int16_t MEMS::readRawData(int addr)
{
    int high = wiringPiI2CReadReg8(fd, addr);
    int low = wiringPiI2CReadReg8(fd, addr + 1);
    int value = ((high << 8) | low);
    if (value > 32768)
    {
        value = value - 65536;
    }
    return value;
}

void MEMS::readGyroData()
{
    rawGyroX = readRawData(GYRO_XOUT_H); // Turn the MSB and LSB into a signed 16-bit value
    rawGyroY = readRawData(GYRO_YOUT_H);
    rawGyroZ = readRawData(GYRO_ZOUT_H);
    // uint8_t rawData[6];                                            // x/y/z gyro register data stored here
    // readBytes(MPU6050_ADDR, GYRO_XOUT_H, 6, &rawData[0]);          // Read the six raw data registers sequentially into data array
    // rawGyroX = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
    // rawGyroY = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
    // rawGyroZ = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
}

// void MEMS::CalibrateMag()
// {
//     Logger::log("Calibrating Mag...");
//     for (int i = 0; i < 100; i++)
//     {
//         readMagData(m_rawMagPos);
//         printf("MAG:  \tX: %8.3f  \tY: %8.3f  \tZ: %8.3f\r\n", m_rawMagPos[0] * getMres(), m_rawMagPos[1] * getMres(), m_rawMagPos[2] * getMres());
//         getMaxAtIndex(0);
//         getMaxAtIndex(1);
//         getMaxAtIndex(2);
//         getMinAtIndex(0);
//         getMinAtIndex(1);
//         getMinAtIndex(2);
//         delay(100);
//     }

//     calcualteDeltaAtIndex(0);
//     calcualteDeltaAtIndex(1);
//     calcualteDeltaAtIndex(2);

//     m_avgDelta = (m_magAvg[0] + m_magAvg[1] + m_magAvg[2]) / 3;

//     calculateScaleAtIndex(0);
//     calculateScaleAtIndex(1);
//     calculateScaleAtIndex(2);
//     Logger::log("Calibrating Done!");
// }

// void MEMS::setInitialState()
// {
//     readMagData(m_rawMagPos);
//     m_magMax[0] = m_rawMagPos[0] * getMres();
//     m_magMax[1] = m_rawMagPos[1] * getMres();
//     m_magMax[2] = m_rawMagPos[2] * getMres();
//     m_magMin[0] = m_rawMagPos[0] * getMres();
//     m_magMin[1] = m_rawMagPos[1] * getMres();
//     m_magMin[2] = m_rawMagPos[2] * getMres();
//     delay(100);
// }

// void MEMS::getMaxAtIndex(int i)
// {
//     m_magMax[i] = std::max(m_rawMagPos[i] * getMres(), m_magMax[i]);
// }

// void MEMS::getMinAtIndex(int i)
// {
//     m_magMin[i] = std::min(m_rawMagPos[i] * getMres(), m_magMax[i]);
// }

// void MEMS::calcualteDeltaAtIndex(int i)
// {
//     m_magAvg[i] = (m_magMax[i] - m_magMin[i]) / 2.0;
// }

// void MEMS::calculateScaleAtIndex(int i)
// {
//     m_magScale[i] = m_avgDelta / m_magAvg[i];
// }

// void MEMS::ReadData()
// {
//     readMagData(m_rawMagPos);
//     float x = (m_rawMagPos[0] * getMres() - m_magAvg[0]) * m_magScale[0];
//     float y = (m_rawMagPos[1] * getMres() - m_magAvg[1]) * m_magScale[1];
//     float z = (m_rawMagPos[2] * getMres() - m_magAvg[2]) * m_magScale[2];
//     std::cout << "Raw X: " << m_rawMagPos[0] * getMres() << " Y: " << m_rawMagPos[1] * getMres() << " Z: " << m_rawMagPos[2] * getMres() << std::endl;
//     // std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
//     // std::cout << "AVGx : " << m_magAvg[0] << " AVGy: " << m_magAvg[1] << " AVGz: " << m_magAvg[2] << std::endl;
//     // std::cout << "SCx : " << m_magScale[0] << " SCy: " << m_magScale[1] << " SCz: " << m_magScale[2] << std::endl;
// }
