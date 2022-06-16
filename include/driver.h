#pragma once
#include "Arduino.h"
#include "mapper.h"

// MOVEMENT PARAMS
#define FWD 0
#define LFT 1
#define RGT 2
#define BCK 3

void visitAdjacentNode(Node *fromNode, Node *toNode);

class Driver
{
public:
    int time_fwd = 1000;
    int time_turn = 500;
    int LM_1;
    int LM_2;
    int RM_1;
    int RM_2;
    int LM_EN;
    int RM_EN;
    int speed;

public:
    Driver(int motor1_1, int motor1_2, int motor2_1, int motor2_2, int motor1_EN, int motor2_EN, int speed);
    void forward();
    void backward();
    void left();
    void right();
    void stop();
    void follow_path(int *path);
};
