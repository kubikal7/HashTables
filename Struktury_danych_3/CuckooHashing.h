#pragma once
#include <iostream>
#include "KeyValuePair.h"
#include "Hash.h"

using namespace std;

struct Element {
    KeyValuePair keyValue;
    bool empty = true;
};

class CuckooHash : public Hash{
private:
    Element* tab1;
    Element* tab2;
    Element* tab3;
    int currSize = 10000;
    int numEle = 0;
    float loadThresh = 0.7;
    int test = 0;

    void fill(Element* tab, int size) {
        for (int i = 0; i < size; i++) {
            tab[i].empty = true;                                                //switch all places to empty
        }
    }

    void rehash(int oldSize, int futureSize) {
        //cout << "Zaczynam powiekszac" << endl;
        currSize = futureSize;
        Element* newTab1 = new Element[currSize];
        Element* newTab2 = new Element[currSize];
        Element* newTab3 = new Element[currSize];
        fill(newTab1, currSize);
        fill(newTab2, currSize);
        fill(newTab3, currSize);

        for (int i = 0; i < oldSize; i++) {
            //cout << "Sprawdzam indeks: " << i << endl;
            if (!tab1[i].empty) {
                //cout << "Znalazlem niepusty kubelek w tab1 wiec szukam dla niego nowego miejsca" << endl;
                if (!insertNewRehash(newTab1, newTab2, newTab3, tab1[i].keyValue.key, tab1[i].keyValue.value, 0)) {                 //if there is no space for element rehash with more space
                    delete[] newTab1;
                    delete[] newTab2;
                    delete[] newTab3;
                    rehash(oldSize, currSize * 2);
                    return;
                }
            }

            if (!tab2[i].empty) {
                //cout << "Znalazlem niepusty kubelek w tab2 wiec szukam dla niego nowego miejsca" << endl;
                if (!insertNewRehash(newTab1, newTab2, newTab3, tab2[i].keyValue.key, tab2[i].keyValue.value, 0)) {                 //if there is no space for element rehash with more space
                    delete[] newTab1;
                    delete[] newTab2;
                    delete[] newTab3;
                    rehash(oldSize, currSize * 2);
                    return;
                }
            }

            if (!tab3[i].empty) {
                //cout << "Znalazlem niepusty kubelek w tab3 wiec szukam dla niego nowego miejsca" << endl;
                if (!insertNewRehash(newTab1, newTab2, newTab3, tab3[i].keyValue.key, tab3[i].keyValue.value, 0)) {                 //if there is no space for element rehash with more space  
                    delete[] newTab1;
                    delete[] newTab2;
                    delete[] newTab3;
                    rehash(oldSize, currSize * 2);
                    return;
                }
            }
        }

        delete[] tab1;
        delete[] tab2;
        delete[] tab3;
        tab1 = newTab1;
        tab2 = newTab2;
        tab3 = newTab3;
    }

    int hash1(int key) {                                                                        //hash function
        return key % currSize;
    }

    int hash2(int key) {                                                                        //hash function
        return (key * 500) % currSize;
    }

    int hash3(int key) {                                                                        //hash function
        return (key + 100000) % currSize;
    }

