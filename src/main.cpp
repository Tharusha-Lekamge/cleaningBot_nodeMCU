// Arduino Libraries
#include <Servo.h>
#include <Arduino.h>
#include <vector>

// Required Files
#include "fullMapGen.h"
#include "relativeMapGen.h"
#include "node.h"
#include "driver.h"
#include "modDFS.h"

// DEFINITIONS

// 1.2 Motor Params
#define speed 5
const int TIME_PER_REV = 100;

// 2.1 IR pins - A0

// 3.1 Map Inits
#include "mapArrays.h"

// 4.1 State variables for current location
int currPos[2] = {5, 5};
// Directions - 0 - front, 1 - right, 2 - back, 3 - left
// clockwise rotation. Directions are absolute
int curDir = 2;

Node nodeArray[11][11];

// Path finding variables
Node *outOfBoundsNode = new Node;
Node *obstacleNode = new Node;

// Maximum number of nodes is 121
Node **stack = new Node *[128];
std::vector<Node *> stackVec;
Node **visitedList = new Node *[128];
std::vector<Node *> pathList;
/*  Set the following variable to true when the robot
 *  completed cleaning the room */
// bool isComplete;

// Sharp and Servo objects - Not used
// Servo sharpMountServoInit;

// Mapper objects
FullMapGen fullMap;
// RelativeMapGen relMapper(relMapIn);
Driver testDriver;

// Servo newServo;

