#include <iostream>
#include <fstream>
#include <sstream>
#include "administrador.h"

using namespace std;

void menuAdministrador() {
    cout << "\n=== MENU ADMINISTRADOR ===\n";
    cout << "1. Cambio de Dia\n";
    cout << "2. Consultar Huespedes\n";
    cout << "3. Cancelar reservaciones\n";
    cout << "4. Salir\n";
}

void menuUsuario() {
    cout << "\n=== MENU HUÉSPED ===\n";
    cout << "1. Buscar alojamiento\n";
    cout << "2. Ver reservaciones\n";
    cout << "3. Cancelacion de reservas\n";
    cout << "4. Salir\n";
}

string login(string documento, string contrasena, administrador*& adminObj /*, huesped*& userObj */) {
    ifstream archivo;

    // ------------------ Buscar en administradores ------------------
    archivo.open("administradores.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir administradores.txt" << endl;
    } else {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string doc, pass, nombre, puntuacionStr, numLugaresStr;

            getline(ss, doc, ';');
            getline(ss, pass, ';');
            getline(ss, nombre, ';');
            getline(ss, puntuacionStr, ';');
            getline(ss, numLugaresStr, ';');

            if (doc == documento && pass == contrasena) {
                float puntuacion = stof(puntuacionStr);
                unsigned int numLugares = stoi(numLugaresStr);
                adminObj = new administrador(nombre, doc, pass, numLugares, puntuacion);
                archivo.close();
                return "admin";
            }
        }
        archivo.close();
    }

    // ------------------ Buscar en usuarios ------------------
    archivo.open("usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir usuarios.txt" << endl;
    } else {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string doc, pass, nombre, antiguedadStr, puntuacionStr;

            getline(ss, doc, ';');
            getline(ss, pass, ';');
            getline(ss, nombre, ';');
            getline(ss, antiguedadStr, ';');
            getline(ss, puntuacionStr, ';');

            if (doc == documento && pass == contrasena) {
                // Aquí se crearía el objeto huesped, cuando lo tengas implementado:
                // unsigned int antiguedad = stoi(antiguedadStr);
                // float puntuacion = stof(puntuacionStr);
                // userObj = new huesped(nombre, doc, pass, antiguedad, puntuacion);
                return "usuario";
            }
        }
        archivo.close();
    }

    return "";
}


int main() {
    string documento, contrasena;

    cout << "Bienvenido a UdeAStay\n";
    cout << "Ingrese su numero de documento: ";
    cin >> documento;
    cout << "Ingrese su contrasena: ";
    cin >> contrasena;

    administrador* adminObj = nullptr;

    string tipo = login(documento, contrasena, adminObj);
    if (tipo == "admin") {
        cout << "\nInicio de sesion exitoso como ADMINISTRADOR\n";
        cout << " Bienvenido "<<adminObj->getNombre()<<endl;
        menuAdministrador();

    } else if (tipo == "usuario"){
        cout << "\nCredenciales incorrectas o usuario no encontrado.\n";
    }

    else {
        cout << "\nCredenciales incorrectas o usuario no encontrado.\n";
    }

    delete adminObj;

    return 0;
}

