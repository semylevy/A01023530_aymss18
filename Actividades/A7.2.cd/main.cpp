#include <iostream>
#include <string>

using namespace std;

class Printer {
public:
    virtual void connect() = 0;
    virtual void setup() = 0;
};

class Document {
public:
    virtual void create() = 0;
    virtual void format() = 0;
};

class Laser : public Printer{
public:
    void connect() {
        cout << "Connecting laser\n";
    }
    void setup() {
        cout << "LaserHP setup\n";
    }
};

class Inyeccion : public Printer{
public:
    void connect() {
        cout << "Connecting Inyeccion\n";
    }
    void setup() {
        cout << "Inyeccion setup\n";
    }
};

class PDF : public Printer{
public:
    void connect() {
        cout << "Connecting PDF\n";
    }
    void setup() {
        cout << "PDF setup\n";
    }
};

class Postscript : public Printer{
public:
    void connect() {
        cout << "Connecting Postscript\n";
    }
    void setup() {
        cout << "Postscript setup\n";
    }
};

class Simple : public Document{
public:
    void create() {
        cout << "Creating simple\n";
    }
    void format() {
        cout << "Formatting simple\n";
    }
};

class Formato : public Document{
public:
    void create() {
        cout << "Creating formato\n";
    }
    void format() {
        cout << "Formatting formato\n";
    }
};

class Imagen : public Document{
public:
    void create() {
        cout << "Creating imagen\n";
    }
    void format() {
        cout << "Formatting imagen\n";
    }
};

class Creator
{
  private:
    static Creator* instance;
    Creator () {}
    ~Creator () {}

    template <class Tipo>
    Tipo *factoryMethod() {
        return new Tipo;
    }

  public:
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
    template <class Tipo>
    Tipo *createPrinter() {
        Tipo *printer = factoryMethod<Tipo>();
        printer->connect();
        printer->setup();
        return printer;
    }
    template <class Tipo>
    Tipo *createDocument() {
        Tipo *document = factoryMethod<Tipo>();
        document->create();
        document->format();
        return document;
    }
};

Creator* Creator::instance = NULL;

int main() {
    Creator* instance = Creator::getInstance();

    Document* v1 = instance->createDocument<Simple>();
    v1->format();
    
    return 1;
}