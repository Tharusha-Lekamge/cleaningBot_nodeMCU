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
int curDir = 0;

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

Servo newServo;

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
    // Serial.begin(9600);
  }

  newServo.attach(D10);
  // Create mapper objects
  // bool mapInit = relMapper.initArray(relMapIn);
  // relMapper.updateMap();

  fullMap.initData_array(fullMapTest);
  // fullMap.updateMap_arr(currPos, relMapIn);

  // Init Node array
#include "arr_to_graph.h"

  fullMap.updateNodeMap(&nodeArray[10][5], &curDir, obstacleNode);
  // Find initial path for a map with no obstacles
}

// the loop function runs over and over again forever
void loop()
{
  delay(3000);
  newServo.write(180);
  // testDriver.forward();

  /*
  01. Initialize the path in setup[For a map with no obstacles]
  02. Scan for obstacles.
  03. Update the map.
  04. Find a path.
  05. Travel along the path.
  06.
  */
  Node *startNode = &nodeArray[10][5];
  modDFS(startNode, stackVec, visitedList, 0, 0, &pathList, &curDir);
  delay(10000);
}
