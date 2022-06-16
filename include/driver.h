#pragma once
#include <Arduino.h>

#define LM1 2
#define LM2 3
#define RM1 4
#define RM2 5
#define LmEN 9;
#define RmEN 10;
/*===========*/

// MOVEMENT PARAMS
#define FWD 0
#define LFT 1
#define RGT 2
#define BCK 3

class Driver
{
private:
public:
    void followPath(int *path);
    /**
     * @brief Moves forward by one block. Approximately 7 inches
     */
    void forward();
    /**
     * @brief Rotates the robot by 180 degrees. No displacement of the robot
     */
    void backward();
    /**
     * @brief Rotates the robot by 90 degrees anticlockwise. No displacement of the robot
     */
    void left();
    /**
     * @brief Rotates the robot by 90 degrees clockwise. No displacement of the robot
     */
    void right();
    /**
     * @brief Stop all motors of the robot
     */
    void stop();
};