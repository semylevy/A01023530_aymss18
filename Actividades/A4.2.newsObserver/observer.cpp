#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Subject;
class Observer;

class Observer {
public:
    virtual void update(string, Subject*) = 0;
};

class Subject {
public:
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
    void notifyAll(string move, Subject* s) {
        for(int i = 0; i < observers.size(); i++) {
            observers[i]->update(move, s);
        }
    }
    virtual string whoami() = 0;
private:
    vector<Observer*> observers;
};

class Trump : public Subject {
public:
    void makeNoise() {
        notifyAll("FAKE NEWS!", this);
    }
    string whoami() {
        return "PRESDIENT TRUMP";
    }
};

class Anaya : public Subject {
public:
    void makeNoise() {
        notifyAll("Hola a todos", this);
    }
    string whoami() {
        return "Anaya";
    }
};

class Meade : public Subject {
public:
    void makeNoise() {
        notifyAll("Por el país", this);
    }
    string whoami() {
        return "Meade";
    }
};

class Zavala : public Subject {
public:
    void makeNoise() {
        notifyAll("Quien?", this);
    }
    string whoami() {
        return "Zavala";
    }
};

class AMLO : public Subject {
public:
    void makeNoise() {
        notifyAll("Comida para todos!", this);
    }
    string whoami() {
        return "Ya Sabes Quien";
    }
};

class MVSNews : public Observer{
public:
    void update(string move, Subject* s) {
        cout << "MVS News: " << s->whoami() << " says " << move << '\n';
    }
};

class TelevisaNews : public Observer {
public:
    void update(string move, Subject* s) {
        cout << "Televisa Noticias: " << s->whoami() << " says " << move << '\n';
    }
};

class AztecaNews : public Observer {
public:
    void update(string move, Subject* s) {
        cout << "Azteca Noticias: " << s->whoami() << " says " << move << '\n';
    }
};

int main() {
    AMLO *sr = new AMLO();
    TelevisaNews *tn = new TelevisaNews();
    AztecaNews *an = new AztecaNews();
    sr->attach(tn);
    sr->attach(an);
    sr->makeNoise();
    return 1;
}