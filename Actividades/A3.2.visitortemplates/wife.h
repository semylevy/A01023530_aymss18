#include <string>

#ifndef WIFE_H
#define WIFE_H

using namespace std;

class Husband;

class Wife {
public:
    Husband* h;
    string name;
    void whoami();
};

#endif
