#include <iostream>

using namespace std;

int suma(int a, int b){
    return a+b;
}

int resta(int a, int b) {
    return a-b;
}

// Recibe una función como parámetro
int operacion(int a, int b, int(*f)(int, int)) {
    return f(a, b);
}

// Devuelve una función
typedef int(*f)(int, int);

f getOperacion(char o) {
    if(o == 's') return suma;
    if(o == 'r') return resta;
    else return NULL;
}

// Lo mismo, pero más rebuscado
int (*getf(char o))(int a, int b){
    if(o == 's') return suma;
    if(o == 'r') return resta;
    else return NULL;
}

int main() {
    cout << operacion(1,2,resta) << endl;
    cout << getOperacion('s')(2,2) << endl;
    cout << getf('s')(2,4) << endl;
    return 1;
}
