#pragma once
#include "Arduino.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// SYSTEM VARIABLES

class Sharp
{
private:
    float sharpSensorVolt;
    float Vr;

    float sharpSensorVal; // Vaue of the sensor in pin
    float sum;            // To store sum of sharpSensorVal to get an average reading within a time
    float distance;       // Measured distance from the sharpSensor

    // constants taken after interpolation to get voltage -> distance conversion
    float k1 = 16.7647563;
    float k2 = -0.85803107;
    int sharpPin = A0;

public:
    Sharp();
    Sharp(uint8_t sharpPin);
    /**
     * @brief Get the Distance from the sensor to the nearest obstacle in the facing direction. Units of measurement is cm
     *
     * @return floating point value in cm.
     */
    float getDistance();
    /**
     * @brief check if the block in the facing direction of the ultrasonic sensor is an obstacle
     *
     * @return true - Is an obstacle
     * @return false - Obstacle not detected
     */
    bool isNextBlockObstacle();
};