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

    return 0;
}
