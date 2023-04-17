template <typename TYPE>
class BinarySearchTree
{
private:
    struct Node
    {
        TYPE data;
        Node *left;
        Node *right;
        Node(TYPE item) : data(item), left(nullptr), right(nullptr) {}
    };
    Node *root = nullptr;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        destroyTree(root);
    }
    void destroyTree(BinarySearchTree<TYPE> *node)
    {
        if (node == nullptr)
            return;
        else
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};