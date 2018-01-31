#include <iostream>

using namespace std;

template <class T>
T suma(T a, T b) {
    return a+b;
}

template <class T>
T resta(T a, T b) {
    return a-b;
}

template <class T>
T duplica(T a) {
    return a*2;
}

template <class T, class Function>
T doTemplateFunction(T a, T b, Function f) {
    return f(a, b);
}

// Muy genérico, puede recibir o devolver lo que quiera
template <class Function>
Function getTemplateFunction(char o) {
    if(o == 's') return suma;
    if(o == 'r') return resta;
    //if(o == 'd') return duplica;
    return NULL;
}

int main() {
    cout << doTemplateFunction(2,2,suma<int>) << endl;
    cout << getTemplateFunction<int (*)(int,int)>('s')(1,5) << endl;
    //cout << getTemplateFunction<int (*)(int)>('d')(4) << endl;
    return 1;
}
