#pragma once
#include <Arduino.h>
#include "stdio.h"
#include "node.h"

#include "sharp.h"
#include "ultrasonic.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

class FullMapGen
{
private:
public:
    /*============Array Implementation(Fully Functioning and to be used)=======================*/
    /*currPos format = {row index, column index}*/
    int (*fullMap_arr)[11];
    void initData_array(int (*ptr)[11]);
    void printMap_arr();
    void updateMap_arr(int *currentPos_arr, int (*relMap_arr)[11]);
    void updateMap_arr(int *currentPos_arr, int curDir);
    void updateNodeMap(Node *curNode, int *curDir, Node *obsNode);
    /*============Array Implementation(Fully Functioning and to be used)=======================*/
};