    void insertNew(Element* newTab1, Element* newTab2, Element* newTab3, int key, int value, int depth) {
        if (depth > 16) { // Ograniczenie g³êbokoœci rekursji
            //cout << "Musze poszerzyæ" << endl;
            rehash(currSize, currSize * 2);                                                     //if there is no space for element rehash tables
            //cout << "Poszerzylem i teraz bede wstawiac" << endl;
            insertNew(tab1, tab2, tab3, key, value, 0);
            //cout << "Wstawilem i teraz wychodze z funkcji insertNew" << endl;
            return;
        }

        int x1 = hash1(key);
        //cout << test++ << " Depth: " << depth << ", Key: " << key << ", Value: " << value << ", x1: " << x1 << ", Current size: " << currSize << " Value in tab 1: " << newTab1[x1].keyValue.key << endl;
        if (newTab1[x1].empty){                                                     //insert in first table without moving element
            newTab1[x1].keyValue = { key, value };
            newTab1[x1].empty = false;
        }
        else {
            KeyValuePair displaced = newTab1[x1].keyValue;                          //insert in first table with moving element
            newTab1[x1].keyValue = { key, value };
            int x2 = hash2(displaced.key);
            if (newTab2[x2].empty) {                                                //insert in second table without moving element
                newTab2[x2].keyValue = displaced;
                newTab2[x2].empty = false;
            }
            else {
                KeyValuePair displaced2 = newTab2[x2].keyValue;                      //insert in second table with moving element
                newTab2[x2].keyValue = displaced;
                int x3 = hash3(displaced2.key);
                if (newTab3[x3].empty) {                                            //insert in third table without moving element
                    newTab3[x3].keyValue = displaced2;
                    newTab3[x3].empty = false;
                }
                else {
                    KeyValuePair displaced3 = newTab3[x3].keyValue;                 //insert in third table with moving element
                    newTab3[x3].keyValue = displaced2;
                    insertNew(newTab1, newTab2, newTab3, displaced3.key, displaced3.value, depth + 1);
                }
            }
        }
    }

    bool insertNewRehash(Element* newTab1, Element* newTab2, Element* newTab3, int key, int value, int depth) {
        if (depth > 16) { // Ograniczenie g³êbokoœci rekursji
            return false;
        }

        int x1 = hash1(key);
        //cout << test++ << " Depth: " << depth << ", Key: " << key << ", Value: " << value << ", x1: " << x1 << ", Current size: " << currSize << " Value in tab 1: " << newTab1[x1].keyValue.key << endl;
        if (newTab1[x1].empty) {                                                        //insert in first table without moving element
            newTab1[x1].keyValue = { key, value };
            newTab1[x1].empty = false;
            return true;
        }
        else {
            KeyValuePair displaced = newTab1[x1].keyValue;                              //insert in first table with moving element
            newTab1[x1].keyValue = { key, value };
            int x2 = hash2(displaced.key);
            if (newTab2[x2].empty) {                                                    //insert in second table without moving element
                newTab2[x2].keyValue = displaced;
                newTab2[x2].empty = false;
                return true;
            }
            else {
                KeyValuePair displaced2 = newTab2[x2].keyValue;                         //insert in second table with moving element
                newTab2[x2].keyValue = displaced;
                int x3 = hash3(displaced2.key);
                if (newTab3[x3].empty) {                                                //insert in third table without moving element
                    newTab3[x3].keyValue = displaced2;
                    newTab3[x3].empty = false;
                    return true;
                }
                else {
                    KeyValuePair displaced3 = newTab3[x3].keyValue;                     //insert in third table with moving element
                    newTab3[x3].keyValue = displaced2;
                    return insertNewRehash(newTab1, newTab2, newTab3, displaced3.key, displaced3.value, depth + 1);
                }
            }
        }
    }

public:
    CuckooHash() {
        tab1 = new Element[currSize];                                                       //creating three tables
        tab2 = new Element[currSize];
        tab3 = new Element[currSize];
        fill(tab1, currSize);
        fill(tab2, currSize);
        fill(tab3, currSize);
    }

    ~CuckooHash() {
        delete[] tab1;
        delete[] tab2;
        delete[] tab3;
    }

