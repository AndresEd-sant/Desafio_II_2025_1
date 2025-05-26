#include "lugar.h"
#include <iostream>
using namespace std;

Lugar::Lugar(string codigo, string nombre, string departamento, string municipio,
             string tipo, float precioNoche, string documentoAdmin, float puntuacion) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->departamento = departamento;
    this->municipio = municipio;
    this->tipo = tipo;
    this->precioNoche = precioNoche;
    this->documentoAdmin = documentoAdmin;
    this->puntuacion = puntuacion;
}

string Lugar::getCodigo() { return codigo; }
string Lugar::getNombre() { return nombre; }
string Lugar::getDepartamento() { return departamento; }
string Lugar::getMunicipio() { return municipio; }
string Lugar::getTipo() { return tipo; }
float Lugar::getPrecioNoche() { return precioNoche; }
string Lugar::getDocumentoAdmin() { return documentoAdmin; }
float Lugar::getPuntuacion() {return puntuacion;}

Lugar::~Lugar() {
    // nada dinámico aún
}
