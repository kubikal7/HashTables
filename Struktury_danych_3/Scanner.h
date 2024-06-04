#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Hash.h"

class Scanner {
private:
    std::ifstream file;

public:
    Scanner() {
        
    }

    ~Scanner() {
        if (file.is_open()) {
            file.close();
        }
    }

    void readNumbers(const std::string& filename, Hash* hashTable, int number) {
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file." << std::endl;
        }
        int key, value;
        for (int i = 0; i < number; i++) {
            
            file >> key >> value;
            //std::cout << "key: " << key << " value: " << value << std::endl;
            hashTable->insert(key, value);
        }
        file.close();
    }
};


