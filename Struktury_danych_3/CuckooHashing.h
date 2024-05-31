#pragma once
#include <iostream>
#include "ArrayList.h"
#include "KeyValuePair.h"

using namespace std;

class CuckooHash {
private:
    ArrayList<KeyValuePair>* tab1;
    ArrayList<KeyValuePair>* tab2;
    int currSize = 100;
    int numEle = 0;
    float loadThresh = 0.5;

    void rehash() {
        int oldSize = currSize;
        currSize *= 2;
        ArrayList<KeyValuePair>* newTab1 = new ArrayList<KeyValuePair>[currSize];
        ArrayList<KeyValuePair>* newTab2 = new ArrayList<KeyValuePair>[currSize];

        for (int i = 0; i < oldSize; i++) {
            int size1 = tab1[i].getSize();
            for (int j = 0; j < size1; j++) {
                KeyValuePair pair = tab1[i].getElement(j);
                insertNew(newTab1, newTab2, pair.key, pair.value);
            }

            int size2 = tab2[i].getSize();
            for (int j = 0; j < size2; j++) {
                KeyValuePair pair = tab2[i].getElement(j);
                insertNew(newTab1, newTab2, pair.key, pair.value);
            }
        }

        delete[] tab1;
        delete[] tab2;
        tab1 = newTab1;
        tab2 = newTab2;
    }

    int hash1(int key) {
        return key % currSize;
    }

    int hash2(int key) {
        return (key / currSize) % currSize;
    }

    void insertNew(ArrayList<KeyValuePair>* newTab1, ArrayList<KeyValuePair>* newTab2, int key, int value) {
        int x1 = hash1(key);
        if (newTab1[x1].getSize() == 0) {
            newTab1[x1].push_back({ key, value });
        }
        else {
            KeyValuePair displaced = newTab1[x1].getElement(0);
            newTab1[x1].deleteElement(0);
            newTab1[x1].push_back({ key, value });
            insertNew(newTab2, newTab1, displaced.key, displaced.value);
        }
    }

public:
    CuckooHash() {
        tab1 = new ArrayList<KeyValuePair>[currSize];
        tab2 = new ArrayList<KeyValuePair>[currSize];
    }

    ~CuckooHash() {
        delete[] tab1;
        delete[] tab2;
    }

    void insert(int key, int value) {
        float loadFactor = static_cast<float>(numEle) / currSize;
        if (loadFactor > loadThresh) {
            rehash();
        }

        int x1 = hash1(key);
        if (tab1[x1].getSize() == 0) {
            tab1[x1].push_back({ key, value });
        }
        else {
            KeyValuePair displaced = tab1[x1].getElement(0);
            tab1[x1].deleteElement(0);
            tab1[x1].push_back({ key, value });

            int x2 = hash2(displaced.key);
            if (tab2[x2].getSize() == 0) {
                tab2[x2].push_back(displaced);
            }
            else {
                KeyValuePair displaced2 = tab2[x2].getElement(0);
                tab2[x2].deleteElement(0);
                tab2[x2].push_back(displaced);
                insertNew(tab1, tab2, displaced2.key, displaced2.value);
            }
        }

        numEle++;
    }

    int find(int key) {
        int x1 = hash1(key);
        if (tab1[x1].getSize() != 0 && tab1[x1].getElement(0).key == key) {
            return tab1[x1].getElement(0).value;
        }

        int x2 = hash2(key);
        if (tab2[x2].getSize() != 0 && tab2[x2].getElement(0).key == key) {
            return tab2[x2].getElement(0).value;
        }

        return -1;
    }

    void remove(int key) {
        int x1 = hash1(key);
        if (tab1[x1].getSize() != 0 && tab1[x1].getElement(0).key == key) {
            tab1[x1].deleteElement(0);
            numEle--;
            return;
        }

        int x2 = hash2(key);
        if (tab2[x2].getSize() != 0 && tab2[x2].getElement(0).key == key) {
            tab2[x2].deleteElement(0);
            numEle--;
            return;
        }
    }

    void printTab() {
        cout << "Table 1:" << endl;
        for (int i = 0; i < currSize; ++i) {
            int size = tab1[i].getSize();
            cout << "Bucket " << i << ": ";
            for (int j = 0; j < size; j++) {
                KeyValuePair pair = tab1[i].getElement(j);
                cout << "(" << pair.key << ", " << pair.value << ") -> ";
            }
            cout << "NULL" << endl;
        }

        cout << "Table 2:" << endl;
        for (int i = 0; i < currSize; ++i) {
            int size = tab2[i].getSize();
            cout << "Bucket " << i << ": ";
            for (int j = 0; j < size; j++) {
                KeyValuePair pair = tab2[i].getElement(j);
                cout << "(" << pair.key << ", " << pair.value << ") -> ";
            }
            cout << "NULL" << endl;
        }
    }
};

