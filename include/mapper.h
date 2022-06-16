#pragma once
#include <Arduino.h>

typedef struct Node Node;

struct Node
{
  Node *front;
  Node *back;
  Node *left;
  Node *right;

  int col;
  int row;
  int state;
};