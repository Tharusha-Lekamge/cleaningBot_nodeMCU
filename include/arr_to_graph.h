// Add values to NodeArray

for (int rows = 0; rows < 11; rows++)
{
  for (int cols = 0; cols < 11; cols++)
  {
    nodeArray[rows][cols].col = cols;
    nodeArray[rows][cols].row = rows;
    nodeArray[rows][cols].state = fullMapTest[cols][rows];
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
        fr = nullptr; // No node to front

        // Check if the back node is obstacle
        Node backNode = nodeArray[rows + 1][cols];
        if (backNode.state == 2) // If the backNode is an obstacle
        {
          bk = nullptr;
        }
        else
        {
          bk = &backNode;
        }

        // Test for left and right availability
        if (cols == 0) //  If robot is at leftmost
        {
          Node rightNode = nodeArray[rows][cols + 1];
          if (rightNode.state == 2) // If rightNode is an obstacle
          {
            r = nullptr;
          }
          else
          {
            r = &rightNode;
          }

          l = nullptr; // No node to left
        }
        else if (cols == 10) // If robot is at rightmost
        {
          r = nullptr; // No node to right

          Node leftNode = nodeArray[rows][cols - 1];
          if (leftNode.state == 2) // If leftNode is an obstacle
          {
            l = nullptr;
          }
          else
          {
            l = &leftNode;
          }
        }
        else
        {
          Node rightNode = nodeArray[rows][cols + 1];
          if (rightNode.state == 2) // If rightNode is an obstacle
          {
            r = nullptr;
          }
          else
          {
            r = &rightNode;
          }

          Node leftNode = nodeArray[rows][cols - 1];
          if (leftNode.state == 2) // If leftNode is an obstacle
          {
            l = nullptr;
          }
          else
          {
            l = &leftNode;
          }
        }
      }
      else if (rows == 10) // No node to back
      {
        Node frontNode = nodeArray[rows - 1][cols];
        if (frontNode.state == 2) // If the frontNode is an obstacle
        {
          fr = nullptr;
        }
        else
        {
          fr = &frontNode;
        }

        bk = nullptr; // No node to the back

        // Test for left and right availability
        if (cols == 0) //  If robot is at leftmost
        {
          Node rightNode = nodeArray[rows][cols + 1];
          if (rightNode.state == 2) // If rightNode is an obstacle
          {
            r = nullptr;
          }
          else
          {
            r = &rightNode;
          }

          l = nullptr; // No node to left
        }
        else if (cols == 10) // If robot is at rightmost
        {
          r = nullptr; // No node to right

          Node leftNode = nodeArray[rows][cols - 1];
          if (leftNode.state == 2) // If leftNode is an obstacle
          {
            l = nullptr;
          }
          else
          {
            l = &leftNode;
          }
        }
        else
        {
          Node rightNode = nodeArray[rows][cols + 1];
          if (rightNode.state == 2) // If rightNode is an obstacle
          {
            r = nullptr;
          }
          else
          {
            r = &rightNode;
          }

          Node leftNode = nodeArray[rows][cols - 1];
          if (leftNode.state == 2) // If leftNode is an obstacle
          {
            l = nullptr;
          }
          else
          {
            l = &leftNode;
          }
        }
      }
      else // Robot is in middle row
      {
        Node frontNode = nodeArray[rows + 1][cols];
        if (frontNode.state == 2) // If the backNode is an obstacle
        {
          fr = nullptr;
        }
        else
        {
          fr = &frontNode;
        }

        Node backNode = nodeArray[rows + 1][cols];
        if (backNode.state == 2) // If the backNode is an obstacle
        {
          bk = nullptr;
        }
        else
        {
          bk = &backNode;
        }

        // Test for left and right availability
        if (cols == 0) //  If robot is at leftmost
        {
          Node rightNode = nodeArray[rows][cols + 1];
          if (rightNode.state == 2) // If rightNode is an obstacle
          {
            r = nullptr;
          }
          else
          {
            r = &rightNode;
          }

          l = nullptr; // No node to left
        }
        else if (cols == 10) // If robot is at rightmost
        {
          r = nullptr; // No node to right

          Node leftNode = nodeArray[rows][cols - 1];
          if (leftNode.state == 2) // If leftNode is an obstacle
          {
            l = nullptr;
          }
          else
          {
            l = &leftNode;
          }
        }
        else
        {
          Node rightNode = nodeArray[rows][cols + 1];
          if (rightNode.state == 2) // If rightNode is an obstacle
          {
            r = nullptr;
          }
          else
          {
            r = &rightNode;
          }

          Node leftNode = nodeArray[rows][cols - 1];
          if (leftNode.state == 2) // If leftNode is an obstacle
          {
            l = nullptr;
          }
          else
          {
            l = &leftNode;
          }
        }
      }
      nodeArray[rows][cols].front = fr;
      nodeArray[rows][cols].back = bk;
      nodeArray[rows][cols].right = r;
      nodeArray[rows][cols].left = l;
    }
  }
