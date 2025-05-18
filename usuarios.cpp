#include "usuarios.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor
Usuarios::Usuarios(string documento, string contrasena, string nombre) {
    this->Documento = documento;
    this->Contrasena = contrasena;
    this->Nombre = nombre;
    this->N_reservaciones = 0;
    this->ReservasT = nullptr; // No tiene reservas al inicio
}

// Getters
string Usuarios::getDocumento() {
    return Documento;
}

string Usuarios::getNombre() {
    return Nombre;
}

string Usuarios::getcontrasena() {
    return Contrasena;
}

unsigned int Usuarios::getN_reservaciones() {
    return N_reservaciones;
}

// Destructor
Usuarios::~Usuarios() {
    if (ReservasT != nullptr) {
        delete[] ReservasT; // Libera memoria de reservas si existía
    }
}
