#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Hola Ariel, el siguiente código está basado en en Command, Factory Method, y Singleton Pattern.
// Si al leer el código te preguntas, ¿dónde está el Factory?, la respuesta es muy sencilla.
// Utilizo una combinación de las clases de Command, y la clase ConcreteCreator (de Factory) para determinar
// que tipo de Caller se necesita, y crearlo.
//
// Gracias. Atentamente,
// Salomon Levy.


using namespace std;

struct params {
    string from, to, subject, mensaje, telefono, nombre;
};

class Command {
public:
    virtual void execute(struct params) = 0;
};

class Receiver {
public:
    void enviaEmail(struct params p) {
        cout << "Enviando email a" << p.to << "\n";
    }
    void enviaSms(struct params p) {
        cout << "Enviando sms a " << p.telefono << "\n";
    }
    void llamaTelefono(struct params p) {
        cout << "Llamando a " << p.nombre << " al número " << p.telefono << "\n";
    }
};

class Caller {
public:
    void setCommand(Command *cmd) {
        my_cmd = cmd;
    }
    void executeAction(struct params p) {
        my_cmd->execute(p);
    }
private:
    Command *my_cmd;
};

class CcEmail : public Command {
public:
    CcEmail(Receiver *r_in) : r(r_in) { }
    void execute(struct params p) {
        r -> enviaEmail(p);
    }
private:
    Receiver *r;
};

class CcSMS : public Command {
public:
    CcSMS(Receiver *r_in) : r(r_in) { }
    void execute(struct params p) {
        r -> enviaSms(p);
    }
private:
    Receiver *r;
};

class CcTelefono : public Command {
public:
    CcTelefono(Receiver *r_in) : r(r_in) { }
    void execute(struct params p) {
        r -> llamaTelefono(p);
    }
private:
    Receiver *r;
};

class Cliente {
public:
    virtual Caller* factoryMethod(string) = 0;
    
    void addClient(string id_in, string cus_name_in, string cus_last_in, string type_comm_in, string mail_in, string phone_num_in, string calle_in, string numero_in, string colonia_in) {
        c = factoryMethod(type_comm_in);
        id = id_in;
        cus_name = cus_name_in;
        cus_last = cus_last_in;
        type_comm = type_comm_in;
        mail = mail_in;
        phone_num = phone_num_in;
        calle = calle_in;
        numero = numero_in;
        colonia = colonia_in;
    }
    
    void contactar() {
        struct params p;
        p.telefono = phone_num;
        p.nombre = cus_name;
        p.to = mail;
        c->executeAction(p);
    }
    void print() {
        cout << "Nombre: " << cus_name << " Apellido: " << cus_last << " Tipo: " <<  type_comm << " Mail: " <<  mail << " Telefono: " <<  phone_num << " Calle: " <<  calle << " Numero: " <<  numero << " Colonia: " <<  colonia << "\n";
    }
private:
    Caller *c;
    string id, cus_name, cus_last, type_comm, mail, phone_num, calle, numero, colonia;
};

class ConcreteCreator : public Cliente {
public:
    Caller* factoryMethod(string type_comm) {
        if (type_comm == "mail") {
            Caller *c = new Caller;
            c->setCommand(new CcEmail(new Receiver));
            return c;
        } else if(type_comm == "sms") {
            Caller *c = new Caller;
            c->setCommand(new CcSMS(new Receiver));
            return c;
        } else if(type_comm == "phone_call") {
            Caller *c = new Caller;
            c->setCommand(new CcTelefono(new Receiver));
            return c;
        } else {
            return NULL;
        }
    }
};

class Tienda {
private:
    static Tienda* instance;
    vector<Cliente*> clientes;
    Tienda () { }
    ~Tienda () { }
public:
    static Tienda* getInstance() {
        if(instance == NULL) {
            instance = new Tienda;
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
    void readFromFile() {
        ifstream file;
        file.open ("customers.csv");
        string id, cus_name, cus_last, type_comm, mail, phone_num, calle, numero, colonia;
        
        //Remove first line (id's)
        string dummy;
        getline(file, dummy, '\n');
        
        while (getline(file, id, ',')) {
            getline(file, cus_name, ',') ;
            getline(file, cus_last, ',') ;
            getline(file, type_comm, ',');
            getline(file, mail, ',');
            getline(file, phone_num, ',');
            getline(file, calle, ',');
            getline(file, numero, ',');
            getline(file, colonia, '\n');
            
            Cliente *nuevo = new ConcreteCreator();
            nuevo->addClient(id, cus_name, cus_last, type_comm, mail, phone_num, calle, numero, colonia);
            clientes.push_back(nuevo);
        }
        file.close();
    }
    void imprimirTodos() {
        for(int i = 0; i < clientes.size(); i++) {
            clientes[i]->print();
        }
    }
    void contactarTodos() {
        for(int i = 0; i < clientes.size(); i++) {
            clientes[i]->contactar();
        }
    }
};

Tienda* Tienda::instance = NULL;

int main() {
    // Creas instancia singleton de Tienda
    Tienda* instance = Tienda::getInstance();
    
    // Lee de archivo (formato de Classroom) y crea Clientes en Tienda
    instance->readFromFile();
    
    // Llama los métodos para contactar de cada Cliente, respectivamente
    instance->contactarTodos();
    
    // Opcional: imprimir todos los clientes
    // instance->imprimirTodos();
    
    // Nota: falta implementar la entrada de datos extras en comunicación (ej. from, subjeft, etc), pero la struct está preparada para recibirlos
    return 1;
}
