#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>
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
    Node *root = nullptr;

public:
    // Changed the constructor here to not take in a comparison function in it as I have the actual comparison function itself in the main file
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        destroyTree(root);
    }
    void destroyTree(Node *node)
    {
        if (node == nullptr)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
        root = nullptr;
    }
    // Before I had an insert function that didn't really make much sense as there is no need for a node when inserting rather just the data itselfs

    void insert(TYPE item)
    {
        if (root == nullptr)
        {
            root = new Node(item);
        }
        else
        {
            Node *current = root;
            while (true)
            {
                if (compare(item, current->data) == -1)
                {
                    if (current->left == nullptr)
                    {
                        current->left = new Node(item);
                        break;
                    }
                    else
                    {
                        current = current->left;
                        break;
                    }
                }
                else if (compare(current->data, item) == 1)
                {
                    if (current->right == nullptr)
                    {
                        current->right = new Node(item);
                        break;
                    }
                    else
                    {
                        current = current->right;
                        break;
                    }
                }
            }
        }
    }
    // Refactored the remove function to use a friend function here to remove properly (compared to how this function was originally set up)
    void remove(TYPE item)
    {
        root = removeNode(root, item);
    }

    Node *removeNode(Node *node, TYPE item)
    {
        if (node == nullptr)
            return node;

        if (compare(item, node->data) == -1)
            node->left = removeNode(node->left, item);
        else if (compare(node->data, item) == 1)
            node->right = removeNode(node->right, item);
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                Node *temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = removeNode(node->right, temp->data);
                delete temp;
            }
        }
        return node;
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
        if (root == nullptr)
            throw std::runtime_error("Item not found in tree");
        else if (compare(item, node->data) == -1)
        {
            return search(node->left, item); // search in the left subtree
        }
        else if (compare(node->data, item) == 1)
        {
            return search(node->right, item); // search in the right subtree
        }
        else
        {
            return node->data; // item found
        }
    }
    // This function is the left Rotation in DSW
    // I had a super simple leftRotation/rightRotation function before, but after reading the grandparent note on the slides I realized I needed to change my functions to include parents and grandparents, not just children nodes.

    void leftRotation(Node *node, int m)
    {
        Node *current = node->right;
        for (int i = 0; i < m; i++)
        {
            Node *oldCurrent = current;
            current = current->right;
            node->right = current;
            oldCurrent->right = current->left;
            current->left = oldCurrent;
            node = current;
            current = current->right;
        }
    }
    // this function is the right rotation in DSW

    int rightRotation(Node *node)
    {
        int count = 0;
        Node *current = node->right;
        // We traverse until current is nullptr/NULL
        while (current)
        {
            if (current->left)
            {
                Node *oldCurrent = current;
                current = current->left;
                oldCurrent = current->right;
                current->right = oldCurrent;
                node->right = current;
            }
            // Here left doesn't exist so we traverse down the right side instead
            else
            {
                count++;
                node = current;
                current = current->right;
            }
        }
        return count;
    }
    // For this function, im using https://www.geeksforgeeks.org/day-stout-warren-algorithm-to-balance-given-binary-search-tree/ as a reference
    // Something to note, designerShoeWarehouse is the DSW method algorithm. Its just a little joke that I thought of when DSW was being lectured about.
    Node *designerShoeWarehouse()
    {
        Node *current = new Node(0);
        current->right = root;
        int count = rightRotation(current);
        int h = log2(count + 1);
        int m = pow(2, h) - 1;
        leftRotation(current, count - m);
        for (m = m / 2; m > 0; m /= 2)
        {
            leftRotation(current, m);
        }
        return current->right;
    }
    int compare(const TYPE &item1, const TYPE &item2)
    {
        if (item1 < item2)
            return -1;
        if (item1 == item2)
            return 0;

        return 1;
    }
};