#include <iostream>
#include "tree.h"
using namespace std;

int main()
{
    Tree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.display();
}