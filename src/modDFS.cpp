#include "modDFS.h"

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

void addRetracePath(Node *destinationNode, Node *curNode, std::vector<Node *> *pathList)
{
  if (isNextChildOfCurrent(destinationNode, curNode))
  {
    return;
  }
  else
  {
    pathList->push_back(curNode->parent);
    addRetracePath(destinationNode, curNode->parent, pathList);
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

void modDFS(Node *startNode, std::vector<Node *> stackVec, Node **visitedList, int visitedCounter, int stackCounter, std::vector<Node *> *pathList)
{
  // startNode is the name of the current node

  // std::cout<<"Inside DFS "<<iterationNo<<"\n";
  //  Add X to visited and increment counter

  // Init pathList
  startNode->visited = true;
  pathList->push_back(startNode);

  visitedList[visitedCounter] = startNode;
  visitedCounter++;

  // Scanning for Obstacles
  // relMapper.updateMap();
  // fullMapper.updateMap();
  // Arr_to_graph();

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

    addRetracePath(nextNode, startNode, pathList);
    modDFS(nextNode, stackVec, visitedList, visitedCounter, stackCounter, pathList);
  }
}
