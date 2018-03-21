#include <iostream>
#include <string>
#include <list>

using namespace std;

class DocPart {
public:
    string text;
    virtual string toHTML() = 0;
    virtual string toText() = 0;
    virtual string toLatex() = 0;
};

class Text : public DocPart{
public:
    string toHTML() {
        return text;
    }
    string toText() {
        return text;
    }
    string toLatex() {
        return text;
    }
};

class Bold : public DocPart {
public:
    string toHTML() {
        return "<b>" + text + "</b>";
    }
    string toText() {
        return text;
    }
    string toLatex() {
        return "\\textbf{" + text + "}";
    }
};

class HyperLink : public DocPart {
public:
    string URL;
    string toHTML() {
        return "<a href='" + URL + "'>" + text + "</a>";
    }
    string toText() {
        return text;
    }
    string toLatex() {
        return "\\href{" + URL + "}{" + text + "}";
    }
};

class Document {
public:
    list<DocPart*> docpart;
    string toHTML() {
        string out = "";
        for(DocPart* d : docpart) {
            out += d->toHTML();
        }
        return out;
    }
    string toText() {
        string out = "";
        for(DocPart* d : docpart) {
            out += d->toText();
        }
        return out;
    }
    string toLatex() {
        string out = "";
        for(DocPart* d : docpart) {
            out += d->toLatex();
        }
        return out;
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
    
    cout << d.toLatex();
    return 1;
}
