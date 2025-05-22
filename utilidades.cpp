#include "utilidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void menuPrincipal() {
    cout << "Bienvenido a UdeAStay\n";
    cout << "1. Login\n2. Salir\n";
}

void menuAdministrador() {
    cout << "\n=== MENU ADMINISTRADOR ===\n";
    cout << "1. Cambio de Dia\n";
    cout << "2. Ver Alojamientos\n";
    cout << "3. Ver/Cancelar Reservas\n";
    cout << "4. Salir\n";
}

void menuUsuario() {
    cout << "\n=== MENU HUÉSPED ===\n";
    cout << "1. Buscar alojamiento\n2. Ver/Cancelar Reservas\n3. Salir\n";
}

string login(administrador*& adminObj){//,usuario*& userObj) {
    ifstream archivo;
    string documento, contrasena;

    cout << "Ingrese su numero de documento: ";
    cin >> documento;
    cout << "Ingrese su contrasena: ";
    cin >> contrasena;

    archivo.open("administradores.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string doc, pass, nombre, puntuacionStr, numLugaresStr;
            getline(ss, doc, ';'); getline(ss, pass, ';'); getline(ss, nombre, ';');
            getline(ss, puntuacionStr, ';'); getline(ss, numLugaresStr, ';');

            if (doc == documento && pass == contrasena) {
                adminObj = new administrador(nombre, doc, pass, stoi(numLugaresStr), stof(puntuacionStr));
                archivo.close();
                return "admin";
            }
        }
        archivo.close();
    }
    archivo.open("usuarios.txt");
    if (archivo.is_open()){
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string doc, pass, nombre, antiguedad, puntuacion;
            getline(ss, doc, ';'); getline(ss, pass, ';'); getline(ss, nombre, ';');
            getline(ss, antiguedad, ';'); getline(ss, puntuacion, ';');

            if (doc == documento && pass == contrasena) {
                //userObj = new usuario(nombre, doc, pass);

                archivo.close();
                return "user";
            }
        }
        archivo.close();

    }


    return "0";
}
