#ifndef GALERIA_H
#define GALERIA_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Cliente {
private:
    string nombre;
    string direccion;
public:
    Cliente(string nombre_in, string direccion_in): nombre(nombre_in), direccion(direccion_in) { }
};

class Cuadro {
private:
    string autor;
    float precio_inicial;
public:
    Cuadro(string autor_in, float precio): autor(autor_in), precio_inicial(precio) { }
};

class Venta {
private:
    float precio;
    int fecha;
    Cuadro *pintura;
    Cliente *comprador;
public:
    Venta(Cuadro *pintura_in, Cliente *comprador_in, float precio_in): pintura(pintura_in), comprador(comprador_in), precio(precio_in) {
        // Agregar formato fecha
        fecha = 1;
    }
    float generaPrecio() {
        return 1;
    }
};

class Ventas {
private:
    vector<Venta> *lista_ventas;
public:
    Ventas() { }
    Venta getSimilares(Cuadro *pieza) {
        return lista_ventas.;
    }
    void addVenta(Venta nueva_venta) {
        //lista_ventas->insert(nueva_venta);
    }
};

class Galeria {
private:
    Ventas *historial;
public:
    Galeria() {
        //historial = new Ventas;
    }
    float getOferta(Cuadro *pieza) {
        //Cuadro similar = historial->getSimilares(pieza);
        return calculaPrecio(pieza);
    }
    bool vender(Cuadro *pieza, Cliente *comprador, float precio) {
        //Venta *transaccion = new Venta(pieza, comprador, precio);
        //historial->addVenta(transaccion);
        return true;
    }
    float calculaPrecio(Cuadro *pieza) {
        // Agregar cálculo de precio
        return 100;
    }
};

#endif
