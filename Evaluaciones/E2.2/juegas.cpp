#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <sstream>

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
    static int* serie;

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
    string nombre;

    Videojuego() {}
    
    // Singleton implementation
    static int* getSerie() {
        if(serie == NULL) {
            serie = new int;
            *serie = 0;
        }
        (*serie)++;
        return serie;
    }

    void setValues(float precio_in, string nombre_in) {
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
    Estrategia(string in_atr1, string in_atr2, string in_atr3, float precio, string nombre) : fecha(in_atr1), autor(in_atr2), otro(in_atr3) {
        Videojuego::setValues(precio, nombre);
        serie = *(Videojuego::getSerie());
    }
    // Copy constructor
    Estrategia(const Estrategia& t) {
        precio = t.precio;
        nombre = t.nombre;
        fecha = t.fecha;
        autor = t.autor;
        otro = t.otro;
        serie = *(Videojuego::getSerie());
    }
    // Print all parameters
    void print() {
        cout << "Num serie: " << serie << ", precio: " << precio << ", nombre: " << nombre << ". Estrategia. " << "Atr 1: " << fecha << ", Atr 2: " << autor << ", Atr 3: " << otro << '\n';
    }
    void accept(IVisitor* visitor);
private:
    int serie;
    string fecha, autor, otro;
};

class Aventura : public CloneCRTP<Videojuego, Aventura>{
public:
    // Default Constructor
    Aventura() {};
    // Argument Constructor
    Aventura(string in_atr1, string in_atr2, string in_atr3, float precio, string nombre) : color(in_atr1), comp(in_atr2), otro(in_atr3) {
        Videojuego::setValues(precio, nombre);
        serie = *(Videojuego::getSerie());
    }
    // Copy Constructor
    Aventura(const Aventura& t) {
        precio = t.precio;
        nombre = t.nombre;
        color = t.color;
        comp = t.comp;
        otro = t.otro;
        serie = *(Videojuego::getSerie());
    }
    // Print all parameters
    void print() {
        cout << "Num serie: " << serie << ", precio: " << precio << ", nombre: " << nombre << ". Aventura. " << "Atr 1: " << color << ", Atr 2: " << comp << ", Atr 3: " << otro << '\n';
    }
    void accept(IVisitor* visitor);
private:
    int serie;
    string color, comp, otro;
};

class Aprendizaje : public CloneCRTP<Videojuego, Aprendizaje> {
public:
    // Default Constructor
    Aprendizaje() {};
    // Argument Constructor
    Aprendizaje(string in_atr1, string in_atr2, string in_atr3, float precio, string nombre) : nivel(in_atr1), funcion(in_atr2), otro(in_atr3) {
        Videojuego::setValues(precio, nombre);
        serie = *(Videojuego::getSerie());
    }
    // Copy Constructor
    Aprendizaje(const Aprendizaje& t) {
        precio = t.precio;
        nombre = t.nombre;
        nivel = t.nivel;
        funcion = t.funcion;
        otro = t.otro;
        serie = *(Videojuego::getSerie());
    }
    // Print all parameters
    void print() {
        cout << "Num serie: " << serie << ", precio: " << precio << ", nombre: " << nombre << ". Aprendizaje. " << "Atr 1: " << nivel << ", Atr 2: " << funcion << ", Atr 3: " << otro << '\n';
    }
    void accept(IVisitor* visitor);
private:
    int serie;
    string nivel, funcion, otro;
};

