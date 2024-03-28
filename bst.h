#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <queue>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    virtual void insert(const std::pair<const Key, Value>& keyValuePair);
    virtual void remove(const Key& key);
    void clear();
    bool isBalanced() const;
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const;
    Node<Key, Value> *getSmallestNode() const;
    static Node<Key, Value>* predecessor(Node<Key, Value>* current);
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    int numChildren(Node<Key, Value>* current) const;
    void remove_0(Node<Key, Value>* node);
    void remove_1(Node<Key, Value>* node);
    bool isBalanced(Node<Key, Value>* root) const;
    int left_height(Node<Key, Value>* current) const;
    int right_height(Node<Key, Value>* current) const;
    static Node<Key, Value>* successor(Node<Key, Value>* current);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if(this->current_ == NULL) {
        return rhs.current_ == NULL;
    }
    else if(rhs.current_ == NULL) {
        return this->current_ == NULL;
    }
    else {
        return this->current_->getItem() == (rhs.current_)->getItem();
    }
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if(this->current_ == NULL) {
        return rhs.current_ != NULL;
    }
    else if(rhs.current_ == NULL) {
        return this->current_ != NULL;
    }
    else {
        return this->current_->getItem() != (rhs.current_)->getItem();
    }
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // need iterator.current_ to point to successor
    current_ = BinarySearchTree<Key, Value>::successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    if(!empty()) {
        clear();
    }
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    Key key = keyValuePair.first;
    Value value = keyValuePair.second;

    // if key is already in tree, overwrite current value
    if(internalFind(key) != NULL) {
        internalFind(key)->setValue(value);
    }

    // if key is not already in tree, insert new node
    else {
        // called on empty tree
        if(empty()) {
            root_ = new Node<Key, Value>(key, value, nullptr);
        }

        // if not empty, traverse through tree
        else {
            Node<Key, Value>* current = root_;
            while(current != NULL) {
                // check if current node's key equals desired key
                Key current_key = current->getKey();

                if(key < current_key) {
                    if(current->getLeft() != NULL) {
                        current = current->getLeft();
                    }
                    else { // insert new node on left
                        Node<Key, Value>* node = new Node<Key, Value>(key, value, current);
                        current->setLeft(node);
                        break;
                    }
                }

                else { // key > current_key
                    if(current->getRight() != NULL) {
                        current = current->getRight();
                    }
                    else { // insert new node on right
                        Node<Key, Value>* node = new Node<Key, Value>(key, value, current);
                        current->setRight(node);
                        break;
                    }
                }
            }
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    Node<Key, Value>* removal_node = internalFind(key);

    // function will only remove if node exists in tree
    if(removal_node != NULL) {
        int n_children = numChildren(removal_node);

        // if removal_node has 0 children, simply remove
        if(n_children == 0) {
            // special case: removal_node is root_
            if(removal_node == root_) {
              delete removal_node;
              root_ = NULL;
            }
            else remove_0(removal_node);
        }

        // if removal_node has 1 child, promote child
        else if(n_children == 1) {
            remove_1(removal_node);
        }

        // if removal_node has 2 children, swap with predecessor
        else {
            Node<Key, Value>* pred = BinarySearchTree<Key, Value>::predecessor(removal_node);
            nodeSwap(removal_node, pred);
            
            if(pred->getParent() == NULL) {
              root_ = pred;
            }

            // remove node at new location based on numChildren
            if(numChildren(removal_node) == 0) {
                remove_0(removal_node);
            }
            else { // numChildren(removal_node) == 1
                remove_1(removal_node);
            }
        }
        
    }
}

// helper function for remove() for 0-child case
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove_0(Node<Key, Value>* node) {
    // determine if node was left or right child and update parent
    if(node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(NULL);
    }
    else node->getParent()->setRight(NULL);
    delete node;
}

// helper function for remove() for 1-child case
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove_1(Node<Key, Value>* node) {
    // get child to swap with current node
    Node<Key, Value>* child;

    if(node->getLeft() != NULL) {
        child = node->getLeft();
    }
    else {
        child = node->getRight();
    }

    // update child node's parent to grandparent
    if(node == root_) {
        child->setParent(NULL);
        root_ = child;
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
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    Node<Key, Value>* temp = current;

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

// helper function for iterator class to call when incrementing (i.e. ++)
template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    Node<Key, Value>* temp = current;
    
    // if right child exists, successor is leftmost node
    if(temp->getRight() != NULL) {
        temp = temp->getRight();
        while(temp->getLeft() != NULL) {
            temp = temp->getLeft();
        }
    }

    // else, successor is parent of first ancestor left child
    else {
        while(temp != NULL) {
            // no successor if got to root without finding left child
            if(temp->getParent() == NULL) {
                temp = NULL;
                break;
            }
            else if(temp == temp->getParent()->getLeft()) {
                temp = temp->getParent();
                break;
            }
            temp = temp->getParent();
        }
    }
    return temp;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    if(!empty()) {
        std::queue<Node<Key, Value>*> nodes;
        nodes.push(root_);
        Node<Key, Value>* current;

        while(!nodes.empty()) {
            current = nodes.front();
            if(current->getLeft() != NULL) {
                nodes.push(current->getLeft());
            }
            if(current->getRight() != NULL) {
                nodes.push(current->getRight());
            }
            nodes.pop();
            delete current;
        }
    }

    root_ = NULL;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // smallest node = leftmost node in tree
    Node<Key, Value>* current = root_;

    while(current->getLeft() != NULL) {
        current = current->getLeft();
    }

    return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // if empty tree, return NULL
    if(empty()) {
        return NULL;
    }

    // traverse through tree
    Node<Key, Value>* current = root_;
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

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // called on tree with 0 or 1 nodes: return true
    if((root_ == NULL) || (numChildren(root_) == 0)) {
        return true;
    }

    // root_ has only 1 child: if only two nodes in tree, return true
    if(numChildren(root_) == 1) {
        if((root_->getLeft() != NULL) && (numChildren(root_->getLeft()) == 0)) {
            return true;
        }
        else if((root_->getRight() != NULL) && (numChildren(root_->getRight()) == 0)) {
            return true;
        }
        else return false;
    }

    // if root_ has 2 children, perform recursive tree traversals
    return isBalanced(root_);
}

// helper function for isBalanced() with input argument for root Node
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced(Node<Key, Value>* root) const
{
    // function only called if root_ has 2 children

    // head recursive calls to smaller binary trees
    if(numChildren(root->getLeft()) >= 1) {
        if(!isBalanced(root->getLeft())) {
            return false;
        }
    }
    if(numChildren(root->getRight()) >= 1) {
        if(!isBalanced(root->getRight())) {
            return false;
        }
    }

    // evaluate heights of left and right subtrees
    if(abs(left_height(root->getLeft()) - right_height(root->getRight())) > 1) {
        return false;
    }
    else return true;
}

// helper function for isBalanced() to return height of left subtree
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::left_height(Node<Key, Value>* current) const
{
    if(current == NULL) {
        return 0;
    }
    else if(numChildren(current) == 0) {
        return 1;
    }
    else if(current->getLeft() != NULL) {
        return left_height(current->getLeft()) + 1;
    }
    else {
        return left_height(current->getRight()) + 1;
    }
}

// helper function for isBalanced() to return height of right subtree
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::right_height(Node<Key, Value>* current) const
{
    if(current == NULL) {
        return 0;
    }
    else if(numChildren(current) == 0) {
        return 1;
    }
    else if(current->getRight() != NULL) {
        return right_height(current->getRight()) + 1;
    }
    else {
        return right_height(current->getLeft()) + 1;
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

// returns number of children of current node: legal values are {0, 1, 2}
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::numChildren(Node<Key, Value>* current) const {
    if(current == NULL) return 0;
    else if((current->getLeft() == NULL) && (current->getRight() == NULL)) {
        return 0;
    }

    else if((current->getLeft() != NULL) && (current->getRight() != NULL)) {
        return 2;
    }

    else return 1;
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif