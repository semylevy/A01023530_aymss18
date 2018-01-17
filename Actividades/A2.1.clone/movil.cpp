#include <iostream>

using namespace std;

class Movil {
public:
    virtual Movil* clone() = 0;
    void encender() {}
    void apagar() {}
    void reiniciar() {}
    void restaurar() {}
    
    float *bateria;
    bool *status;
    int serie;
    int modelo;
    
    Movil() {}
    Movil(float bateria, bool status, int serie, int modelo) : bateria(new float(bateria)), status(new bool(status)), serie(serie), modelo(modelo) {}
};

class Tablet : public Movil {
public:
    // Default constructor
    Tablet() {};
    // Argument constructor
    Tablet(float bateria, bool status, int serie, int modelo, int pantalla) : Movil(bateria, status, serie, modelo), pantalla(new int (pantalla)) {}
    // Copy constructor
    Tablet(const Tablet& t) {
        bateria = new float(*(t.bateria));
        status = new bool(*(t.status));
        serie = t.serie;
        modelo = t.modelo;
        pantalla = new int(*(t.pantalla));
    }
    // Clone implementation
    Movil* clone() {
        return new Tablet(*this);
    }
    // Print all parameters
    void print() {
        cout << "\tTablet\nBateria: " << *bateria << "\nStatus: " << *status << "\nSerie: " << serie << "\nModelo: " << modelo << "\n";
    }
private:
    int* pantalla;
};

class Smartphone : public Movil {
public:
    // Default Constructor
    Smartphone() {};
    // Argument Constructor
    Smartphone(float bateria, bool status, int serie, int modelo, int senal) : Movil(bateria, status, serie, modelo), senal(new int(senal)) {}
    // Copy Constructor
    Smartphone(const Smartphone& t) {
        bateria = new float(*(t.bateria));
        status = new bool(*(t.status));
        serie = t.serie;
        modelo = t.modelo;
        senal = new int(*(t.senal));
    }
    // Clone implementation
    Movil* clone() {
        return new Smartphone(*this);
    }
private:
    int* senal;
};

class Smartwatch : public Movil {
public:
    // Default Constructor
    Smartwatch() {};
    // Argument Constructor
    Smartwatch(float bateria, bool status, int serie, int modelo, int hora) : Movil(bateria, status, serie, modelo), hora(new int(hora)) {}
    // Copy Constructor
    Smartwatch(const Smartwatch& t) {
        bateria = new float(*(t.bateria));
        status = new bool(*(t.status));
        serie = t.serie;
        modelo = t.modelo;
        hora = new int(*(t.hora));
    }
    // Clone implementation
    Movil* clone() {
        return new Smartwatch(*this);
    }
private:
    int* hora;
};

int main() {
    Movil *t1 = new Tablet(1,2,3,4,5);
    
    return 1;
}
