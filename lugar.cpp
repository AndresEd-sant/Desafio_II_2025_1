#include "lugar.h"

Lugar::Lugar(string codigo, string nombre, string departamento, string municipio,
             string tipo, float precioNoche, string documentoAdmin, float puntuacion)
    : codigo(codigo),
    nombre(nombre),
    departamento(departamento),
    municipio(municipio),
    tipo(tipo),
    precioNoche(precioNoche),
    documentoAdmin(documentoAdmin),
    puntuacion(puntuacion) {}

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
