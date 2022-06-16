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

void FullMapGen::updateMap_arr(int *currentPos_arr, int curDir)
{
    Sharp sharpUpdate;
    Ultrasonic leftUltrasonic(13, 12);
    Ultrasonic rightUltrasonic(3, 15);

    int currentRow = currentPos_arr[0];
    int currentCol = currentPos_arr[1];

    switch (curDir)
    {
    case NORTH:
        // sharp pointing to rows-1
        if (sharpUpdate.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow - 1][currentCol] = 2;
        }
        if (leftUltrasonic.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow][currentCol - 1] = 2;
        }
        if (rightUltrasonic.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow][currentCol + 1] = 2;
        }
    case EAST:
        // sharp pointing to cols+1
        if (sharpUpdate.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow][currentCol + 1] = 2;
        }
        if (leftUltrasonic.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow - 1][currentCol] = 2;
        }
        if (rightUltrasonic.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow + 1][currentCol] = 2;
        }
    case SOUTH:
        // sharp pointing to rows+1
        if (sharpUpdate.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow + 1][currentCol] = 2;
        }
        if (leftUltrasonic.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow][currentCol + 1] = 2;
        }
        if (rightUltrasonic.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow][currentCol - 1] = 2;
        }
    case WEST:
        // sharp pointing to cols-1
        if (sharpUpdate.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow][currentCol - 1] = 2;
        }
        if (leftUltrasonic.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow + 1][currentCol] = 2;
        }
        if (rightUltrasonic.isNextBlockObstacle())
        {
            this->fullMap_arr[currentRow - 1][currentCol] = 2;
        }
    }
}

void FullMapGen::updateNodeMap(Node *curNode, int *curDir, Node *obsNode)
{
    Sharp sharpUpdate;
    Ultrasonic leftUltrasonic(13, 12);
    Ultrasonic rightUltrasonic(3, 15);

    switch (*curDir)
    {
    case NORTH:
        // sharp pointing to rows-1
        if (sharpUpdate.isNextBlockObstacle())
        {
            curNode->front = obsNode;
        }
        if (leftUltrasonic.isNextBlockObstacle())
        {
            curNode->left = obsNode;
        }
        if (rightUltrasonic.isNextBlockObstacle())
        {
            curNode->right = obsNode;
        }
        break;
    case EAST:
        // sharp pointing to cols+1
        if (sharpUpdate.isNextBlockObstacle())
        {
            curNode->left = obsNode;
        }
        if (leftUltrasonic.isNextBlockObstacle())
        {
            curNode->front = obsNode;
        }
        if (rightUltrasonic.isNextBlockObstacle())
        {
            curNode->back = obsNode;
        }
        break;
    case SOUTH:
        // sharp pointing to rows+1
        if (sharpUpdate.isNextBlockObstacle())
        {
            curNode->back = obsNode;
        }
        if (leftUltrasonic.isNextBlockObstacle())
        {
            curNode->right = obsNode;
        }
        if (rightUltrasonic.isNextBlockObstacle())
        {
            curNode->left = obsNode;
        }
        break;
    case WEST:
        // sharp pointing to cols-1
        if (sharpUpdate.isNextBlockObstacle())
        {
            curNode->left = obsNode;
        }
        if (leftUltrasonic.isNextBlockObstacle())
        {
            curNode->back = obsNode;
        }
        if (rightUltrasonic.isNextBlockObstacle())
        {
            curNode->front = obsNode;
        }
        break;
    default:
        break;
    }
}
