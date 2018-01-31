#include <iostream>

// Loop de 100, corre en tiempo constante. Todo el procedimiento se corre en compilación.

using namespace std;

template<int n>
class Repeat : public Repeat<n-1> {
public:
    Repeat() {
        cout << n << " ";
    }
};

template<>
class Repeat<0> {
public:
    Repeat() {
    }
};

int main() {
    Repeat<999> r;
    return 1;
}

// Para compilar:
// g++ metaprogramming.cpp -ftemplate-depth=1000
