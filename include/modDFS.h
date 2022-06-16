#pragma once
#include "node.h"
#include <vector>
#include "iostream"

void printNodeVec(Node (*nodeArray)[11]);
void modDFS(Node *startNode, std::vector<Node *> stackVec, Node **visitedList, int visitedCounter, int stackCounter, std::vector<Node *> *pathList);
void printNodes(Node **nodeArray);
bool isInVisited(Node *nodeIn, Node **visited);
bool isNextChildOfCurrent(Node *nextNode, Node *curNode);
void addRetracePath(Node *destinationNode, Node *curNode, std::vector<Node *> *pathList);
void printPathList(std::vector<Node *> pathL);
bool isInStack(Node *node, std::vector<Node *> *stackv);
void printStack(std::vector<Node *> stackv);