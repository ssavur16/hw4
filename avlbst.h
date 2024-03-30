#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* internalFind(const Key& key) const;
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current);
    void removeFix(AVLNode<Key, Value>* node, int diff);
    void rotateRight(AVLNode<Key, Value>* node);
    void rotateLeft(AVLNode<Key, Value>* node);
    bool zigzig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void removal_case_0(Node<Key, Value>* node);
    void removal_case_1(Node<Key, Value>* node);
    AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* current);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
  Key item_key = new_item.first;
  Value item_value = new_item.second;

  // if empty tree, set new_item as root
  if(this->empty()) {
    AVLNode<Key, Value>* item_node = new AVLNode<Key, Value>(item_key, item_value, nullptr);
    this->root_ = item_node;
  }
  
  else { // non-empty tree
    // if key is already in tree, update value
    if(internalFind(item_key) != NULL) {
      internalFind(item_key)->setValue(item_value);
    }

    // if not in tree, insert new_item
    else {
      AVLNode<Key, Value>* parent = static_cast<AVLNode<Key, Value>*>(this->root_);
      AVLNode<Key, Value>* item_node = new AVLNode<Key, Value>(item_key, item_value, nullptr);

      // traverse through tree and insert at correct position
      while(parent != NULL) {
        Key parent_key = parent->getKey();

        if(item_key < parent_key) {
          if(parent->getLeft() != NULL) {
            parent = parent->getLeft();
          }
          else { // if no left child, insert node at that position
            item_node->setParent(parent);
            parent->setLeft(item_node);

            // update parent balance
            parent->updateBalance(-1);
            break;
          }
        }

        else { // item_key > current_key
          if(parent->getRight() != NULL) {
            parent = parent->getRight();
          }
          else { // if no right child, insert node at that position
            item_node->setParent(parent);
            parent->setRight(item_node);

            // update parent balance
            parent->updateBalance(1);
            break;
          }
        }
      }

      // if b(p) != 0, call insertFix
      if(parent->getBalance() != 0) {
        insertFix(parent, item_node);
      }
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current)
{
  // if grandparent exists, update balance
  if((parent != nullptr) && (parent->getParent() != nullptr)) {
    AVLNode<Key, Value>* grandparent = parent->getParent();

    // parent is a left child of grandparent
    if(parent == grandparent->getLeft()) {
      grandparent->updateBalance(-1);
      int gp_balance = (int)grandparent->getBalance();

      if(gp_balance == -1) {
        insertFix(grandparent, parent);
      }

      else if(gp_balance == -2) {
        // zig-zig -> rotateRight(g)
        if(zigzig(grandparent, parent, current)) {
          rotateRight(grandparent);

          // update balances
          parent->setBalance(0);
          grandparent->setBalance(0);
        }
        // zig-zag -> rotateLeft(p); rotateRight(g)
        else {
          rotateLeft(parent);
          rotateRight(grandparent);

          // update balances
          int curr_bal = (int)current->getBalance();

          if(curr_bal == -1) {
            parent->setBalance(0);
            grandparent->setBalance(1);
            current->setBalance(0);
          }

          else if(curr_bal == 0) {
            parent->setBalance(0);
            grandparent->setBalance(0);
            current->setBalance(0);
          }

          else { // curr_bal == +1
            parent->setBalance(-1);
            grandparent->setBalance(0);
            current->setBalance(0);
          }
        }
      }
    }

    // parent is a right child of grandparent
    else {
      grandparent->updateBalance(1);
      int gp_balance = (int)grandparent->getBalance();

      if(gp_balance == 1) {
        insertFix(grandparent, parent);
      }

      else if(gp_balance == 2) {
        // zig-zig -> rotateLeft(g)
        if(zigzig(grandparent, parent, current)) {
          rotateLeft(grandparent);

          // update balances
          parent->setBalance(0);
          grandparent->setBalance(0);
        }
        // zig-zag -> rotateRight(p); rotateLeft(g)
        else {
          rotateRight(parent);
          rotateLeft(grandparent);

          // update balances
          int curr_bal = (int)current->getBalance();

          if(curr_bal == 1) {
            parent->setBalance(0);
            grandparent->setBalance(-1);
            current->setBalance(0);
          }

          else if(curr_bal == 0) {
            parent->setBalance(0);
            grandparent->setBalance(0);
            current->setBalance(0);
          }

          else { // curr_bal == -1
            parent->setBalance(1);
            grandparent->setBalance(0);
            current->setBalance(0);
          }
        }
      }
    }
  }
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::internalFind(const Key& key) const
{
    // if empty tree, return NULL
    if(this->empty()) {
        return NULL;
    }

    // traverse through tree
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
    while(current != NULL) {
        // check if current node's key equals desired key
        Key current_key = current->getKey();

        if(key == current_key) {
            return current;
        }

        else if(key < current_key) {
            current = current->getLeft();
        }

        else if(key > current_key) {
            current = current->getRight();
        }
    }

    // if key not found, return NULL 
    return NULL;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::zigzig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) {
  // n is a left child of p
  if(n == p->getLeft()) {
    if(p == g->getLeft()) {
      return true;
    }
    else return false;
  }

  // n is a right child of p, i.e. n == p->getRight()
  else if(p == g->getRight()) return true;
  else return false;
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node)
{
  AVLNode<Key, Value>* child = node->getLeft();
  AVLNode<Key, Value>* parent = node->getParent();

  // update root_ if necessary
  if(node == this->root_) {
    this->root_ = child;
  }

  // update node, child and parent pointers
  if(child->getRight() != NULL) {
    child->getRight()->setParent(node);
  }
  node->setLeft(child->getRight());
  child->setRight(node);
  node->setParent(child);
  child->setParent(parent);
  if(parent != NULL) {
    if(node == parent->getRight()) {
      parent->setRight(child);
    }
    else parent->setLeft(child);
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node)
{
  AVLNode<Key, Value>* child = node->getRight();
  AVLNode<Key, Value>* parent = node->getParent();

  // update root_ if necessary
  if(node == this->root_) {
    this->root_ = child;
  }

  // update pointers of node, child and parent
  if(child->getLeft() != NULL) {
    child->getLeft()->setParent(node);
  }
  node->setRight(child->getLeft());
  child->setLeft(node);
  node->setParent(child);
  child->setParent(parent);
  if(parent != NULL) {
    if(node == parent->getRight()) {
      parent->setRight(child);
    }
    else parent->setLeft(child);
  }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
  AVLNode<Key, Value>* node = internalFind(key);

  // only remove if node exists in tree
  if(node != NULL) {
    // if 2 children, swap with predecessor
    if(this->numChildren(node) == 2) {
      AVLNode<Key, Value>* pred = predecessor(node);
      nodeSwap(node, pred);
    }

    AVLNode<Key, Value>* parent = node->getParent();
    if(parent != NULL) {
      // find difference to update parent balance
      int diff;
      if(node == parent->getLeft()) {
        diff = 1;
      }
      else { // node is a right child of parent node
        diff = -1;
      }

      // delete node and update pointers
      int n_children = this->numChildren(node);
      if(n_children == 0) removal_case_0(node);
      else removal_case_1(node);

      // patch tree
      removeFix(parent, diff);
    }
  }
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* current)
{
    AVLNode<Key, Value>* temp = current;

    // if left child exists, predecessor is rightmost node
    if(temp->getLeft() != NULL) {
        temp = temp->getLeft();
        while(temp->getRight() != NULL) {
            temp = temp->getRight();
        }
    }

    // else, predecessor is parent of first ancestor right child
    else {
        while(temp != NULL) {
            if(temp == temp->getParent()->getRight()) {
                temp = temp->getParent();
                break;
            }
            temp = temp->getParent();
        }
    }

    return temp;
}

// if 0 children, simply remove
template<class Key, class Value>
void AVLTree<Key, Value>::removal_case_0(Node<Key, Value>* node) 
{
  // special case: node = root_
  if(node == this->root_) {
    this->root_ = NULL;
  }

  // update node's parent to have NULL child
  else {
    if(node == node->getParent()->getLeft()) {
      node->getParent()->setLeft(NULL);
    }
    else {
      node->getParent()->setRight(NULL);
    }
  }

  delete node;
}

// if 1 child, promote child
template<class Key, class Value>
void AVLTree<Key, Value>::removal_case_1(Node<Key, Value>* node)
{
  // get child node
  Node<Key, Value>* child;
  if(node->getLeft() != NULL) {
    child = node->getLeft();
  }
  else {
    child = node->getRight();
  }

  // update child node's parent to grandparent
  if(node == this->root_) {
    child->setParent(NULL);
    this->root_ = child;
  }
  else {
    child->setParent(node->getParent());

    // update grandparent's left/right child to child node
    if(node == child->getParent()->getLeft()) {
      child->getParent()->setLeft(child);
    }
    else {
      child->getParent()->setRight(child);
    }
  }

  delete node;
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int diff)
{
  if(node != NULL) /* && (parent != NULL) */ {
    AVLNode<Key, Value>* parent = node->getParent();

    // compute diff for next recursive call
    int ndiff;
    if(parent != NULL) {
      if(node == parent->getLeft()) {
        ndiff = 1;
      }
      else ndiff = -1;
    }

    node->updateBalance(diff);
    int8_t node_bal = node->getBalance();

    if(node_bal == 0) {
      removeFix(parent, ndiff);
    }
    else if(node_bal == -2) {
      AVLNode<Key, Value>* child = node->getLeft();
      int8_t child_bal = child->getBalance();

      if(child_bal == -1) {
        // zig-zig case
        rotateRight(node);
        node->setBalance(0);
        child->setBalance(0);
        removeFix(parent, ndiff);
      }
      else if(child_bal == 0) {
        // zig-zig case
        rotateRight(node);
        node->setBalance(-1);
        child->setBalance(1);
      }
      else { // child_bal == +1
        // zig-zag case
        AVLNode<Key, Value>* grandchild = child->getRight();
        int8_t grandchild_bal = grandchild->getBalance();

        rotateLeft(child);
        rotateRight(node);

        if(grandchild_bal == 1) {
          node->setBalance(0);
          child->setBalance(-1);
          grandchild->setBalance(0);
        }
        else if(grandchild_bal == 0) {
          node->setBalance(0);
          child->setBalance(0);
          grandchild->setBalance(0);
        }
        else { // grandchild_bal == -1
          node->setBalance(1);
          child->setBalance(0);
          grandchild->setBalance(0);
        }

        removeFix(parent, ndiff);
      }
    }
    else if(node_bal == 2) {
      AVLNode<Key, Value>* child = node->getRight();
      int8_t child_bal = child->getBalance();

      if(child_bal == 1) {
        // zig-zig case
        rotateLeft(node);
        node->setBalance(0);
        child->setBalance(0);
        removeFix(parent, ndiff);
      }
      else if(child_bal == 0) {
        // zig-zig case
        rotateLeft(node);
        node->setBalance(1);
        child->setBalance(-1);
      }
      else { // child_bal == -1
        // zig-zag case
        AVLNode<Key, Value>* grandchild = child->getLeft();
        int8_t grandchild_bal = grandchild->getBalance();

        rotateRight(child);
        rotateLeft(node);

        if(grandchild_bal == -1) {
          node->setBalance(0);
          child->setBalance(1);
          grandchild->setBalance(0);
        }
        else if(grandchild_bal == 0) {
          node->setBalance(0);
          child->setBalance(0);
          grandchild->setBalance(0);
        }
        else { // grandchild_bal == +1
          node->setBalance(-1);
          child->setBalance(0);
          grandchild->setBalance(0);
        }

        removeFix(parent, ndiff);
      }
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif