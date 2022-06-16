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
    void forward();
    void backward();
    void left();
    void right();
    void stop();
};