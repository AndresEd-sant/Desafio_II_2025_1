#include "utilidades.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "fecha.h"
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
    cout << "\n=== MENU HUESPED ===\n";
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

fecha* convertirAFecha(const char* strFecha) {
    unsigned int anio = 0, mes = 0, dia = 0;
    int i = 0, j = 0;
    char buffer[5];

    // Año (4 caracteres)
    for (; i < 4; ++i)
        buffer[j++] = strFecha[i];
    buffer[j] = '\0';
    anio = atoi(buffer);

    j = 0;
    i++; // saltar el guion

    // Mes (2 caracteres)
    for (; i < 7; ++i)
        buffer[j++] = strFecha[i];
    buffer[j] = '\0';
    mes = atoi(buffer);

    j = 0;
    i++; // saltar el guion

    // Día (2 caracteres)
    for (; i < 10; ++i)
        buffer[j++] = strFecha[i];
    buffer[j] = '\0';
    dia = atoi(buffer);

    return new fecha(dia,mes,anio);
}
bool hayConflictoFechas(fecha* nuevaInicio, fecha* nuevaFin, fecha* existenteInicio, fecha* existenteFin) {
    return !( *nuevaFin < *existenteInicio || *existenteFin < *nuevaInicio );
}
string generarCodigoUnico() {
    ifstream archivo("reservas_activas.txt");
    int maxNum = 0;
    string linea;

    while (getline(archivo, linea)) {
        if (linea.length() >= 2 && linea[0] == 'R') {
            // Leer desde R hasta el primer ';'
            size_t  posPuntoYComa = linea.find(';');
            if (posPuntoYComa != string::npos) {
                string numStr = linea.substr(1, posPuntoYComa - 1);
                int num = atoi(numStr.c_str());
                if (num > maxNum) maxNum = num;
            }
        }
    }
    archivo.close();

    int nuevoNum = maxNum + 1;
    return "R" + to_string(nuevoNum);
}
unsigned int obtenerCostoLugar(const string& codSeleccionado) {
    ifstream archivo("lugares.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de lugares.\n";
        return 0;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string cod, nombre, departamento, ciudad, tipo, costoStr, cedula, puntuacion;

        getline(ss, cod, ';');
        getline(ss, nombre, ';');
        getline(ss, departamento, ';');
        getline(ss, ciudad, ';');
        getline(ss, tipo, ';');
        getline(ss, costoStr, ';');
        getline(ss, cedula, ';');
        getline(ss, puntuacion, ';');

        if (cod == codSeleccionado) {
            archivo.close();
            return atoi(costoStr.c_str());
        }
    }

    archivo.close();
    return 0;
}
void guardarComentarioReserva(const string& nombreUsuario, const string& codLugar, const fecha* inicio, const fecha* fin) {
    char opcion;
    cout << "\n  Desea dejar un comentario sobre esta reserva ? (s/n): ";
    cin >> opcion;
    cin.ignore(); // Limpiar salto de línea

    if (opcion == 's' || opcion == 'S') {
        string comentario;
        cout << "Ingrese su comentario (maximo 1000 caracteres) :\n";
        getline(cin, comentario);

        while (comentario.length() > 1000) {
            cout << "El comentario excede los 1000 caracteres. Intente nuevamente:\n";
            getline(cin, comentario);
        }

        ofstream out("comentarios.txt", ios::app);
        if (!out) {
            cout << "Error al guardar el comentario.\n";
            return;
        }

        out << nombreUsuario << ";" << codLugar << ";"
            << inicio->formatoCorto() << ";" << fin->formatoCorto() << ";"
            << comentario << "\n";

        out.close();
        cout << "Comentario guardado correctamente.\n";
    }
}