void setup()
{
  // SETTING PINS
  // Motor pins
  {
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    // EN2
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D10, OUTPUT);

    // put your setup code here, to run once:
    analogWrite(D4, 36);
    analogWrite(D5, 47);
  }

  // Initiate Serial for testing
  {
    Serial.begin(9600);
    Serial.println("");
  }

  Serial.println("inside Setup");
  // newServo.attach(D10);
  //  Create mapper objects
  //  bool mapInit = relMapper.initArray(relMapIn);
  //  relMapper.updateMap();

  fullMap.initData_array(fullMapTest);
  // fullMap.updateMap_arr(currPos, relMapIn);

  Serial.println("creating Node array");
  outOfBoundsNode->row = -2;
  outOfBoundsNode->col = -2;

  obstacleNode->row = -3;
  obstacleNode->col = -3;
  // Init Node array

  std::cout << "main inside\n";
  for (int rows = 0; rows < 11; rows++)
  {
    for (int cols = 0; cols < 11; cols++)
    {
      nodeArray[rows][cols].col = cols;
      nodeArray[rows][cols].row = rows;
      nodeArray[rows][cols].state = fullMapTest[rows][cols];
    }
  }

  // Add pointers
  for (int rows = 0; rows < 11; rows++)
  {
    for (int cols = 0; cols < 11; cols++)
    {
      // Get the address of the current node
      // Node *curNode = &nodeArray[rows][cols];
      Node *fr; // Front pointer
      Node *bk; // back pointer
      Node *r;  // Right pointer
      Node *l;  // Left pointer

      if (rows == 0) // If robot is at top
      {
        fr = outOfBoundsNode; // No node to front

        // Check if the back node is obstacle
        Node *backNode = &nodeArray[rows + 1][cols];
        if (backNode->state == 2) // If the backNode is an obstacle
        {
          bk = obstacleNode;
        }
        else
        {
          bk = backNode;
        }

        // Test for left and right availability
        if (cols == 0) //  If robot is at leftmost
        {
          Node *rightNode = &nodeArray[rows][cols + 1];
          if (rightNode->state == 2) // If rightNode is an obstacle
          {
            r = obstacleNode;
          }
          else
          {
            r = rightNode;
          }

          l = outOfBoundsNode; // No node to left
        }
        else if (cols == 10) // If robot is at rightmost
        {
          r = outOfBoundsNode; // No node to right

          Node *leftNode = &nodeArray[rows][cols - 1];
          if (leftNode->state == 2) // If leftNode is an obstacle
          {
            l = obstacleNode;
          }
          else
          {
            l = leftNode;
          }
        }
        else
        {
          Node *rightNode = &nodeArray[rows][cols + 1];
          if (rightNode->state == 2) // If rightNode is an obstacle
          {
            r = obstacleNode;
          }
          else
          {
            r = rightNode;
          }

          Node *leftNode = &nodeArray[rows][cols - 1];
          if (leftNode->state == 2) // If leftNode is an obstacle
          {
            l = obstacleNode;
          }
          else
          {
            l = leftNode;
          }
        }
      }
      else if (rows == 10) // No node to back
      {
        Node *frontNode = &nodeArray[rows - 1][cols];
        if (frontNode->state == 2) // If the backNode is an obstacle
        {
          fr = obstacleNode;
        }
        else
        {
          fr = frontNode;
        }

        bk = outOfBoundsNode; // No node to the back

        // Test for left and right availability
        if (cols == 0) //  If robot is at leftmost
        {
          Node *rightNode = &nodeArray[rows][cols + 1];
          if (rightNode->state == 2) // If rightNode is an obstacle
          {
            r = obstacleNode;
          }
          else
          {
            r = rightNode;
          }

          l = outOfBoundsNode; // No node to left
        }
        else if (cols == 10) // If robot is at rightmost
        {
          r = outOfBoundsNode; // No node to right

          Node *leftNode = &nodeArray[rows][cols - 1];
          if (leftNode->state == 2) // If leftNode is an obstacle
          {
            l = obstacleNode;
          }
          else
          {
            l = leftNode;
          }
        }
        else
        {
          Node *rightNode = &nodeArray[rows][cols + 1];
          if (rightNode->state == 2) // If rightNode is an obstacle
          {
            r = obstacleNode;
          }
          else
          {
            r = rightNode;
          }

          Node *leftNode = &nodeArray[rows][cols - 1];
          if (leftNode->state == 2) // If leftNode is an obstacle
          {
            l = obstacleNode;
          }
          else
          {
            l = leftNode;
          }
        }
      }
      else // Robot is in middle row
      {
        Node *frontNode = &nodeArray[rows - 1][cols];
        if (frontNode->state == 2) // If the backNode is an obstacle
        {
          fr = obstacleNode;
        }
        else
        {
          fr = frontNode;
        }

        Node *backNode = &nodeArray[rows + 1][cols];
        if (backNode->state == 2) // If the backNode is an obstacle
        {
          bk = obstacleNode;
        }
        else
        {
          bk = backNode;
        }

        // Test for left and right availability
        if (cols == 0) //  If robot is at leftmost
        {
          Node *rightNode = &nodeArray[rows][cols + 1];
          if (rightNode->state == 2) // If rightNode is an obstacle
          {
            r = obstacleNode;
          }
          else
          {
            r = rightNode;
          }

          l = outOfBoundsNode; // No node to left
        }
        else if (cols == 10) // If robot is at rightmost
        {
          r = outOfBoundsNode; // No node to right

          Node *leftNode = &nodeArray[rows][cols - 1];
          if (leftNode->state == 2) // If leftNode is an obstacle
          {
            l = obstacleNode;
          }
          else
          {
            l = leftNode;
          }
        }
        else
        {
          Node *rightNode = &nodeArray[rows][cols + 1];
          if (rightNode->state == 2) // If rightNode is an obstacle
          {
            r = obstacleNode;
          }
          else
          {
            r = rightNode;
          }

          Node *leftNode = &nodeArray[rows][cols - 1];
          if (leftNode->state == 2) // If leftNode is an obstacle
          {
            l = obstacleNode;
          }
          else
          {
            l = leftNode;
          }
        }
      }
      nodeArray[rows][cols].front = fr;
      nodeArray[rows][cols].back = bk;
      nodeArray[rows][cols].right = r;
      nodeArray[rows][cols].left = l;
    }
  }

  // (row, col) |
  // printNodeVec(nodeArray);

  for (int i = 0; i < 11; i++)
  {
    for (int j = 0; j < 11; j++)
    {
      Serial.print("(");
      Serial.print(nodeArray[i][j].row);
      Serial.print(",");
      Serial.print(nodeArray[i][j].col);
      Serial.print(",");
      Serial.print(nodeArray[i][j].state);
      Serial.print(")");
      Serial.print(" | ");
    }
    Serial.println("");
  }
  Serial.println("Update Node Array");

  // fullMap.updateNodeMap(&nodeArray[10][5], &curDir, obstacleNode);
  Serial.println("running modDFS");
  // ESP.wdtDisable();

  // ESP.wdtEnable(1000);
  Serial.println("End setup");
  // Find initial path for a map with no obstacles
  ESP.wdtEnable(1000);
}

// the loop function runs over and over again forever
void loop()
{
  Node *startNode = &nodeArray[0][0];
  Serial.println("inside Loop");

  Serial.println("running modDFS");
  modDFS(startNode, stackVec, visitedList, 0, 0, &pathList, &curDir);
  Serial.println("end ModDFS");
  for (int i = 0; i < 11; i++)
  {
    for (int j = 0; j < 11; j++)
    {
      Serial.print("(");
      Serial.print(nodeArray[i][j].row);
      Serial.print(",");
      Serial.print(nodeArray[i][j].col);
      Serial.print(",");
      Serial.print(nodeArray[i][j].state);
      Serial.print(")");
      Serial.print(" | ");
    }
    Serial.println("");
  }
  // ESP.wdtDisable();
  // for (int i = 0; i < pathList.size(); i++)
  // {
  //   Serial.print("(");
  //   Serial.print(pathList[i]->row);
  //   Serial.print(",");
  //   Serial.print(pathList[i]->col);
  //   Serial.print(")");
  //   Serial.println("");
  // }
  // delay(1000000);
}
