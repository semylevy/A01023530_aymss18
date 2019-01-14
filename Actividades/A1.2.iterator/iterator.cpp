#include <iostream>

using namespace std;

class IntCollection;

class Iterator {
protected:
    IntCollection* collection;
    int count;
public:
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

class IntCollection {
public:
    virtual void add(int element) = 0;
    virtual int at(int position) = 0;
    virtual Iterator* getIterator() = 0;
    virtual int getNumElements() = 0;
};

class IntArray;

class ArrayIterator : public Iterator {
public:
    ArrayIterator(IntArray* intArray) {
        collection = (IntCollection*)intArray;
        count = 0;
    }
    int next() {
        return collection->at(count++);
    }
    bool hasNext(){
        if( count >= collection->getNumElements()) {
            return false;
        }
        return true;
    }
};

class IntArray : public IntCollection {
protected:
    int* array;
    int size;
    int numElems;
public:
    IntArray() {
        size = 10;
        array = new int[size];
        numElems = 0;
    }
    void add(int element) {
        if(numElems >= size) {
            cout << "No more space" << endl;
            return;
        }
        array[numElems++] = element;
    }
    int at(int position) {
        if(size <= position < 0) {
            cout << "index not valid" << endl;
            throw "out_of_range";
        }
        return array[position];
    }
    Iterator* getIterator() {
        return new ArrayIterator(this);
    }
    int getNumElements() {
        return numElems;
    }
};


int main(int argc, char const *argv[]) {
    IntCollection* c = new IntArray;
    c->add(2);
    c->add(3);
    c->add(14);
    c->add(2);
    
    Iterator* i = c->getIterator();
    while( i->hasNext() ) {
        cout << i->next() << " ";
    }
    cout << endl;
    return 0;
}
