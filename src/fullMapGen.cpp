#include "../include/fullMapGen.h"
#include "stdio.h"

void FullMapGen::initData_array(int (*fullMapIn_arr)[11])
{
    this->fullMap_arr = fullMapIn_arr;
}

void FullMapGen::updateMap_arr(int *currentPos_arr, int (*relMap_arr)[11])
{
    int relMapsize = (sizeof(relMap_arr[0]) / sizeof(relMap_arr[0][0]) / 2);

    int startX = currentPos_arr[0] - relMapsize;
    int startY = currentPos_arr[1] - relMapsize;

    for (int i = 0; i < (int)(sizeof(relMap_arr[0]) / sizeof(relMap_arr[0][0])); i++)
    {
        for (int j = 0; j < (int)(sizeof(relMap_arr[0]) / sizeof(relMap_arr[0][0])); j++)
        {
            if (startX + i >= 0 && startY + j >= 0 && startX + i < (int)sizeof(fullMap_arr[0]) / 4 && startY + j < (int)sizeof(fullMap_arr[0]) / 4)
            {
                this->fullMap_arr[startX + i][startY + j] += relMap_arr[i][j];
            }
        }
    }
}
