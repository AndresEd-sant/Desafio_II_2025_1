// src/main.cpp
#include <iostream>
#include <string>
#include "usuarios.h"
#include "gestor_usuario.h"

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
int main(){

string tipo;
Usuarios* sesion = loginDesdeArchivos("admins.txt", "usuarios.txt", tipo);

if (sesion != nullptr) {
    if (tipo == "admin") {
        cout << "Bienvenido administrador: " << sesion->getNombre() << endl;
    } else if (tipo == "usuario") {
        cout << "Bienvenido usuario: " << sesion->getNombre() << endl;
    }
    // No olvides liberar la sesión si no la usas después
    delete sesion;
}
else {
    cout << "No se pudo iniciar sesión." << endl;}
}
