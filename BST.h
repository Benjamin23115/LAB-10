#pragma once
template <typename TYPE>
class BinarySearchTree
//Since we had to implement it and weren't given a file to inherit from public class, I took the liberty of trying
//To keep everything as void functions (similar to how the other assignments have been) and changed certain functions
//As needed, for example if it made more sense to make a function a void or a bool.
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
    bool search(Node *node, TYPE item)
    {
        if (node == nullptr)
            throw std::runtime_error("Item not found in tree");
        else if (cmp(item, node->data))
        {
            return search(node->left, item); // search in the left subtree
        }
        else if (cmp(node->data, item))
        {
            return search(node->right, item); // search in the right subtree
        }
        else
        {
            return true; // item found
        }
    }
};