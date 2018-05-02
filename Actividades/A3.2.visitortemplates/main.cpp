#include "husband.h"
#include "wife.h"

int main() {
    Husband h;
    h.name = "Pedro";
    Wife w;
    w.name = "Juana";
    h.w = &w;
    w.h = &h;
    h.whoami();
    w.whoami();
    return 1;
}
