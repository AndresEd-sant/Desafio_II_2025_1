// src/main.cpp
#include <iostream>
#include <string>
#include "administrador.h"

using namespace std;

void menuAdministrador() {
    cout << "\n=== MENÚ ADMINISTRADOR ===\n";
    cout << "1. Cambio de Dia\n";
    cout << "2. Consultar Huespedes\n";
    cout << "3. Salir\n";
}

void menuUsuario() {
    cout << "\n=== MENÚ HUÉSPED ===\n";
    cout << "1. Buscar alojamiento\n";
    cout << "2. Ver reservaciones\n";
    cout << "3. Cancelacion de reservas\n";
    cout << "4. Salir\n";
}

string login(string *documento, string *contrasena){
    string tipo;
    //Prototipo de autenticacion
    return tipo;
}

int main() {
    string documento;
    string contrasena;

    cout << "Bienvenido a UdeAStay\n";
    cout << "Ingrese su numero de documento: ";
    cin >> documento;
    cout << "Ingrese su contrasena: ";
    cin >> contrasena;



    // Boceto de autenticación (simulada)
    if (login(&documento,&contrasena) == "admin") {
        cout << "\nInicio de sesión exitoso como ADMINISTRADOR\n";
        menuAdministrador();
    } else if (login(&documento,&contrasena) == "usuario") {
        cout << "\nInicio de sesión exitoso como HUÉSPED\n";
        menuUsuario();
    } else {
        cout << "\nTipo de usuario no válido. Intente de nuevo.\n";
    }
    string nombre = "Andres Ed";
    string documentoss = "123456";
    string contrasenass = "123";
    unsigned int lugares = 3;
    float puntuacion = 5.0;
    administrador andresito(nombre,documentoss,contrasenass,lugares,puntuacion);
    cout << andresito.getNombre()<<endl;


    return 0;
}