// Factory method
class Creator {
private:
    static Creator* instance;
    template <class Tipo>
    Tipo* factoryMethod(string in_atr1, string in_atr2, string in_atr3, float precio, string nombre) {
        return new Tipo(in_atr1, in_atr2, in_atr3, precio, nombre);
    }
    Creator() {}
    ~Creator() {}
public:
    template <class Tipo>
    Tipo* crearVideojuego(string in_atr1, string in_atr2, string in_atr3, float precio, string nombre) {
        Tipo* videojuego = factoryMethod<Tipo>(in_atr1, in_atr2, in_atr3, precio, nombre);
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

class Proxy {
private:
    static Proxy* instance;
    queue<Videojuego*> queue;
    Proxy() {}
public:
    // Singleton implementation
    static Proxy* getInstance() {
        if(instance == NULL) {
            instance = new Proxy;
        }
        return instance;
    }
    bool eliminarVideoJuego(vector<Videojuego*>& inventario, int index) {
        addToDeleted(inventario[index]);
        inventario.erase(inventario.begin() + index);
        return true;
    }
    void addToDeleted(Videojuego* v) {
        if(queue.size() == 3) {
            queue.pop();
        }
        queue.push(v);
    }
    Videojuego* getFrontPop() {
        if(queue.size() > 0) {
            Videojuego* v = queue.front();
            queue.pop();
            return v;
        }
        return NULL;
    }
};

class Almacen {
private:
    static Almacen* instance;
    vector<Videojuego*> inventario;
    queue<Videojuego*> lastThree;

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
    bool agregarJuego(Videojuego* nuevo) {
        inventario.push_back(nuevo);
        nuevo->notifyAll(nuevo);
        return true;
    }
    bool eliminarJuegoNombre(string nombre) {
        for(int i = 0; i < inventario.size(); i++) {
            if(inventario[i]->nombre == nombre) {
                return Proxy::getInstance()->eliminarVideoJuego(inventario, i);
            }
        }
        return false;
    }
    bool eliminarJuegoSerie(int serie) {
        for(int i = 0; i < inventario.size(); i++) {
            if(*(inventario[i]->serie) == serie) {
                return Proxy::getInstance()->eliminarVideoJuego(inventario, i);;
            }
        }
        return false;
    }
    void deshacer() {
        Videojuego* v = Proxy::getInstance()->getFrontPop();
        while(v) {
            agregarJuego(v);
            v = Proxy::getInstance()->getFrontPop();
        }
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
            if(*(inventario[i]->serie) == serie) {
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

void menuNuevoVJ(Creator* creador, Almacen* almacen, Publico* publico) {
    int seleccion, copias;
    float precio;
    string nombre, cust1, cust2, cust3;
    Videojuego *v;
    cout << "Selecciona el tipo de juego:\n1 - Estrategia\n2 - Aventura\n3 - Aprendizaje\n";
    cin >> seleccion;
    cout << "Ingresa el nombre:\n";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingresa el precio:\n";
    cin >> precio;
    cin.ignore();
    cout << "Ingresa parámetro específico 1:\n";
    getline(cin, cust1);
    cout << "Ingresa parámetro específico 2:\n";
    getline(cin, cust2);
    cout << "Ingresa parámetro específico 3:\n";
    getline(cin, cust3);
    cout << "Ingresa cantidad de copias (1+):\n";
    cin >> copias;
    switch(seleccion) {
        case 1:
            v = creador->crearVideojuego<Estrategia>(cust1,cust2,cust3,precio,nombre);
            break;
        case 2:
            v = creador->crearVideojuego<Aventura>(cust1,cust2,cust3,precio,nombre);
            break;
        case 3:
            v = creador->crearVideojuego<Aprendizaje>(cust1,cust2,cust3,precio,nombre);
            break;
        default:
            return;
    }
    if(!copias) return;
    v->attach(publico);
    almacen->agregarJuego(v);
    for(int i = 1; i < copias; i++) {
        almacen->agregarJuego(v->clone());
    }
}

void menuEliminar(Almacen* almacen) {
    int seleccion, serie;
    string nombre;
    cout << "Seleccione el método de búsqueda\n1 - Nombre\n2 - Número de serie\n";
    cin >> seleccion;
    switch(seleccion) {
        case 1:
            cout << "Ingrese nombre del videojuego:\n";
            cin.ignore();
            getline(cin, nombre);
            if(almacen->eliminarJuegoNombre(nombre)) {
                cout << "Eliminado exitosamente\n";
            } else {
                cout << "Juego no encontrado\n";
            }
            break;
        case 2:
            cout << "Ingrese el número de serie del videojuego:\n";
            cin >> serie;
            if(almacen->eliminarJuegoSerie(serie)) {
                cout << "Eliminado exitosamente\n";
            } else {
                cout << "Juego no encontrado\n";
            }
            break;
        default:
            return;
    }
}

void menuOrdenar(Almacen* almacen) {
    int seleccion;
    cout << "Seleccione el orden deseado:\n1 - Ascendiente\n2 - Descendiente\n";
    cin >> seleccion;
    switch(seleccion) {
        case 1:
            almacen->ordenarInventario(true);
            break;
        case 2:
            almacen->ordenarInventario(false);
            break;
        default:
            return;
    }
}

void menuBuscar(Almacen* almacen) {
    int seleccion, serie;
    string nombre;
    Videojuego *v;
    cout << "Seleccione el método de búsqueda\n1 - Nombre\n2 - Número de serie\n";
    cin >> seleccion;
    switch(seleccion) {
        case 1:
            cout << "Ingrese nombre del videojuego:\n";
            cin.ignore();
            getline(cin, nombre);
            v = almacen->buscarJuegoNombre(nombre);
            if(v) {
                cout << "Encontrado:\n";
                v->print();
            } else {
                cout << "Juego no encontrado\n";
            }
            break;
        case 2:
            cout << "Ingrese el número de serie del videojuego:\n";
            cin >> serie;
            v = almacen->buscarJuegoSerie(serie);
            if(v) {
                cout << "Encontrado:\n";
                v->print();
            } else {
                cout << "Juego no encontrado\n";
            }
            break;
        default:
            return;
    }
}

void menuCambioPrecio(Almacen* almacen) {
    int seleccion;
    cout << "Elije la el ajuste de precio deseado:\n1 - Aumentar 15%\n2 - Reducir 15%\n";
    cin >> seleccion;
    switch(seleccion) {
        case 1:
            almacen->operacionPrecios(true);
            break;
        case 2:
            almacen->operacionPrecios(false);
            break;
        default:
            return;
    }
}

void waitForEnter() {
    cin.ignore();
    cout << "Presiona enter para continuar\n";
    cin.get();
}

void menuPrincipal(Creator* creador, Almacen* almacen, Publico* publico) {
    int seleccion = 0;
    while(seleccion != 9) {
        cout << "Bienvenido a Jueg A.S.\n-------------------------------\n1 - Crear videojuego\n2 - Eliminar videojuego\n3 - Deshacer últimas tres operaciones\n4 - Ordenar inventario\n5 - Buscar\n6 - Número total de videojuegos\n7 - Imprimir inventario\n8 - Aplicar cambio de precio\n9 - Salir\n";
        cin >> seleccion;
        switch(seleccion) {
            case 1:
                menuNuevoVJ(creador, almacen, publico);
                break;
            case 2:
                menuEliminar(almacen);
                break;
            case 3:
                almacen->deshacer();
                break;
            case 4:
                menuOrdenar(almacen);
                break;
            case 5:
                menuBuscar(almacen);
                break;
            case 6:
                cout << almacen->getNumeroDeJuegos() << '\n';
                break;
            case 7:
                almacen->imprimirInventario();
                break;
            case 8:
                menuCambioPrecio(almacen);
                break;
            default:
                return;
        }
        waitForEnter();
    }
}

Creator* Creator::instance = NULL;
Almacen* Almacen::instance = NULL;
Proxy* Proxy::instance = NULL;
int* Videojuego::serie = NULL;

int main() {
    Creator* creador = Creator::getInstance();
    Almacen* almacen = Almacen::getInstance();
    Proxy* proxy = Proxy::getInstance();

    Publico* publico = new Publico;

    menuPrincipal(creador, almacen, publico);
    
    return 1;
}