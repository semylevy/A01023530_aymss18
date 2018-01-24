#include <iostream>

using namespace std;

class Product {
public:
    virtual void operacion1() = 0;
    virtual void operacion2() = 0;
};

class Producto1 : public Product{
public:
    void operacion1() {
        cout << "Estoy en operación 1, prod 1\n";
    }
    void operacion2() {
        cout << "Estoy en operación 2, prod 1\n";
    }
};

class Producto2 : public Product {
public:
    void operacion1() {
        cout << "Estoy en operación 1, prod 2\n";
    }
    void operacion2() {
        cout << "Estoy en operación 2, prod 2\n";
    }
};

class Creator {
public:
    virtual Product* factoryMethod(int) = 0;
    Product* createProduct(int tipo) {
        Product* myProduct = factoryMethod(tipo);
        myProduct->operacion1();
        myProduct->operacion2();
        return myProduct;
    }
};

class ConcreteCreator : public Creator {
public:
    Product* factoryMethod(int tipo) {
        if(tipo == 1)
            return new Producto1;
        if(tipo == 2)
            return new Producto2;
        else
            return NULL;
    }
};

int main() {
    Creator* cliente = new ConcreteCreator();
    Product* miProducto = cliente->createProduct(1);
    
    return 1;
}
