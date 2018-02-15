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
    string getNombre() {
        return nombre;
    }
};

class Cuadro {
private:
    string autor;
    string nombre;
    float precio_inicial;
public:
    Cuadro(string autor_in, string nombre_in, float precio): autor(autor_in), nombre(nombre_in), precio_inicial(precio) { }
    string getAutor() {
        return autor;
    }
    string getNombre() {
        return nombre;
    }
    float getPrecio() {
        return precio_inicial;
    }
};

class Venta {
private:
    float precio;
    int year;
    Cuadro pintura;
    Cliente comprador;
public:
    Venta(Cuadro pintura_in, Cliente comprador_in, float precio_in, int year_in=0): pintura(pintura_in), comprador(comprador_in), precio(precio_in), year(year_in) {
        if(!year) {
            time_t now = time(0);
            tm *fecha = localtime(&now);
            year = fecha->tm_year+1900;
        }
    }
    void imprimir() {
        cout << pintura.getAutor() << " - " << pintura.getNombre() << ". Comprado por " << comprador.getNombre() << ", " << year <<". \n";
    }
    string getAutor() {
        return pintura.getAutor();
    }
    int getYear() {
        return year;
    }
    float getPrecio() {
        return precio;
    }
};

class Ventas {
private:
    vector<Venta> lista_ventas;
public:
    Ventas() { }
    Venta getSimilares(Cuadro pieza) {
        for(int i = 0; i < lista_ventas.size(); i++) {
            if(lista_ventas[i].getAutor() == pieza.getAutor())
                return lista_ventas[i];
        }
        return Venta(Cuadro("","",-1), Cliente("",""), -1);
    }
    void imprimir() {
        for (int i = 0; i < lista_ventas.size(); i++)
            lista_ventas[i].imprimir();
    }
    void nuevaVenta(Venta nueva) {
        lista_ventas.push_back(nueva);
    }
};

class Galeria {
private:
    Ventas historial;
public:
    Galeria() { }
    float getOferta(Cuadro pieza) {
        Venta similar = historial.getSimilares(pieza);
        if(similar.getPrecio() == -1) {
            return -1;
        }
        return calculaPrecio(similar);
    }
    bool vender(Cuadro pieza, Cliente comprador, float precio, int year=0) {
        Venta transaccion(pieza, comprador, precio, year);
        historial.nuevaVenta(transaccion);
        return true;
    }
    float calculaPrecio(Venta pieza) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int curr_year = ltm->tm_year + 1900;
        int years = curr_year - pieza.getYear();
        float precio = pieza.getPrecio();
        for(int i = 0; i < years; i++) {
            precio*=1.085;
        }
        return precio;
    }
    void imprimirVentas() {
        historial.imprimir();
    }
};

#endif
