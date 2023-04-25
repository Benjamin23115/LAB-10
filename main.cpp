#include <iostream>
#include "BST.h"
using namespace std;

int main(int argc, char const *argv[])
{
    BinarySearchTree<int> BST;
    BST.insert(50);
    BST.insert(20);
    BST.insert(25);
    BST.insert(49);
    BST.insert(42);
    BST.insert(9);
    BST.insert(2);

    BST.designerShoeWarehouse();

cout << " operation done"  << endl;

    return 0;
}
