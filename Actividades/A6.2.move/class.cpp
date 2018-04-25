#include <iostream>
using namespace std;

class Foo {
public:
    int* pointer;
    // Both default and parameter constructor
    explicit Foo(int i=10) : pointer(new int(i)) {
        cout << "const def/para\n";
    }
    // Copy constructor
    Foo(const Foo& original) {
        pointer = new int(*(original.pointer));
        cout << "copy const\n";
    }
    // Move constructor
    Foo(Foo&& temporal) {
        swap(pointer, temporal.pointer);
        temporal.pointer = nullptr;
        cout << "move const\n";
    }
    ~Foo() {
        delete pointer;
        cout << "destr\n";
    }
};

Foo devuelveFoo(Foo a) {
    return a;
}

int main() {
    Foo a;
    Foo b(a);
    Foo c(devuelveFoo(a));
    cout << *(a.pointer) << endl;
    return 0;
}