#include <iostream>

using namespace std;

class Command {
public:
    virtual void execute() = 0;
};

class Receiver {
public:
    void method_1() {
        cout << "Method 1 call\n";
    }
    void method_2() {
        cout << "Method 2 call\n";
    }
};

class Caller {
public:
    void setCommand(Command *cmd) {
        my_cmd = cmd;
    }
    void executeAction() {
        my_cmd->execute();
    }
private:
    Command *my_cmd;
};

class ConcreteCommand1 : public Command {
public:
    ConcreteCommand1(Receiver *r) : my_r(r) { }
    void execute() {
        my_r -> method_1();
    }
private:
    Receiver *my_r;
};

class ConcreteCommand2 : public Command {
public:
    ConcreteCommand2(Receiver *r) : my_r(r) { }
    void execute() {
        my_r -> method_2();
    }
private:
    Receiver *my_r;
};

// Invoker
int main() {
    Receiver *r = new Receiver;
    
    ConcreteCommand1 *cc1 = new ConcreteCommand1(r);
    ConcreteCommand2 *cc2 = new ConcreteCommand2(r);
    
    Caller *c = new Caller;
    
    c->setCommand(cc1);
    c->executeAction();
    c->setCommand(cc2);
    c->executeAction();
    
    return 1;
}
