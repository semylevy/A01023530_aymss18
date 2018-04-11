#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class IVisitor;
class Videojuego;

class Observer {
public:
    virtual void update(Videojuego*) = 0;
};

class Videojuego {
public:
    virtual Videojuego* clone() = 0;
    virtual void accept(IVisitor*) = 0;
    virtual void print() = 0;

    void concepcion() {cout << "Concepción\n";}
    void diseno() {cout << "Diseño\n";}
    void planificacion() {cout << "Planificación\n";}
    void produccion() {cout << "Producción\n";}
    void pruebasAceptacion() {cout << "Pruebas de aceptación\n";}

    void setPrecio(float precio_in) {
        precio = precio_in;
    }
    float getPrecio() {
        return precio;
    }

    float precio;
    int serie;
    string nombre;

    Videojuego() {}
    
    void setValues(int serie_in, float precio_in, string nombre_in) {
        serie = serie_in;
        precio = precio_in;
        nombre = nombre_in;
    }

    void attach(Observer* o) {
        observers.push_back(o);
    }
    void dettach(Observer* o) {
        for(int i = 0; i < observers.size(); i++) {
            if(observers[i] == o) {
                observers.erase(observers.begin()+i);
                return;
            }
        }
    }
    void notifyAll(Videojuego* s) {
        for(int i = 0; i < observers.size(); i++) {
            observers[i]->update(s);
        }
    }
    bool operator > (const Videojuego& cmp) const {
        return (precio > cmp.precio);
    }
    bool operator < (const Videojuego& cmp) const {
        return (precio < cmp.precio);
    }

private:
    vector<Observer*> observers;
};

template <class Base, class Subclass>
class CloneCRTP : public Base {
public:
    Base* clone() {
        return new Subclass(dynamic_cast<Subclass&>(*this));
    }
};

class Estrategia : public CloneCRTP<Videojuego, Estrategia> {
public:
    // Default constructor
    Estrategia() {};
    // Argument constructor
    Estrategia(int in_atr, int serie, float precio, string nombre) : in_atr(in_atr) {
        Videojuego::setValues(serie, precio, nombre);
    }
    // Copy constructor
    Estrategia(const Estrategia& t) {
        serie = t.serie;
        precio = t.precio;
        nombre = t.nombre;
    }
    // Print all parameters
    void print() {
        cout << "Atr 1: " << in_atr << ", num serie: " << serie << " precio: " << precio << " nombre: " << nombre << "\n";
    }
    void accept(IVisitor* visitor);
    void notificar() {
        notifyAll(this);
    }
private:
    int in_atr;
};

class Aventura : public CloneCRTP<Videojuego, Aventura>{
public:
    // Default Constructor
    Aventura() {};
    // Argument Constructor
    Aventura(int in_atr, int serie, float precio, string nombre) : in_atr(in_atr) {
        Videojuego::setValues(serie, precio, nombre);
    }
    // Copy Constructor
    Aventura(const Aventura& t) {
        serie = t.serie;
        precio = t.precio;
        nombre = t.nombre;
    }
    // Print all parameters
    void print() {
    cout << "Atr 1: " << in_atr << ", num serie: " << serie << " precio: " << precio << " nombre: " << nombre << "\n";    }
    void accept(IVisitor* visitor);
    void notificar() {
        notifyAll(this);
    }
private:
    int in_atr;
};

class Aprendizaje : public CloneCRTP<Videojuego, Aprendizaje> {
public:
    // Default Constructor
    Aprendizaje() {};
    // Argument Constructor
    Aprendizaje(int in_atr, int serie, float precio, string nombre) : in_atr(in_atr) {
        Videojuego::setValues(serie, precio, nombre);
    }
    // Copy Constructor
    Aprendizaje(const Aprendizaje& t) {
        serie = t.serie;
        precio = t.precio;
        nombre = t.nombre;
    }
    // Print all parameters
    void print() {
        cout << "Atr 1: " << in_atr << ", num serie: " << serie << " precio: " << precio << " nombre: " << nombre << "\n";
    }
    void accept(IVisitor* visitor);
    void notificar() {
        notifyAll(this);
    }
private:
    int in_atr;
};

// Factory method
class Creator {
private:
    static Creator* instance;
    template <class Tipo>
    Tipo* factoryMethod(int in_atr, int serie, float precio, string nombre) {
        return new Tipo(in_atr, serie, precio, nombre);
    }
    Creator() {}
    ~Creator() {}
public:
    template <class Tipo>
    Tipo* crearVideojuego(int in_atr, int serie, float precio, string nombre) {
        Tipo* videojuego = factoryMethod<Tipo>(in_atr, serie, precio, nombre);
        cout << videojuego->nombre << endl;
        videojuego->concepcion();
        videojuego->diseno();
        videojuego->planificacion();
        videojuego->produccion();
        videojuego->pruebasAceptacion();
        return videojuego;
    }
    // Singleton implementation
    static Creator* getInstance() {
        if(instance == NULL) {
            instance = new Creator;
        }
        return instance;
    }
    static bool deleteInstance() {
        if(instance != NULL) {
            delete instance;
            return true;
        }
        return false;
    }
};

