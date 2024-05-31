#pragma once
#include <iostream>
#include "KeyValuePair.h"
using namespace std;



template<typename T>
class ArrayList
{
    int size = 0;
    int capacity = 1;
    T* tab = new T[capacity];
public:
    ArrayList() {
    }
    ~ArrayList() {
        delete[] tab;
    }
    //adding elements - if the array reaches its capacity, it's resized to double its size and elements are copied to new array

    void push_back(T element) {                             //method adds a new element to the end of the array 
        if (size == capacity) {
            capacity *= 2;
            T* newTab = new T[capacity];
            for (int i = 0; i < size; i++) {
                newTab[i] = tab[i];
            }
            delete[] tab;
            tab = newTab;
        }

        tab[size] = element;
        size++;
    };

    void push_front(T element) {                            //method adds a new element to the start of the array
        if (size == capacity) {
            capacity *= 2;
            T* newTab = new T[capacity];
            for (int i = 0; i < size; i++) {
                newTab[i] = tab[i];
            }
            delete[] tab;
            tab = newTab;
        }

        for (int i = size; i > 0; i--) {
            tab[i] = tab[i - 1];
        }

        tab[0] = element;
        size++;
    };

    void addElement(T element, int index) {                    //method inserts a new element at a given index
        if (index < 0 || index > size) {
            cout << "Invalid index!" << endl;
            return;
        }

        if (size == capacity) {
            capacity *= 2;
            T* newTab = new T[capacity];
            for (int i = 0; i < size; i++) {
                newTab[i] = tab[i];
            }
            delete[] tab;
            tab = newTab;
        }

        for (int i = size; i > index; i--) {
            tab[i] = tab[i - 1];
        }

        tab[index] = element;
        size++;
    };

    T pop_front() {                                     //delete and return first element in a list
        if (size == 0) {
            cout << "List is empty" << endl;
            return T();                                 //if list is empty returns default T
        }

        T poppedValue = tab[0];
        for (int i = 0; i < size - 1; i++) {
            tab[i] = tab[i + 1];
        }
        size--;

        return poppedValue;
    }

    T pop_back() {                                      //delete and return last element
        if (size == 0) {
            cout << "List is empty" << endl;
            return T();                                 //if list is empty returns default T
        }

        size--;

        return tab[size];                               //returns value of last element
    }

    T deleteElement(int index) {                        //delete and return element at given index
        if (index < 0 || index >= size) {
            cout << "Invalid index!" << endl;
            return T();                                 //if list is empty returns default T
        }

        T deletedElement = tab[index];


        for (int i = index; i < size - 1; i++) {
            tab[i] = tab[i + 1];
        }

        size--;

        return deletedElement;
    }


    T& getElement(int index) {                           //method returns element by index
        return tab[index];
    };

    void expand(T value) {
        int oldCapacity = capacity;
        capacity *= 2;
        T* newTab = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            newTab[i] = value;
        }
        for (int i = 0; i < oldCapacity; i++) {
            newTab[i] = tab[i];
        }
        delete[] tab;
        tab = newTab;
    }

    void fill(T value) {
        for (int i = 0; i < capacity; i++) {
            tab[i] = value;
        }
    }

    int findElement(T element) const {                  //method searches for element and returns its index or -1 if not found
        for (int i = 0; i < size; ++i) {
            if (tab[i] == element) {
                return i;
            }
        }
        return -1;
    };

    int getSize() const {                               //method returns the number of elements
        return size;
    };

    int getCapacity() const {                           //method gives current array capacity
        return capacity;
    }

    bool isEmpty() const {                              //method checks if list is empty
        return size ? true : false;
    };
};
