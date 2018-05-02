#include <iostream>

using namespace std;

template <class T>
class Collection;

template <class T>
class Iterator {
protected:
    Collection<T>* collection;
    int count;
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

template <class T>
class Collection {
public:
    virtual void add(T element) = 0;
    virtual T at(int position) = 0;
    virtual Iterator<T>* getIterator() = 0;
    virtual int getNumElements() = 0;
};

template <class T>
class Array;

template <class T>
class ArrayIterator : public Iterator<T> {
public:
    ArrayIterator(Array<T>* array) {
        this->collection = (Collection<T>*)array;
        this->count = 0;
    }
    T next() {
        return this->collection->at(this->count++);
    }
    bool hasNext(){
        if( this->count >= this->collection->getNumElements()) {
            return false;
        }
        return true;
    }
};

template <class T>
class Array : public Collection<T> {
protected:
    T* array;
    int size;
    int numElems;
public:
    Array() {
        size = 10;
        array = new T[size];
        numElems = 0;
    }
    void add(T element) {
        if(numElems >= size) {
            cout << "No more space" << endl;
            return;
        }
        array[numElems++] = element;
    }
    T at(int position) {
        if(size <= position < 0) {
            cout << "index not valid" << endl;
            throw "out_of_range";
        }
        return array[position];
    }
    Iterator<T>* getIterator() {
        return new ArrayIterator<T>(this);
    }
    int getNumElements() {
        return numElems;
    }
};


int main(int argc, char const *argv[]) {
    Collection<float>* c = new Array<float>;
    c->add(7.2);
    c->add(50.15);
    c->add(1);
    c->add(7.2);
    c->add(50.15);
    c->add(1);
    c->add(7.2);
    c->add(50.15);
    c->add(1);
    c->add(7.2);
    c->add(50.15);
    c->add(1);
    
    Iterator<float>* i = c->getIterator();
    while( i->hasNext() ) {
        cout << i->next() << " ";
    }
    cout << endl;
    return 0;
}
