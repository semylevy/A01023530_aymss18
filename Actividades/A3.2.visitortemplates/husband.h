#include <string>

#ifndef HUSBAND_H
#define HUSBAND_H

using namespace std;

class Wife;

class Husband {
public:
    Wife* w;
    string name;
    void whoami();
};

#endif
