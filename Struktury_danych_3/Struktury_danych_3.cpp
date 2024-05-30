#include <iostream>
#include "SeparateChaining.h"

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

    return 0;
}

