#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

// helper function to determine if node is a leaf node
bool isLeaf(Node* n) {
  if(n == NULL) {
    return false;
  }
  else {
    return ((n->left == NULL) && (n->right == NULL));
  }
}

// helper function to determine if node has 2 children
bool hasTwoChildren(Node* n) {
  if(n == NULL) {
    return false;
  }
  else {
    return ((n->left != NULL) && (n->right != NULL)); 
  }
}

// helper function to return length of path from node n to leaf
int distToLeaf(Node* n) {
  if(n == NULL) {
    return 0;
  }
  else if(isLeaf(n)) {
    return 1;
  }
  else if(n->left != NULL) {
    return distToLeaf(n->left) + 1;
  }
  else {
    return distToLeaf(n->right) + 1;
  }
}

// helper function to return child of single parent
Node* aliveChild(Node* root) {
  if(root->left == NULL) {
    return root->right;
  }
  else return root->left;
}

bool equalPaths(Node * root)
{
    // called on tree with 0 or 1 nodes: return true
    if(isLeaf(root) || (root == NULL)) {
        return true;
    }

    if(!hasTwoChildren(root)) {
      Node* child = aliveChild(root);

      // called on tree with only 2 nodes: return true
      if(isLeaf(child)) {
        return true;
      }
      
      else return equalPaths(child);
    }
    
    // head recursion: recursive calls to smaller binary trees
    if(hasTwoChildren(root->left)) { 
      if(!equalPaths(root->left)) {
        return false;
      }
    }
    if(hasTwoChildren(root->right)) { 
      if(!equalPaths(root->right)) {
        return false;
      }
    }

    // evaluate this binary tree
    if(hasTwoChildren(root)) {
      // one child is a leaf node and the other child is not
      if(isLeaf(root->left) != isLeaf(root->right)) {
        return false;
      }

      // both children are or aren't leaf nodes
      else {
        if(distToLeaf(root->left) == distToLeaf(root->right)) {
          return true;
        }
      }
    }
    
    return false;
}

