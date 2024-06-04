#include <iostream>
#include <chrono>
#include "SeparateChaining.h"
#include "CuckooHashing.h"
#include "ListBST.h"
#include "HashBST.h"
#include "Scanner.h"
using namespace std;

int main()
{
    Hash* hashTable=nullptr;
    Scanner scanner;

    /*const int numIterations = 100;
    double totalExecutionTime = 0.0;
    int number = 50000;
    

    for (int i = 0; i < numIterations/4; i++) {
        hashTable = new CuckooHash();

        scanner.readNumbers("liczby1.txt", hashTable, number);

        hashTable->insert(24, 10);

        auto start = chrono::high_resolution_clock::now();                          //tests

        hashTable->remove(24);

        auto end = chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> elapsed = end - start;
        totalExecutionTime += elapsed.count();

        delete hashTable;
    }

    for (int i = 0; i < numIterations / 4; i++) {
        hashTable = new CuckooHash();

        scanner.readNumbers("liczby2.txt", hashTable, number);

        auto start = chrono::high_resolution_clock::now();                          //tests

        hashTable->insert(24, 10);

        auto end = chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> elapsed = end - start;
        totalExecutionTime += elapsed.count();

        delete hashTable;
    }

    for (int i = 0; i < numIterations / 4; i++) {
        hashTable = new CuckooHash();

        scanner.readNumbers("liczby3.txt", hashTable, number);

        auto start = chrono::high_resolution_clock::now();                          //tests

        hashTable->insert(24, 10);

        auto end = chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> elapsed = end - start;
        totalExecutionTime += elapsed.count();

        delete hashTable;
    }

    for (int i = 0; i < numIterations / 4; i++) {
        hashTable = new CuckooHash();

        scanner.readNumbers("liczby4.txt", hashTable, number);

        auto start = chrono::high_resolution_clock::now();                          //tests

        hashTable->insert(24, 10);

        auto end = chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> elapsed = end - start;
        totalExecutionTime += elapsed.count();

        delete hashTable;
    }

    double averageExecutionTime = totalExecutionTime / numIterations;
    cout << "Średni czas wykonania push_back: " << averageExecutionTime << " mikrosekund." << endl;*/
    
    int structure_type;
    int load_size;
    int action;
    int quit = false;

    while (!quit) {
        cout << "Which structure would you like choose?" << endl;
        cout << "1. Separate Chaining" << endl << "2. BST List" << endl<<"3. Cuckoo Hashing" << endl;
        cout << "Choose: ";
        cin >> structure_type;

        if (structure_type == 1)
            hashTable = new SeparateChaining();                  //creating separate chaining object at hash table pointer
        else if (structure_type == 2)
            hashTable = new ListBST();                                    //creating list with BST object at hash table pointer
        else if (structure_type == 3)
            hashTable = new CuckooHash();                           //creating Hash Table with Cuckoo Hashing method 


        if (hashTable != nullptr) {

            cout << endl;

            cout << "How many elements would you like generate in Queue?: ";
            cin >> load_size;

            scanner.readNumbers("liczby1.txt", hashTable, load_size);                                                   //read numbers from file

            cout << endl;

            while (!quit) {
                cout << "Wchis action would you like choose?" << endl;
                cout << "1. Insert element" << endl << "2. Remove element" << endl << "3. Find element" << endl<<"4. Print table" << endl;
                cout << "5. Change structure" << endl << "6. Reset queue" << endl << "7. Quit program" << endl;
                cout << "Choose: ";
                cin >> action;
                if (action == 1) {
                    int key, value;
                    cout << "Enter a key of element: ";
                    cin >> key;
                    cout << endl << "Enter a value of element: ";
                    cin >> value;
                    auto start = chrono::high_resolution_clock::now();                                  //timer
                    hashTable->insert(key, value);                                                      //adding element to table
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, std::micro> elapsed = end - start;
                    cout << "Operation time: " << elapsed.count() << " microseconds" << endl;
                }
                else if (action == 2) {
                    int key;
                    cout << "Enter a key of element: ";
                    cin >> key;
                    auto start = chrono::high_resolution_clock::now();                                  //timer
                    hashTable->remove(key);                                                             //remove element
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, std::micro> elapsed = end - start;
                    cout << "Operation time: " << elapsed.count() << " microseconds" << endl;
                }
                else if (action == 3) {
                    int key;
                    cout << "Enter a key of element: ";
                    cin >> key;
                    auto start = chrono::high_resolution_clock::now();                                  //timer
                    hashTable->find(key);                                                               //find element without remove
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, std::micro> elapsed = end - start;
                    cout << "Operation time: " << elapsed.count() << " microseconds" << endl;
                }
                else if (action == 4) {
                    auto start = chrono::high_resolution_clock::now();                                  //timer
                    hashTable->printTable();                                                            //print table
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double, std::micro> elapsed = end - start;
                    cout << "Operation time: " << elapsed.count() << " microseconds" << endl;
                }
                else if (action == 5) {
                    delete hashTable;                                                                    //deleting table and return to first step in menu
                    break;
                }
                else if (action == 6) {
                    delete hashTable;
                    if (structure_type == 1)
                        hashTable = new SeparateChaining();                                             //creating separate chaining object at hash table pointer 
                    else if (structure_type == 2)
                        hashTable = new ListBST();                                                      //creating list with BST object at hash table pointer
                    else if (structure_type == 3)
                        hashTable = new CuckooHash();                                                   //creating Hash Table with Cuckoo Hashing method 

                    scanner.readNumbers("liczby1.txt", hashTable, load_size);

                    cout << "Queue reseted" << endl;
                }
                else if (action == 7) {
                    quit = true;
                }

                cout << endl;
            }
            cout << endl;
        }
    }
    delete hashTable;
    
    return 0;
}

