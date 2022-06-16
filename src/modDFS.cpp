#include "modDFS.h"

FullMapGen *newMapperObject = new FullMapGen;
Driver *dfsDriver = new Driver;
Node *obstacleNode1 = new Node;

void printNodeVec(Node (*nodeArray)[11])
{
  for (int i = 0; i < 11; i++)
  {
    for (int j = 0; j < 11; j++)
    {
      std::cout << "(" << nodeArray[i][j].row << "," << nodeArray[i][j].col << ")"
                << " - " << nodeArray[i][j].state << " | ";
      if (j < 10)
      {
        // std::cout<<"("<<nodeArray[i][j].right->row<<","<<nodeArray[i][j].right->col<<")"<<" | ";
      }
    }
    std::cout << "\n";
  }
}

void printNodes(Node **nodeArray)
{
  for (int i = 0; i < 128; i++)
  {
    std::cout << "(" << nodeArray[i]->row << "," << nodeArray[i]->col << ") | \n";
  }
}

bool isInVisited(Node *nodeIn, Node **visited)
{
  for (int i = 0; i < 128; i++)
  {
    if (visited[i] == nodeIn)
    {
      return true;
    }
  }
  return false;
}

bool isNextChildOfCurrent(Node *nextNode, Node *curNode)
{
  // Check if the nextNode is directly connected to current Node
  if (curNode->front == nextNode ||
      curNode->back == nextNode ||
      curNode->left == nextNode ||
      curNode->right == nextNode)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void addRetracePath(Node *destinationNode, Node *curNode, std::vector<Node *> *pathList, int *curDir)
{
  if (isNextChildOfCurrent(destinationNode, curNode))
  {
    moveToNextNodePhysically(curNode, destinationNode, dfsDriver, curDir);
    return;
  }
  else
  {
    pathList->push_back(curNode->parent);
    moveToNextNodePhysically(curNode, curNode->parent, dfsDriver, curDir);
    addRetracePath(destinationNode, curNode->parent, pathList, curDir);
  }
}

void printPathList(std::vector<Node *> pathL)
{
  for (int i = 0; i < (int)pathL.size(); i++)
  {
    std::cout << "(" << pathL[i]->row << ", " << pathL[i]->col << ")\n";
  }
}

bool isInStack(Node *node, std::vector<Node *> *stackv)
{
  bool wereThereAny = false;
  auto iterator = stackv->begin();
  while (iterator != stackv->end())
  {
    if (*iterator == node)
    {
      iterator = stackv->erase(iterator);
      // std::cout<<"deleted from stack-----------------\n";
    }
    else
    {
      iterator++;
    }
  }
  return wereThereAny;
}

void printStack(std::vector<Node *> stackv)
{
  for (int i = 0; i < (int)stackv.size(); i++)
  {
    std::cout << "(" << stackv[i]->row << "," << stackv[i]->col << "," << stackv[i]->visited << ") ";
  }
  std::cout << "\n";
}

void modDFS(Node *startNode, std::vector<Node *> stackVec, Node **visitedList, int visitedCounter, int stackCounter, std::vector<Node *> *pathList, int *curDir)
{
  //  startNode is the name of the current node
  //  Add startNode to visited and increment counter

  // Init pathList
  startNode->visited = true;
  pathList->push_back(startNode);

  visitedList[visitedCounter] = startNode;
  visitedCounter++;

  // Scanning for Obstacles
  newMapperObject->updateNodeMap(startNode, curDir, obstacleNode1);

  // Recording the current location of the node
  Node *nextNode;

  // Check all for directional pointers

  // RIGHT NODE
  nextNode = startNode->right;
  // Check if the pointer actually points to the node on right
  // Not to an obstacle of ourOfBounds
  if (nextNode->col != startNode->col + 1)
  {
  }
  else if (isInVisited(nextNode, visitedList))
  {
  }
  else
  {
    if (nextNode->visited)
    {
      isInStack(nextNode, &stackVec);
    }
    nextNode->visited = true;

    stackVec.push_back(nextNode);
    nextNode->parent = startNode;
    stackCounter++;
  }

  // FRONT NODE
  nextNode = startNode->front;
  if (nextNode->row != startNode->row - 1)
  {
  }
  else if (isInVisited(nextNode, visitedList))
  {
  }
  else
  {
    if (nextNode->visited)
    {
      isInStack(nextNode, &stackVec);
    }
    nextNode->visited = true;

    stackVec.push_back(nextNode);
    nextNode->parent = startNode;
    stackCounter++;
  }

  // BACK NODE
  nextNode = startNode->back;
  if (nextNode->row != startNode->row + 1)
  {
  }
  else if (isInVisited(nextNode, visitedList))
  {
  }
  else
  {
    if (nextNode->visited)
    {
      isInStack(nextNode, &stackVec);
    }
    nextNode->visited = true;

    stackVec.push_back(nextNode);
    nextNode->parent = startNode;
    stackCounter++;
  }

  // LEFT NODE
  nextNode = startNode->left;
  if (nextNode->col != startNode->col - 1)
  {
  }
  else if (isInVisited(nextNode, visitedList))
  {
  }
  else
  {
    if (nextNode->visited)
    {
      isInStack(nextNode, &stackVec);
    }
    nextNode->visited = true;

    stackVec.push_back(nextNode);
    nextNode->parent = startNode;
    stackCounter++;
  }

  // After adding all childern
  // If all Nodes are traversed
  if (stackVec.size() == 0)
  {
    return;
  }
  else
  {
    stackCounter--;

    // visit(Node) physically
    nextNode = stackVec.back();
    stackVec.pop_back();

    addRetracePath(nextNode, startNode, pathList, curDir);
    modDFS(nextNode, stackVec, visitedList, visitedCounter, stackCounter, pathList, curDir);
  }
}

void moveToNextNodePhysically(Node *fromNode, Node *toNode, Driver *car, int *curDir)
{
  // Find turning direction
  int fromRow = fromNode->row;
  int fromCol = fromNode->col;
  int toRow = toNode->row;
  int toCol = toNode->col;

  // Check the axis of motion
  // No change in row value - Vertical motion
  if ((fromRow - toRow) == 0)
  {
    if (fromCol > toCol) // Need a west motion
    {
      switch (*curDir)
      {
      case 0: // Facing north
        car->left();
        car->forward();
        break;
      case 1: // Facing east
        car->left();
        car->left();
        car->forward();
        break;
      case 2: // Facing south
        car->right();
        car->forward();
        break;
      case 3: // Facing west
        car->forward();
        break;
      default:
        break;
      }
      *curDir = 3;
    }
    else // Needs an east motion
    {
      switch (*curDir)
      {
      case 0: // Facing north
        car->right();
        car->forward();
        break;
      case 1: // Facing east
        car->forward();
        break;
      case 2: // Facing south
        car->left();
        car->forward();
        break;
      case 3: // Facing west
        car->left();
        car->left();
        car->forward();
        break;
      default:
        break;
      }
      *curDir = 1;
    }
  }
  else // Needs a vertical motion
  {
    if (fromRow > toRow) // Needs a north motion
    {
      switch (*curDir)
      {
      case 0: // Facing north
        car->forward();
        break;
      case 1: // Facing east
        car->left();
        car->forward();
        break;
      case 2: // Facing south
        car->left();
        car->left();
        car->forward();
        break;
      case 3: // Facing west
        car->right();
        car->forward();
        break;
      default:
        break;
      }
      *curDir = 0;
    }
    else // Needs an west motion
    {
      switch (*curDir)
      {
      case 0: // Facing north
        car->left();
        car->left();
        car->forward();
        break;
      case 1: // Facing east
        car->right();
        car->forward();
        break;
      case 2: // Facing south
        car->forward();
        break;
      case 3: // Facing west
        car->left();
        car->forward();
        break;
      default:
        break;
      }
      *curDir = 2;
    }
  }
}