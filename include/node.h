#pragma once
#include <Arduino.h>

typedef struct Node Node;

struct Node
{
  Node *front;
  Node *back;
  Node *left;
  Node *right;

  // For path retracing in DFS algorithm
  Node *parent;
  bool visited = false;

  int col;
  int row;
  int state;
};