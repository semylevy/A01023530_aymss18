class Prototype {
public:
    virtual Prototype* clone() = 0;
};

class ConcretePrototype1 : public Prototype {
    Prototype* clone() {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype {
    Prototype* clone() {
        return new ConcretePrototype2(*this);
    }
};

int main() {
    ConcretePrototype1 *c1 = new ConcretePrototype1;
}
