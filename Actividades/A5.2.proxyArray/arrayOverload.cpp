#include <iostream>
#include <stdexcept>

using namespace std;

class positiveIntArray;

// Recibe el objeto de array, modifica su funcionamiento
class Proxy {
    positiveIntArray* array;
    int idx;
public:
    Proxy(positiveIntArray* array, int idx) {
        this->array = array;
        this->idx = idx;
    }
    void operator= (int value);
};

class positiveIntArray {
private:
    int *array;
    int size;
public:
    positiveIntArray() {
        size = 100;
        array = new int[size];
    }

    // envuelves el resultado en una clase, para hacer overload de =
    Proxy operator[] (int idx) {
        if(idx < 0) {
            cout << "Negative index not allowed\n";
            throw invalid_argument("Received negative index value");
        }
        return Proxy(this, idx);
    }

    // permite editar la variable devuelta
    int& setGet(int idx) {
        return array[idx];
    }
};

void Proxy::operator= (int value) {
    if (value < 0) {
        cout << "Negative numbers not allowed\n";
        throw invalid_argument("Received negative value");
    } else {
        // array[idx] = value; No puedes hacer esto porque se cicla con si mismo
        array->setGet(idx) = value;
    }
}

int main() {
    positiveIntArray a;
    a[1] = 5;
    cout << a.setGet(1);
    return 1;
}