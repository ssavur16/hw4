#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    // AVL tree test: debugging
    AVLTree<int, int> ct;
    ct.insert(make_pair(-17, -17));
    ct.insert(make_pair(-142, -142));
    ct.insert(make_pair(137, 137));
    ct.insert(make_pair(21, 21));
    ct.insert(make_pair(-48, -48));

    ct.insert(make_pair(-59, -59));
    ct.insert(make_pair(-10, -10));
    ct.insert(make_pair(-98, -98));
    ct.insert(make_pair(20, 20));
    ct.insert(make_pair(-128, -128));

    ct.insert(make_pair(48, 48));
    ct.insert(make_pair(138, 138));
    ct.insert(make_pair(24, 24));
    ct.insert(make_pair(94, 94));
    ct.insert(make_pair(-113, -113));

    ct.insert(make_pair(-135, -135));
    ct.insert(make_pair(-144, -144));
    ct.insert(make_pair(-110, -110));
    ct.insert(make_pair(-114, -114));
    ct.insert(make_pair(-86, -86));

    ct.insert(make_pair(123, 123));
    ct.insert(make_pair(-116, -116));
    ct.insert(make_pair(14, 14));
    ct.insert(make_pair(-18, -18));
    ct.insert(make_pair(93, 93));

    ct.insert(make_pair(-45, -45)); 
    ct.insert(make_pair(106, 106));
    ct.insert(make_pair(58, 58));
    ct.insert(make_pair(36, 36));
    ct.insert(make_pair(84, 84));
    ct.print();

    return 0;
}
