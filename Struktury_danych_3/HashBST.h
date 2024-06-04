#pragma once
#include "ArrayList.h"
#include "ListBST.h"
#include "KeyValuePair.h"
class HashBST
{
private:
    ListBST* table;
    int currentSize = 100;
    int numElements = 0;
    float loadFactorThreshold = 0.7;

    void rehash() {
        int oldSize = currentSize;
        currentSize *= 2;                                                           //new doubled size
        ListBST* newTable = new ListBST[currentSize];

        for (int i = 0; i < oldSize; i++) {
            rehashTree(newTable, table[i].getRoot());
        }

        delete[] table;
        table = newTable;
    }

    void rehashTree(ListBST* newTable, TreeNode* node) {
        if (node == nullptr) return;                                                //if list is empty

        int newIndex = hash(node->data.key, currentSize);                           //calculate new index

        // Wstaw dane w nowej tablicy
        newTable[newIndex].insert(node->data.key, node->data.value);

        rehashTree(newTable, node->left);                                           //going by left side of tree
        rehashTree(newTable, node->right);                                          //going by right side of tree
    }

    int hash(int key, int size) {
        return key % size;
    }

public:
    HashBST() {
        table = new ListBST[currentSize];
    }

    ~HashBST() {
        delete[] table;
    }

    void insert(int key, int value) {
        float currentLoadFactor = static_cast<float>(numElements) / currentSize;
        if (currentLoadFactor > loadFactorThreshold) {                              //if load factor is bigger than 0.7 rehash 
            rehash();
        }
        int index = hash(key, currentSize);
        table[index].insert(key, value);
        numElements++;
    }

    int find(int key) {
        int index = hash(key, currentSize);
        return table[index].find(key);
    }

    void remove(int key) {
        int index = hash(key, currentSize);
        table[index].remove(key);
    }

    void printTable() {
        for (int i = 0; i < currentSize; ++i) {
            std::cout << "Index " << i<<":"<<endl;
            table[i].printTable();
            std::cout << "NULL" << std::endl;
        }
    }

    int getNumElements() {
        return numElements;
    }
};

