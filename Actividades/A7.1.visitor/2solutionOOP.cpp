class DocPart {
public:
    string text;
    virtual void accept(IVisitor*) = 0;
};

class Text : public DocPart {
public:
    void accept(IVisitor* visitor) {
        visitor->visit(*this);
    }
};

class HyperLink : public DocPart {
public:
    string URL;
    void accept(IVisitor* visitor) {
        visitor->visit(*this);
    }
};

class Bold : public DocPart {
public:
    void accept(IVisitor* visitor) {
        visitor->visit(*this);
    }
};

class IVisitor {
public:
    string out;
    virtual void visit(HyperLink) = 0;
    virtual void visit(Bold) = 0;
    virtual void visit(Text) = 0;
};

class HTMLVisitor : public : IVisitor {
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
    list<DocPart*> docpart;
};

int main() {
    return 1;
}
