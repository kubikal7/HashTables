#pragma once
#include <iostream>
#include "KeyValuePair.h"
#include "Hash.h"

struct TreeNode {
    KeyValuePair data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int key, int value) : data{ key, value }, left(nullptr), right(nullptr), parent(nullptr) {}
};


class ListBST : public Hash {
private:
    TreeNode* root;

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void removeNode(TreeNode* node) {
        if (node->left == nullptr && node->right == nullptr) {                      //check if node doesn't have children
            if (node->parent == nullptr) {
                root = nullptr;
            }
            else if (node == node->parent->left) {                                  //if node is left child
                node->parent->left = nullptr;
            }
            else {                                                                  //if node is right child
                node->parent->right = nullptr;
            }
            delete node;
        }
        else if (node->left != nullptr && node->right != nullptr) {                 //check if node has children
            TreeNode* minNode = findMin(node->right);
            node->data = minNode->data;
            removeNode(minNode);
        }
        else {                                                                      //if node has one child
            TreeNode* child = (node->left != nullptr) ? node->left : node->right;       
            if (node->parent == nullptr) {
                root = child;
            }
            else if (node == node->parent->left) {                                  //if node is left child
                node->parent->left = child;
            }
            else {
                node->parent->right = child;                                        //if node is right child
            }
            child->parent = node->parent;
            delete node;
        }
    }

    void printTree(TreeNode* node, int depth) {
        if (node != nullptr) {
            printTree(node->right, depth + 1);
            std::cout << std::string(depth * 2, ' ') << "Key = " << node->data.key << ", Value = " << node->data.value << std::endl;
            printTree(node->left, depth + 1);
        }
    }

    void clear(TreeNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    ListBST() : root(nullptr) {}
    ~ListBST() { clear(root); }

    void insert(int key, int value) {
        TreeNode* newNode = new TreeNode(key, value);
        if (root == nullptr) {                              //if list is empty
            root = newNode;
            return;
        }

        TreeNode* current = root;
        TreeNode* parent = nullptr;
        while (current != nullptr) {                        //looking for place
            parent = current;
            if (key < current->data.key) {                  //if key is less than node go to left
                current = current->left;
            }
            else {
                current = current->right;                   //if key is bigger than node go to right
            }
        }

        newNode->parent = parent;                    
        if (key < parent->data.key) {                        //insert node
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }

    int find(int key) {
        TreeNode* current = root;
        while (current != nullptr) {                        //looking for node
            if (key == current->data.key) {
                return current->data.value;
            }
            else if (key < current->data.key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return -1;                                          //element not found
    }

    void remove(int key) {
        TreeNode* current = root;
        while (current != nullptr) {                        //looking for node
            if (key == current->data.key) {
                removeNode(current);
                return;
            }
            else if (key < current->data.key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
    }

    TreeNode* getRoot() const {
        return root;                                        //get pointer to first (top) element in list
    }

    void printTable() {
        printTree(root, 0);
    }
    
};

