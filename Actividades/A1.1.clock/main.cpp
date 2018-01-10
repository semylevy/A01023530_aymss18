#include <iostream>
#include "hora.h"

int main() {
    Clock* instance = Clock::getInstance();
    cout << instance->getTime();
    Clock* instance2 = Clock::getInstance();
    cout << instance2->getTime();
    cout << instance << endl << instance2 << endl;
    delete instance;
    return 0;
}
