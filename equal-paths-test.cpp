#include <iostream>
#include <cstdlib>
#include "equal-paths.h"
using namespace std;


Node* a;
Node* b;
Node* c;
Node* d;
Node* e;
Node* f;
Node* g;
Node* h;
Node* i;

void setNode(Node* n, int key, Node* left=NULL, Node* right=NULL)
{
  n->key = key;
  n->left = left;
  n->right = right;
}

void test1(const char* msg)
{
  setNode(a,1,NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test2(const char* msg)
{
  setNode(a,1,b,NULL);
  setNode(b,2,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test3(const char* msg)
{
  setNode(a,1,b,c);
  setNode(b,2,NULL,NULL);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test4(const char* msg)
{
  setNode(a,1,NULL,c);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test5(const char* msg)
{
  setNode(a,1,b,c);
  setNode(b,2,NULL,d);
  setNode(c,3,NULL,NULL);
  setNode(d,4,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void falsetest3(const char* msg)
{
  setNode(a, 1, NULL, b);
  setNode(b, 3, c, d);
  setNode(c, 2, NULL, NULL);
  setNode(d, 8, e, f);
  setNode(e, 6, g, h);
  setNode(f, 9, NULL, NULL);
  setNode(g, 5, i, NULL);
  setNode(h, 7, NULL, NULL);
  setNode(i, 4, NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

int main()
{
  a = new Node(1);
  b = new Node(2);
  c = new Node(3);
  d = new Node(4);

  test1("Test1");
  test2("Test2");
  test3("Test3");
  test4("Test4");
  test5("Test5");
 
  delete a;
  delete b;
  delete c;
  delete d;

  // FalseTest3
  a = new Node(1);
  b = new Node(3);
  c = new Node(2);
  d = new Node(8);
  e = new Node(6);
  f = new Node(9);
  g = new Node(5);
  h = new Node(7);
  i = new Node(4);

  falsetest3("FalseTest3");

  delete a;
  delete b;
  delete c;
  delete d;
  delete e;
  delete f;
  delete g;
  delete h;
  delete i;
}

