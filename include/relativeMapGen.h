// IMPORTS
#pragma once

#include "Arduino.h"
#include <Servo.h>
#include "../include/sharp.h"

// servo motor
class RelativeMapGen
{
private:
    uint8_t servoPin = 11;
    int servoRange = 180; // 180 degree full range of servo motor

    Servo sharpMountServo;
    Sharp sharp;

    int (*relMap_arr)[11];

    /*int relMap_arr[6][11] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};*/

    // If the robot is facing in +y direction,
    // 0 degrees is to the -x direction

    const int angles[60] =
        {
            0,
            0,
            0,
            0,
            0,
            11,
            14,
            18,
            21,
            27,
            27,
            31,
            34,
            37,
            39,
            45,
            45,
            45,
            45,
            45,
            50,
            51,
            53,
            56,
            56,
            59,
            63,
            63,
            63,
            68,
            72,
            72,
            76,
            79,
            81,
            90,
            90,
            90,
            90,
            90,
            90,
            99,
            101,
            104,
            108,
            108};
    const int dist[60] =
        {
            10,
            20,
            30,
            40,
            50,
            51,
            41,
            32,
            54,
            22,
            45,
            58,
            36,
            50,
            64,
            14,
            28,
            42,
            56,
            70,
            78,
            64,
            50,
            36,
            72,
            58,
            22,
            45,
            67,
            53,
            32,
            63,
            41,
            51,
            61,
            10,
            20,
            30,
            40,
            50,
            60,
            61,
            51,
            41,
            32,
            63};
    const int mapBlock[60][2] =
        {
            {0, 1},
            {0, 2},
            {0, 3},
            {0, 4},
            {0, 5},
            {1, 5},
            {1, 4},
            {1, 3},
            {2, 5},
            {1, 2},
            {2, 4},
            {3, 5},
            {2, 3},
            {3, 4},
            {4, 5},
            {1, 1},
            {2, 2},
            {3, 3},
            {4, 4},
            {5, 5},
            {6, 5},
            {5, 4},
            {4, 3},
            {3, 2},
            {6, 4},
            {5, 3},
            {2, 1},
            {4, 2},
            {6, 3},
            {5, 2},
            {3, 1},
            {6, 2},
            {4, 1},
            {5, 1},
            {6, 1},
            {1, 0},
            {2, 0},
            {3, 0},
            {4, 0},
            {5, 0},
            {6, 0},
            {6, 1},
            {5, 1},
            {4, 1},
            {3, 1},
            {6, 2},
            {5, 2}

    };

    // Methods
    bool checkForObstacle(int index);
    bool isInRange(float sharpReading, int blockVal);

public:
    // passed map array should be a 2-D array with dimensions 6x11
    RelativeMapGen(int (*relMapIn_arr)[11]);
    bool initArray(int (*relMapIn_arr)[11]);

    // Call this method
    void updateMap();
};