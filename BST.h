template <typename TYPE>
class BinarySearchTree
{
private:
    struct Node
    {
        TYPE data;
        Node *leftChild;
        Node *rightChild;
        Node(TYPE item) : data(item), leftChild(nullptr), rightChild(nullptr) {}
    };

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        destroyTree(root);
    }
};