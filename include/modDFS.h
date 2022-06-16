#pragma once
#include "node.h"
#include <vector>
#include "iostream"
#include "fullMapGen.h"
#include "driver.h"

void printNodeVec(Node (*nodeArray)[11]);
/**
 * @brief Modified Depth First Search algorithm to solve a graph with unidentifed obstacles. The result of the function is a
 *
 * @param startNode The start location of the car
 * @param stackVec std::vector representation of a stack
 * @param visitedList Node** array to store visited nodes in the DFS algorithm
 * @param visitedCounter Counter to keep track of next location to add a node to the visitedList, pass 0
 * @param stackCounter Counter to keep track of stack, pass 0
 * @param pathList The std::vector<Node*> used to keep the possible path of the robot to take when cleaning the room. The robot only passes through adjacent nodes in this path
 * @param curDir Should pass a pointer to a global direction state variable
 */
void modDFS(Node *startNode, std::vector<Node *> stackVec, Node **visitedList, int visitedCounter, int stackCounter, std::vector<Node *> *pathList, int *curDir);
void printNodes(Node **nodeArray);
bool isInVisited(Node *nodeIn, Node **visited);
bool isNextChildOfCurrent(Node *nextNode, Node *curNode);
/**
 * @brief When traversing the DFS, we have to trace back early steps to get possible moves without moving through diagonals. This method also moves the robot physically to the next location.
 *
 * @param destinationNode The final destination to which the path should be retraced
 * @param curNode The source node from which the path originates
 * @param pathList The list of Nodes that has to be traversed when moving through all free nodes of the graph
 * @param curDir The current facing direction of the robot
 */
void addRetracePath(Node *destinationNode, Node *curNode, std::vector<Node *> *pathList, int *curDir);
void printPathList(std::vector<Node *> pathL);
bool isInStack(Node *node, std::vector<Node *> *stackv);
void printStack(std::vector<Node *> stackv);
/**
 * @brief Physically move the robot from one adjacent node to another. All moves are along X and Y axes. No diagonal moves are allowed
 *
 * @param fromNode the current position of the robot
 * @param toNode The next required position of the robot
 * @param car Pointer to a driver object required to move the robot
 * @param curDir Should pass a pointer to a global direction state variable
 */
void moveToNextNodePhysically(Node *fromNode, Node *toNode, Driver *car, int *curDir);