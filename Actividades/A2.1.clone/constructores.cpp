#include <iostream>

using namespace std;

class Prueba {
public:
    int *value;
    int value2;
    Prueba() {
        cout << "Default constructor\n";
    }
    Prueba(int val): value(new int(val)), value2(val) {
        cout << "Parameter constructor\n";
    }
    Prueba(const Prueba& t) {
        cout << "Copy constructor\n";
        value = new int(*(t.value));
        value2 = t.value2;
    }
    void print() {
        cout << *value << endl;
        cout << value2 << endl;
    }
private:
    
};

int main() {
    Prueba *p = new Prueba(2);
    Prueba w = *p;
    w.value2 = 10;
    w.print();
    p->print();
    return 1;
}
