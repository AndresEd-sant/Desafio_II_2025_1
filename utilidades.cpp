#include "utilidades.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void menuAdministrador() {
    cout << "\n=== MENU ADMINISTRADOR ===\n";
    cout << "1. Cambio de Dia\n";
    cout << "2. Consultar Huespedes\n";
    cout << "3. Salir\n";
}

void menuPrincipal() {
    cout << "Bienvenido a UdeAStay\n";
    cout << "1. Login\n2. Salir\n";
}

void menuUsuario() {
    cout << "\n=== MENU HUÉSPED ===\n";
    cout << "1. Hacer reservacion\n";
    cout << "2. Consultar reservaciones\n";
    cout << "3. Cancelacion de reservas\n";
    cout << "4. Salir\n";
}

string login(Usuarios*& usuario) {
    string documento, contrasena;
    cout << "Ingrese su documento: ";
    cin >> documento;

    // --- Verificar administrador ---
    ifstream archivo("administradores.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string doc, pass, nombre, puntuacionStr, numLugaresStr;
            getline(ss, doc, ';'); getline(ss, pass, ';'); getline(ss, nombre, ';');
            getline(ss, puntuacionStr, ';'); getline(ss, numLugaresStr, ';');

            if (doc == documento) {
                int intentos = 3;
                while (intentos-- > 0) {
                    cout << "Ingrese su clave: ";
                    cin >> contrasena;
                    if (contrasena == pass) {
                        archivo.close();
                        // return "admin";
                        // adminObj = new Administrador(nombre, doc, pass, stoi(numLugaresStr), stof(puntuacionStr));
                        return "admin"; // dejar activo si más adelante lo necesitas
                    } else {
                        cout << "Contrasena incorrecta. Intentos restantes: " << intentos << endl;
                    }
                }
                archivo.close();
                return "0";
            }
        }
        archivo.close();
    }

    // --- Verificar usuario ---
    archivo.open("usuarios.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string doc, pass, nombre, antiguedad, puntuacion;
            getline(ss, doc, ';'); getline(ss, pass, ';'); getline(ss, nombre, ';');
            getline(ss, antiguedad, ';'); getline(ss, puntuacion, ';');

            if (doc == documento) {
                int intentos = 3;
                while (intentos-- > 0) {
                    cout << "Ingrese su clave: ";
                    cin >> contrasena;
                    if (contrasena == pass) {
                        usuario = new Usuarios(doc, pass, nombre, antiguedad);
                        archivo.close();
                        return "user";
                    } else {
                        cout << "Contrasena incorrecta. Intentos restantes: " << intentos << endl;
                    }
                }
                archivo.close();
                return "0";
            }
        }
        archivo.close();
    }

    return "0";
}

