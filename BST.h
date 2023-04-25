#pragma once
#include <cmath>
template <typename TYPE>
class BinarySearchTree
// Since we had to implement it and weren't given a file to inherit from public class, I took the liberty of trying
// To keep everything as void functions (similar to how the other assignments have been) and changed certain functions
// As needed, for example if it made more sense to make a function a void or a bool.
{
private:
    struct Node
    {
        TYPE data;
        Node *left;
        Node *right;
        Node(TYPE item) : data(item), left(nullptr), right(nullptr) {}
    };
    int size;
    Node *root = nullptr;

public:
    // Changed the constructor here to not take in a comparison function in it as I have the actual comparison function itself in the main file
    BinarySearchTree() : size(0) {}
    ~BinarySearchTree()
    {
        destroyTree(root);
    }
    void destroyTree(Node *node)
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
        {
            node = new Node(item);

            size++;
        }
        else
        {

            // TODO: Add value checking here
            //  Using the pointer comparison stuff here
            if (cmp(item, node->data))
                insert(node->left, item);
            else if (cmp(node->data, item))
                insert(node->right, item);
            // Throwing an error if the item is equal to something in the tree
            else
                throw std::runtime_error("Duplicate value in the tree");
        }
    }
    void remove(Node *&node, TYPE item)
    {
        if (node == nullptr)
            return;
        if (cmp(item, node->data))
            remove(node->left, item);
        else if (cmp(node->data, item))
            remove(node->right, item);
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node;
                node = root->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node;
                node = root->left;
                delete temp;
            }
            else
            {

                Node *temp = minValueNode(root->right);
                node->data = temp->data;
                remove(root->right, temp->data);
                delete temp;
            }
        }
    }
    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
    TYPE search(Node *node, TYPE item)
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
            return node->data; // item found
        }
    }
    // This function is the left Rotation in DSW
    void leftRotation(Node *node)
    {
        // TODO update the parent node
        Node *current = node->right;
        if (current->left != nullptr)
        {
            node->right = current->left;
        }
        else
        {
            node->right = nullptr;
        }
        current->left = node;
    }
    // this function is the right rotation in DSW
    void rightRotation(Node *node)
    {
        // TODO update the parent node
        Node *current = node->left;
        if (current->right != nullptr)
        {
            node->left = current->right;
        }
        else
        {
            node->left = nullptr;
        }
        current->right = node;
    }
    int getSize(void)
    {
        return size;
    }
    // For this function, im using https://www.geeksforgeeks.org/day-stout-warren-algorithm-to-balance-given-binary-search-tree/ as a reference
    Node *designerShoeWarehouse(void)
    {
        Node *current = new Node(0);
        current->right = root;
        int count = getSize();
        int h = log2(count + 1);
        int m = pow(2, h) - 1;
        // Getting our tree to be a right-leaning linked list
        rightRotation(current);
        // Doing rotations to make the tree balanced
        for (m = m / 2; m > 0; m /= 2)
        {
            leftRotation(current);
        }
        return current->right;
    }
};