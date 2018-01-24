#include <iostream>

using namespace std;

class Movil {
public:
    virtual Movil* clone() = 0;
    virtual void print() = 0;
    void encender() {
        *status = true;
    }
    void apagar() {
        *status = false;
    }
    void reiniciar() {}
    void restaurar() {}
    
    float *bateria;
    bool *status;
    int serie;
    int modelo;
    
    Movil() {}
    Movil(float bateria, bool status, int serie, int modelo) : bateria(new float(bateria)), status(new bool(status)), serie(serie), modelo(modelo) {}
    
    void setValues(float bateria_in, bool status_in, int serie_in, int modelo_in) {
        bateria = new float(bateria_in);
        status = new bool(status_in);
        serie = serie_in;
        modelo = modelo_in;
    }
};

template <class Base, class Subclass>
class CloneCRTP : public Base {
public:
    Base* clone() {
        return new Subclass(dynamic_cast<Subclass&>(*this));
    }
};

class Tablet : public CloneCRTP<Movil, Tablet> {
public:
    // Default constructor
    Tablet() {};
    // Argument constructor
    Tablet(float bateria, bool status, int serie, int modelo, int pantalla) : pantalla(new int (pantalla)) {
        Movil::setValues(bateria, status, serie, modelo);
    }
    // Copy constructor
    Tablet(const Tablet& t) {
        bateria = new float(*(t.bateria));
        status = new bool(*(t.status));
        serie = t.serie;
        modelo = t.modelo;
        pantalla = new int(*(t.pantalla));
    }
    // Print all parameters
    void print() {
        cout << "**** Tablet ****\nBateria: " << *bateria << "\nStatus: " << *status << "\nSerie: " << serie << "\nModelo: " << modelo << "\nPantalla: " << *pantalla << "\n";
    }
private:
    int* pantalla;
};

class Smartphone : public CloneCRTP<Movil, Smartphone>{
public:
    // Default Constructor
    Smartphone() {};
    // Argument Constructor
    Smartphone(float bateria, bool status, int serie, int modelo, int senal) : senal(new int(senal)) {
        Movil::setValues(bateria, status, serie, modelo);
    }
    // Copy Constructor
    Smartphone(const Smartphone& t) {
        bateria = new float(*(t.bateria));
        status = new bool(*(t.status));
        serie = t.serie;
        modelo = t.modelo;
        senal = new int(*(t.senal));
    }
    // Print all parameters
    void print() {
        cout << "**** Smartphone ****\nBateria: " << *bateria << "\nStatus: " << *status << "\nSerie: " << serie << "\nModelo: " << modelo << "\nSeñal: " << *senal << "\n";
    }
private:
    int* senal;
};

class Smartwatch : public CloneCRTP<Movil, Smartwatch> {
public:
    // Default Constructor
    Smartwatch() {};
    // Argument Constructor
    Smartwatch(float bateria, bool status, int serie, int modelo, int hora) : hora(new int(hora)) {
        Movil::setValues(bateria, status, serie, modelo);
    }
    // Copy Constructor
    Smartwatch(const Smartwatch& t) {
        bateria = new float(*(t.bateria));
        status = new bool(*(t.status));
        serie = t.serie;
        modelo = t.modelo;
        hora = new int(*(t.hora));
    }
    // Print all parameters
    void print() {
        cout << "**** Smartwatch ****\nBateria: " << *bateria << "\nStatus: " << *status << "\nSerie: " << serie << "\nModelo: " << modelo << "\nHora: " << *hora << "\n";
    }
private:
    int* hora;
};

int main() {
    Movil *t1 = new Tablet(1,false,3,4,5);
    Movil *s1 = new Smartphone(5,false,3,2,1);
    Movil *w1 = new Smartwatch(1,false,1,1,1);
    
    t1->encender();
    s1->encender();
    
    Movil *t2 = t1->clone();
    Movil *s2 = s1->clone();
    Movil *w2 = w1->clone();
    
    s2->apagar();
    w2->encender();
    
    t1->print();
    t2->print();
    s1->print();
    s2->print();
    w1->print();
    w2->print();
    
    return 1;
}
