#include <iostream>
#include "BST.h"
using namespace std;
template <typename TYPE>
int compare(const TYPE &item1, const TYPE &item2)
{
    if (item1 < item2)
        return -1;
    if (item1 == item2)
        return 0;

    return 1;
}

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


    return 0;
}
