#include <iostream>
#include "galeria.h"

int main() {
    Galeria mi_tienda;
    Cliente cli_1("Semy", "Dir");
    Cuadro cuad_1("Picasso", "Guernica", 100);
    Cuadro cuad_2("Frida Kahlo", "Diego y yo", 50);
    mi_tienda.vender(cuad_1, cli_1, 120, 1980);
    mi_tienda.vender(cuad_2, cli_1, 80, 1995);
    
    string main_input;
    
    do {
        cout << "1 -- Obtener oferta\n2 -- Imprimir ventas\n3 -- Ayuda\n0 -- Salir\n";
        getline (cin, main_input);
        if(main_input == "1") {
            string nombre, autor;
            cout << "Nombre del cuadro: ";
            getline (cin, nombre);
            cout << "Autor del cuadro: ";
            getline (cin, autor);
            float precio = mi_tienda.getOferta(Cuadro(autor, nombre, 0));
            if(precio == -1) {
                cout << "No se encontró ningún cuadro similar.\n";
                continue;
            }
            cout << "Precio del cuadro: " << precio << "\n¿Comprar por ese precio?\n[y] Si\n[n] No\n";
            string purchase_answer;
            getline (cin, purchase_answer);
            if(purchase_answer == "y") {
                string nombre_comprador, direccion_comprador;
                cout << "Nombre del comprador: ";
                getline (cin, nombre_comprador);
                cout << "Dirección del comprador: ";
                getline (cin, direccion_comprador);
                mi_tienda.vender(Cuadro(autor, nombre, precio),Cliente(nombre_comprador, direccion_comprador), precio);
                cout << "¡Gracias por comprar!\n";
            }
        } else if(main_input == "2") {
            mi_tienda.imprimirVentas();
        } else if(main_input == "3") {
            cout << "\nInstrucciones:\nPara agregar ventas anteriores, editar directamente el código. El formato es el siguiente:\nLlamar método Galeria.vender(Cuadro, Cliente, Precio, Año) con objetos:\n\n Cuadro(Autor, Título, Precio)\n Cliente(Nombre, Dirección)\n\nSemy Levy, 2018.\n\n";
        }
    } while(main_input != "0");
    return 1;
}