    void insert(int key, int value) {
        //cout << "Przyjmuje klucz: " << key << endl;
        float loadFactor = static_cast<float>(numEle) / currSize;
        if (loadFactor > loadThresh) {                                                         //check if load factor is bigger than limit, if yes - increase table
            //cout << "Musze poszerzyæ" << endl;
            rehash(currSize, currSize * 2);
        }

        int x1 = hash1(key);
        if (tab1[x1].empty) {
            //cout << "Umieszczam w pierwszej tablicy bez przestawiania" << endl;
            tab1[x1].keyValue = { key, value };                                                //insert in first table without moving element
            tab1[x1].empty = false;
        }
        else {
            //cout << "Umieszczam w pierwszej tablicy z przestawianiem" << endl;
            KeyValuePair displaced = tab1[x1].keyValue;                                     //insert in first table with moving element
            tab1[x1].keyValue = { key, value };
            int x2 = hash2(displaced.key);
            if (tab2[x2].empty) {
                //cout << "Umieszczam w drugiej tablicy bez przestawiania" << endl; 
                tab2[x2].keyValue = displaced;                                              //insert in second table without moving element
                tab2[x2].empty = false;
            }
            else {
                //cout << "Umieszczam w drugiej tablicy z przestawianiem" << endl;
                KeyValuePair displaced2 = tab2[x2].keyValue;                                 //insert in second table with moving element
                tab2[x2].keyValue = displaced;
                int x3 = hash3(displaced2.key);
                if (tab3[x3].empty) {
                    //cout << "Umieszczam w trzeciej tablicy bez przestawiania" << endl;     
                    tab3[x3].keyValue = displaced2;                                         //insert in third table without moving element
                    tab3[x3].empty = false;
                }
                else {
                    //cout << "Umieszczam w trzeciej tablicy z przestawianiem" << endl;
                    KeyValuePair displaced3 = tab3[x3].keyValue;                            //insert in third table with moving element
                    tab3[x3].keyValue = displaced2;
                    insertNew(tab1, tab2, tab3, displaced3.key, displaced3.value, 0);
                }
            }
        }

        numEle++;
    }

    int find(int key) {
        int x1 = hash1(key);
        if (!tab1[x1].empty && tab1[x1].keyValue.key == key) {                              //looking for element in first table
            return tab1[x1].keyValue.value;
        }

        int x2 = hash2(key);
        if (!tab2[x2].empty && tab2[x2].keyValue.key == key) {                              //looking for element in second table
            return tab2[x2].keyValue.value;
        }

        int x3 = hash3(key);
        if (!tab3[x3].empty && tab3[x3].keyValue.key == key) {                              //looking for element in third table
            return tab3[x3].keyValue.value;
        }

        return -1;                                                                            //key not found
    }

    void remove(int key) {
        int x1 = hash1(key);
        if (!tab1[x1].empty && tab1[x1].keyValue.key == key) {                                //looking for element in first table
            tab1[x1].empty = true;
            numEle--;
            return;
        }

        int x2 = hash2(key);                                                                   //looking for element in second table
        if (!tab2[x2].empty && tab2[x2].keyValue.key == key) {
            tab2[x2].empty = true;
            numEle--;
            return;
        }

        int x3 = hash3(key);
        if (!tab3[x3].empty && tab3[x3].keyValue.key == key) {                                //looking for element in third table
            tab3[x3].empty = true;
            numEle--;
            return;
        }
    }

    void printTable() {
        int x = 0;
        cout << "Table 1:" << endl;
        for (int i = 0; i < currSize; ++i) {
            if (!tab1[i].empty) {
                x++;
                cout << "Bucket " << i << ": ";
                cout << "(" << tab1[i].keyValue.key << ", " << tab1[i].keyValue.value << ") -> ";
                cout << "NULL" << endl;
            }
        }

        cout << "Table 2:" << endl;
        for (int i = 0; i < currSize; ++i) {
            if (!tab2[i].empty) {
                x++;
                cout << "Bucket " << i << ": ";
                cout << "(" << tab2[i].keyValue.key << ", " << tab2[i].keyValue.value << ") -> ";
                cout << "NULL" << endl;
            }
        }

        cout << "Table 3:" << endl;
        for (int i = 0; i < currSize; ++i) {
            if (!tab3[i].empty) {
                x++;
                cout << "Bucket " << i << ": ";
                cout << "(" << tab3[i].keyValue.key << ", " << tab3[i].keyValue.value << ") -> ";
                cout << "NULL" << endl;
            }
        }
        cout << endl << x;
    }
};