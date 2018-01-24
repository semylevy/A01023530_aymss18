#include <iostream>

using namespace std;

class Vehiculo {
public:
    virtual void ensamblaje() = 0;
    virtual void hojalateria() = 0;
    virtual void pintura() = 0;
    virtual void entrega() = 0;
};

class Dodge : public Vehiculo{
public:
    void ensamblaje() {
        cout << "Ensamblando Dodge\n";
    }
    void hojalateria() {
        cout << "Hojalateria Dodge\n";
    }
    void pintura() {
        cout << "Pintando Dodge\n";
    }
    void entrega() {
        cout << "Entregando Dodge\n";
    }
};

class BMW : public Vehiculo {
public:
    void ensamblaje() {
        cout << "Ensamblando BMW\n";
    }
    void hojalateria() {
        cout << "Hojalateria BMW\n";
    }
    void pintura() {
        cout << "Pintando BMW\n";
    }
    void entrega() {
        cout << "Entregando BMW\n";
    }
};

class VV : public Vehiculo {
public:
    void ensamblaje() {
        cout << "Ensamblando VV\n";
    }
    void hojalateria() {
        cout << "Hojalateria VV\n";
    }
    void pintura() {
        cout << "Pintando VV\n";
    }
    void entrega() {
        cout << "Entregando VV\n";
    }
};

class Nissan : public Vehiculo {
public:
    void ensamblaje() {
        cout << "Ensamblando Nissan\n";
    }
    void hojalateria() {
        cout << "Hojalateria Nissan\n";
    }
    void pintura() {
        cout << "Pintando Nissan\n";
    }
    void entrega() {
        cout << "Entregando Nissan\n";
    }
};

class Creator {
private:
    template <class Tipo>
    Tipo* factoryMethod() {
        return new Tipo;
    }
public:
    template <class Tipo>
    Tipo* createVehiculo() {
        Tipo* myVehiculo = factoryMethod<Tipo>();
        myVehiculo->ensamblaje();
        myVehiculo->hojalateria();
        myVehiculo->pintura();
        myVehiculo->entrega();
        return myVehiculo;
    }
};

int main() {
    Creator* cliente = new Creator();
    Vehiculo* v1 = cliente->createVehiculo<Dodge>();
    v1->ensamblaje();
    return 1;
}
