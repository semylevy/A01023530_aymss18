#include <iostream>
#include <string>
#include <list>

using namespace std;

class IVisitor;

class DocPart {
public:
    string text;
    virtual void accept(IVisitor*) = 0;
};

class Text : public DocPart {
public:
    void accept(IVisitor* visitor);
};

class HyperLink : public DocPart {
public:
    string URL;
    void accept(IVisitor* visitor);
};

class Bold : public DocPart {
public:
    void accept(IVisitor* visitor);
};

class IVisitor {
public:
    string out;
    virtual void visit(HyperLink) = 0;
    virtual void visit(Bold) = 0;
    virtual void visit(Text) = 0;
};


void Text::accept(IVisitor* visitor) {
    visitor->visit(*this);
}

void HyperLink::accept(IVisitor* visitor) {
    visitor->visit(*this);
}

void Bold::accept(IVisitor* visitor) {
    visitor->visit(*this);
}

class HTMLVisitor : public IVisitor {
public:
    void visit(HyperLink h) {
        out += "<a href='" + h.URL + "'>" + h.text + "</a>";
    }
    void visit(Text h) {
        out += h.text;
    }
    void visit(Bold h) {
        out += "<b>" + h.text + "</b>";
    }
};

class TextVisitor : public IVisitor {
public:
    void visit(HyperLink h) {
        out += h.text;
    }
    void visit(Text h) {
        out += h.text;
    }
    void visit(Bold h) {
        out += h.text;
    }
};

class LatexVisitor : public IVisitor {
public:
    void visit(HyperLink h) {
        out += "\\href{" + h.URL + "}{" + h.text + "}";
    }
    void visit(Text h) {
        out += h.text;
    }
    void visit(Bold h) {
        out += "\\textbf{" + h.text + "}";
    }
};

class Document {
public:
    list<DocPart*> docpart;
    void accept(IVisitor* visitor) {
        for (DocPart* d : docpart) {
            d->accept(visitor);
        }
    }
};

int main() {
    Document d;
    Text t1;
    t1.text = "Hola, visita ";
    Bold t2;
    t2.text = "my ";
    HyperLink t3;
    t3.text = "página";
    t3.URL = "www.mypage.com";
    d.docpart.push_back(&t1);
    d.docpart.push_back(&t2);
    d.docpart.push_back(&t3);
    
    HTMLVisitor *htmlvisitor = new HTMLVisitor();
    d.accept(htmlvisitor);
    
    cout << htmlvisitor->out;
    
    return 1;
}
