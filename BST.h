#pragma once
template <typename TYPE>
class BinarySearchTree
// constructor that takes a function pointer to a comparison function.
//  Not sure what you meant by this ^^. I assume we use the int (*cmp)(const TYPE &item1, const TYPE &item2)
//  That we used in the LinkedList for comparison. That is what I will be using for this template implementation
// Since its the comparison function im the most familiar with.
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
    int (*cmp)(const TYPE &item1, const TYPE &item2);

public:
    BinarySearchTree(int (*cmpFunc)(const TYPE &item1, const TYPE &item2)) : cmp(cmpFunc) {}
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
    void insert(Node *&node, TYPE item)
    {
        if (node == nullptr)
            node = new Node(item);
        else
        {
            // Using the pointer comparison stuff here
            if (cmp(item, root->data))
                Insert(root->left, item);
            else if (cmp(root->data, item))
                Insert(root->right, item);
            // Throwing an error if the item is equal to something in the tree
            else
                throw std::runtime_error("Duplicate value in the tree");
        }
    }
    void remove(Node *&node, TYPE item)
    {
        if (root == nullptr)
            return;
        if (cmp(item, root->data))
            remove(root->left, item);
        else if (cmp(root->data, item))
            remove(root->right, item);
        else
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else if (root->left == nullptr)
            {
                Node *temp = node;
                node = root->right;
                delete temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = node;
                node = root->left;
                delete temp;
            }
            else
            {

                Node *temp = minValueNode(root->right);
                root->data = temp->data;
                remove(root->right, temp->data);
            }
        }
    }
    TYPE *minValueNode(Node *node)
    {
        Node *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
};