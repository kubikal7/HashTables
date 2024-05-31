#pragma once
#include <iostream>
#include <vector>
#include "ArrayList.h"
#include "KeyValuePair.h"

class SeparateChaining {
private:
    

    ArrayList<KeyValuePair>* table;
    int currentSize=100;
    int numElements=0;
    float loadFactorThreshold=0.7;

    void rehash() {
        int oldSize = currentSize;
        currentSize *= 2; // New size is doubled
        ArrayList<KeyValuePair>* newTable = new ArrayList<KeyValuePair>[currentSize];

        for (int i = 0; i < oldSize; i++) {
            int sizeBucket = table[i].getSize();
            for (int j = 0;j < sizeBucket;j++) {
                KeyValuePair pair = table[i].getElement(j);
                int newIndex = hash(pair.key, currentSize);
                newTable[newIndex].push_back(pair);
            }
        }

        delete[] table;
        table = newTable;
    }

    int hash(int key, int size) {
        return key % size;
    }

public:
    SeparateChaining(){
        table = new ArrayList<KeyValuePair>[currentSize];
    }

    ~SeparateChaining() {
        delete[] table;
    }

    void insert(int key, int value) {
        float currentLoadFactor = static_cast<float>(numElements) / currentSize;
        if (currentLoadFactor > loadFactorThreshold) {
            rehash();
        }
        int index = hash(key, currentSize);
        table[index].push_back({ key, value });
        numElements++;
    }

    int find(int key) {
        int index = hash(key, currentSize);
        int sizeBucket = table[index].getSize();
        for (int j = 0;j < sizeBucket;j++) {
            KeyValuePair pair = table[index].getElement(j);
            if (pair.key == key) {
                return pair.value;
            }
        }
        // Return default value if key not found
        return -1;
    }

    void remove(int key) {
        int index = hash(key, currentSize);
        int sizeBucket = table[index].getSize();
        for (int j = 0;j < sizeBucket;j++) {
            KeyValuePair pair = table[index].getElement(j);
            if (pair.key == key) {
                table[index].deleteElement(j);
                numElements--;
                break; // Stop after first occurrence of key
            }
        }
    }



    void printTable() {
        for (int i = 0; i < currentSize; ++i) {
            int sizeBucket = table[i].getSize();
            std::cout << "Bucket " << i << ": ";
            for (int j = 0;j < sizeBucket;j++) {
                KeyValuePair pair = table[i].getElement(j);
                std::cout << "(" << pair.key << ", " << pair.value << ") -> ";
            }
            std::cout << "NULL" << std::endl;
        }
    }
};


