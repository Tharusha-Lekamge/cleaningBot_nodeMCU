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

// void FullMapGen::updateMap_arr(int *currentPos_arr, int curDir)
// {
//     Sharp sharpUpdate;
//     Ultrasonic leftUltrasonic(13, 12);
//     Ultrasonic rightUltrasonic(3, 15);

//     int currentRow = currentPos_arr[0];
//     int currentCol = currentPos_arr[1];

//     switch (curDir)
//     {
//     case NORTH:
//         // sharp pointing to rows-1
//         if (sharpRead)
//         {
//             this->fullMap_arr[currentRow - 1][currentCol] = 2;
//         }
//         if (leftRead)
//         {
//             this->fullMap_arr[currentRow][currentCol - 1] = 2;
//         }
//         if (rightRead)
//         {
//             this->fullMap_arr[currentRow][currentCol + 1] = 2;
//         }
//     case EAST:
//         // sharp pointing to cols+1
//         if (sharpRead)
//         {
//             this->fullMap_arr[currentRow][currentCol + 1] = 2;
//         }
//         if (leftRead)
//         {
//             this->fullMap_arr[currentRow - 1][currentCol] = 2;
//         }
//         if (rightRead)
//         {
//             this->fullMap_arr[currentRow + 1][currentCol] = 2;
//         }
//     case SOUTH:
//         // sharp pointing to rows+1
//         if (sharpRead)
//         {
//             this->fullMap_arr[currentRow + 1][currentCol] = 2;
//         }
//         if (leftRead)
//         {
//             this->fullMap_arr[currentRow][currentCol + 1] = 2;
//         }
//         if (rightRead)
//         {
//             this->fullMap_arr[currentRow][currentCol - 1] = 2;
//         }
//     case WEST:
//         // sharp pointing to cols-1
//         if (sharpRead)
//         {
//             this->fullMap_arr[currentRow][currentCol - 1] = 2;
//         }
//         if (leftRead)
//         {
//             this->fullMap_arr[currentRow + 1][currentCol] = 2;
//         }
//         if (rightRead)
//         {
//             this->fullMap_arr[currentRow - 1][currentCol] = 2;
//         }
//     }
// }

void FullMapGen::updateNodeMap(Node *curNode, int *curDir, Node *obsNode)
{
    ESP.wdtFeed();
    Serial.println("inside scanner");
    Sharp sharpUpdate;
    Ultrasonic leftUltrasonic(13, 12);
    Ultrasonic rightUltrasonic(3, 15);

    bool sharpRead = sharpUpdate.isNextBlockObstacle();
    bool leftRead = leftUltrasonic.isNextBlockObstacle();
    bool rightRead = rightUltrasonic.isNextBlockObstacle();

    switch (*curDir)
    {
    case NORTH:
        Serial.println("case north");
        // sharp pointing to rows-1
        if (sharpRead)
        {
            curNode->front->state = 2;
            curNode->front->col = -3;
            curNode->front->row = -3;
        }
        if (leftRead)
        {
            curNode->left->state = 2;
            curNode->left->col = -3;
            curNode->left->row = -3;
        }
        if (rightRead)
        {
            curNode->right->state = 2;
            curNode->right->col = -3;
            curNode->right->row = -3;
        }
        break;
    case EAST:
        Serial.println("case east");
        // sharp pointing to cols+1
        if (sharpRead)
        {
            curNode->left->state = 2;
            curNode->left->col = -3;
            curNode->left->row = -3;
        }
        if (leftRead)
        {
            curNode->front->state = 2;
            curNode->front->col = -3;
            curNode->front->row = -3;
        }
        if (rightRead)
        {
            curNode->back->state = 2;
            curNode->back->col = -3;
            curNode->back->row = -3;
        }
        break;
    case SOUTH:
        Serial.println("case south");
        // sharp pointing to rows+1
        if (sharpRead)
        {
            Serial.println("front obs");
            curNode->back->state = 2;
            curNode->back->col = -3;
            curNode->back->row = -3;
        }
        if (leftRead)
        {
            Serial.println("left obs");
            curNode->right->state = 2;
            curNode->right->col = -3;
            curNode->right->row = -3;
        }
        if (rightRead)
        {
            Serial.println("right obs");
            curNode->left->state = 2;
            curNode->left->col = -3;
            curNode->left->row = -3;
        }
        break;
    case WEST:
        Serial.println("case west");
        // sharp pointing to cols-1
        if (sharpRead)
        {
            curNode->left->state = 2;
            curNode->left->col = -3;
            curNode->left->row = -3;
        }
        if (leftRead)
        {
            curNode->back->state = 2;
            curNode->back->col = -3;
            curNode->back->row = -3;
        }
        if (rightRead)
        {
            curNode->front->state = 2;
            curNode->front->col = -3;
            curNode->front->row = -3;
        }
        break;
    default:
        Serial.println("case fucked");
        break;
    }
}
