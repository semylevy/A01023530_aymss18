#include <iostream>
#include "wife.h"
#include "husband.h"

using namespace std;

void Wife::whoami() {
    cout << "I am " << name << ", and my husband is " << h.name << "\n";
}
