#include <iostream>

using namespace std;

class positiveIntArray {
private:
    int *array;
public:
    int& operator[] (int x) {
        if(x < 0) {
            cout << "Negative index not allowed\n";
        }
        return array[x];
    }
};