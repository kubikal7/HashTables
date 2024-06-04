#pragma once

class KeyValuePair {
public:
    int key;
    int value;

    KeyValuePair() : key(0), value(0) {}
    KeyValuePair(int k, int v) : key(k), value(v) {}
};
