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
        currentSize *= 2; // Nowy rozmiar jest podwójny
        ListBST* newTable = new ListBST[currentSize];

        for (int i = 0; i < oldSize; i++) {
            rehashTree(newTable, table[i].getRoot());
        }

        delete[] table;
        table = newTable;
    }

    // Pomocnicza metoda do przechodzenia przez BST i ponownego hashowania
    void rehashTree(ListBST* newTable, TreeNode* node) {
        if (node == nullptr) return;

        // Oblicz nowy indeks w nowej tablicy
        int newIndex = hash(node->data.key, currentSize);

        // Wstaw dane w nowej tablicy
        newTable[newIndex].insert(node->data.key, node->data.value);

        // Rekurencyjne przechodzenie przez lewe i prawe poddrzewo
        rehashTree(newTable, node->left);
        rehashTree(newTable, node->right);
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
        if (currentLoadFactor > loadFactorThreshold) {
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
            table[i].printTree();
            std::cout << "NULL" << std::endl;
        }
    }

    int getNumElements() {
        return numElements;
    }
};