class IVisitor {
public:
    virtual void visit(Estrategia*) = 0;
    virtual void visit(Aventura*) = 0;
    virtual void visit(Aprendizaje*) = 0;
};

class AumentarVisitor : public IVisitor {
public:
    void visit(Estrategia* h) {
        h->setPrecio(h->getPrecio() * 1.15);
    }
    void visit(Aventura* h) {
        h->setPrecio(h->getPrecio() * 1.15);
    }
    void visit(Aprendizaje* h) {
        h->setPrecio(h->getPrecio() * 1.15);
    }
};

class DisminuirVisitor : public IVisitor {
public:
    void visit(Estrategia* h) {
        h->setPrecio(h->getPrecio() * 0.85);
    }
    void visit(Aventura* h) {
        h->setPrecio(h->getPrecio() * 0.85);
    }
    void visit(Aprendizaje* h) {
        h->setPrecio(h->getPrecio() * 0.85);
    }
};

class Almacen {
private:
    static Almacen* instance;
    vector<Videojuego*> inventario;
    Almacen() {}
    ~Almacen() {}
public:
    void operacionPrecios(bool increment) {
        if(increment) {
            accept(new AumentarVisitor);
        } else {
            accept(new DisminuirVisitor);
        }
    }
    void accept(IVisitor* visitor) {
        for (int i = 0; i < inventario.size(); i++) {
            inventario[i]->accept(visitor);
        }
    }
    void agregarJuego(Videojuego* nuevo) {
        inventario.push_back(nuevo);
        nuevo->notifyAll(nuevo);
    }
    bool eliminarJuegoNombre(string nombre) {
        for(int i = 0; i < inventario.size(); i++) {
            if(inventario[i]->nombre == nombre) {
                inventario.erase(inventario.begin() + i);
                return true;
            }
        }
        return false;
    }
    bool eliminarJuegoSerie(int serie) {
        for(int i = 0; i < inventario.size(); i++) {
            if(inventario[i]->serie == serie) {
                inventario.erase(inventario.begin() + i);
                return true;
            }
        }
        return false;
    }
    void deshacer() {

    }
    void ordenarInventario(bool ascendiente) {
        if(ascendiente) {
            sort(inventario.begin(), inventario.end());
        } else {
            sort(inventario.begin(), inventario.end(),greater<Videojuego*>());
        }
    }
    Videojuego* buscarJuegoNombre(string nombre) {
        for(int i = 0; i < inventario.size(); i++) {
            if(inventario[i]->nombre == nombre) {
                return inventario[i];
            }
        }
        return NULL;
    }
    Videojuego* buscarJuegoSerie(int serie) {
        for(int i = 0; i < inventario.size(); i++) {
            if(inventario[i]->serie == serie) {
                return inventario[i];
            }
        }
        return NULL;
    }
    int getNumeroDeJuegos() {
        return inventario.size();
    }
    void imprimirInventario() {
        for(int i = 0; i < inventario.size(); i++) {
            inventario[i]->print();
        }
    }
    // Singleton implementation
    static Almacen* getInstance() {
        if(instance == NULL) {
            instance = new Almacen;
        }
        return instance;
    }
    static bool deleteInstance() {
        if(instance != NULL) {
            delete instance;
            return true;
        }
        return false;
    }
};

void Estrategia::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void Aventura::accept(IVisitor* visitor) {
    visitor->visit(this);
}

void Aprendizaje::accept(IVisitor* visitor) {
    visitor->visit(this);
}

class Publico : public Observer {
public:
    void update(Videojuego* s) {
        cout << "Escuchamos acerca de " << s->nombre << ", y estamos tan felices!\n";
    }
};

Creator* Creator::instance = NULL;
Almacen* Almacen::instance = NULL;

int main() {
    Creator* creador = Creator::getInstance();
    Almacen* almacen = Almacen::getInstance();

    Publico* publico = new Publico;

    Videojuego *t1 = creador->crearVideojuego<Estrategia>(1,1,1,"test");
    Videojuego *s1 = creador->crearVideojuego<Aventura>(1,1,1,"test");
    Videojuego *w1 = creador->crearVideojuego<Aprendizaje>(1,1,1,"test");
    
    Videojuego *t2 = t1->clone();
    Videojuego *s2 = s1->clone();
    Videojuego *w2 = w1->clone();

    almacen->agregarJuego(t1);
    almacen->agregarJuego(s1);
    almacen->agregarJuego(w1);
    almacen->agregarJuego(t2);
    almacen->agregarJuego(s2);
    almacen->agregarJuego(w2);

    almacen->operacionPrecios(true);
    almacen->ordenarInventario(false);
    almacen->imprimirInventario();
    
    return 1;
}
