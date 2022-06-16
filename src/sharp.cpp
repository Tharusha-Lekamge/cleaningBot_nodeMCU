#include "../include/sharp.h"

Sharp::Sharp()
{
    sharpSensorVolt = 0;
    Vr = 5.0;
    sharpSensorVal = 0;
    sum = 0;
    distance = 0;
    this->sharpPin = A0;
}

Sharp::Sharp(uint8_t sharpPin)
{
    this->sharpSensorVolt = 0;
    this->Vr = 5.0;
    this->sharpSensorVal = 0;
    this->sum = 0;
    this->distance = 0;
    this->sharpPin = sharpPin;
};

float Sharp::getDistance()
{
    this->sum = 0;
    for (int i = 0; i < 100; i++)
    {
        this->sum = this->sum + float(analogRead(sharpPin));
    }

    sharpSensorVal = sum / 100;
    sharpSensorVolt = sharpSensorVal * Vr / 1024;

    this->distance = pow(sharpSensorVolt * (1 / k1), 1 / k2);
    // distance = (sharpSensorVolt * (1 / k1)) * *(1 / k2);
    return (this->distance);
};

/* Block size is considered to be 7 inches
 * check if there is an obstacle in the range 7.5 inches from the front of the robot
 * distance is measured in cm from the sharp
 */
bool Sharp::isNextBlockObstacle()
{
    int distance = getDistance();
    if (distance < 19)
    {
        return true;
    }
    else
    {
        return false;
    }
}