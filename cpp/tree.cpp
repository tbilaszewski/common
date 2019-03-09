#include <stdio.h>
#include <iostream>
#include <algorithm>

class Node
{

public:

  Node (Node * left, Node * right, const char *n):name (n)
  {
    left_n = left;
    right_n = right;
  }

  Node *getLeft ()
  {
    return left_n;
  }

  Node *getRight ()
  {
    return right_n;
  }
  bool hasLeft ()
  {
    if (getLeft () != NULL)
      return true;
    else
      return false;
  }
  bool hasRight ()
  {
    if (getRight () != NULL)
      return true;
    else
      return false;
  }
  const char *getName ()
  {
    return name;
  }
    
  int height ()
  {

    int r_height=-1;
    int l_height=-1;
    if(this == NULL)  
      return 0;
    if(hasLeft())  
      l_height = getLeft ()->height ();
    if(hasRight())
      r_height = getRight ()->height ();

    return std::max (r_height, l_height) + 1;
  }
  
  void getHeight()
  {
      std::cout << getName() << " height: " << height() << std::endl;
  }

  ~Node ()
  {
    delete left_n;
    delete right_n;
  }

protected:
  const char *name = "";
  Node *left_n;
  Node *right_n;

};

int
main ()
{
  Node *leaf0 = new Node (NULL, NULL, "leaf0");
  Node *leaf1 = new Node (leaf0, NULL, "leaf1");
  Node *leaf2 = new Node (NULL, NULL, "leaf2");
  Node *node3 = new Node (leaf1, leaf2,"node3");
  Node *leaf4 = new Node (NULL, NULL, "leaf4");
  Node *node5 = new Node (leaf4,NULL,"node5");
  Node *root = new Node (node3, node5, "root");

  root->getHeight();
  node3->getHeight();
  
  return 0;
}
