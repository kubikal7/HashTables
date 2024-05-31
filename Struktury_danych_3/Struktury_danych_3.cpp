#include <iostream>
#include "SeparateChaining.h"
#include "CuckooHashing.h"
using namespace std;

int main()
{
    SeparateChaining ht;
    for (int i = 0;i < 72;i++) {
        ht.insert(i, i + 100);
    }

    ht.printTable();
    cout << ht.find(103) << endl;
    /*std::cout << "Value for key 2: " << ht.find(2) << std::endl;
    std::cout << "Value for key 4: " << ht.find(4) << std::endl;

    ht.remove(2);

    std::cout << "Table after deletion:" << std::endl;
    ht.printTable();*/

    CuckooHash ht1;
    for (int i = 0; i < 72; i++) {
        ht1.insert(i, i + 100);
    }

    ht1.printTab();
    cout << ht1.find(10) << endl;
    ht1.printTab();
    cout << "Value for key 2: " << ht1.find(2) << endl;
    cout << "Value for key 4: " << ht1.find(4) << endl;

    ht1.remove(2);
    ht1.insert(10, 100);

    cout << "Table after deletion:" << endl;
    cout << ht1.find(10) << endl;

    ht1.printTab();
    return 0;
}

