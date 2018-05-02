#include <iostream>
#include "husband.h"
#include "wife.h"

using namespace std;

void Husband::whoami() {
    cout << "I am " << name << ", and my wife is " << w.name << "\n";
}
