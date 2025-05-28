#include "utilidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "fecha.h"
using namespace std;

int iteraciones =0;
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


string login(administrador*& admin,Usuarios*& user) {
        string documento, contrasena;
        cout << "Ingrese su documento: ";
        cin >> documento;

        // --- Verificar administrador ---
        ifstream archivo("administradores.txt");
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                iteraciones++;
                istringstream ss(linea);
                string doc, pass, nombre, puntuacionStr, numLugaresStr;
                getline(ss, doc, ';'); getline(ss, pass, ';'); getline(ss, nombre, ';');
                getline(ss, puntuacionStr, ';'); getline(ss, numLugaresStr, ';');

                if (doc == documento) {
                    int intentos = 3;
                    while (intentos-- > 0) {
                        iteraciones++;
                        cout << "Ingrese su clave: ";
                        cin >> contrasena;
                        if (contrasena == pass) {
                            archivo.close();
                            admin = new administrador(nombre, doc, pass, stoi(numLugaresStr), stof(puntuacionStr));
                            cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
                            iteraciones = 0;
                            return "admin";
                        } else {
                            cout << "Contrasena incorrecta. Intentos restantes: " << intentos << endl;
                        }
                    }
                    archivo.close();
                    cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
                    iteraciones = 0;
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
                iteraciones++;
                istringstream ss(linea);
                string doc, pass, nombre, antiguedad, puntuacion;
                getline(ss, doc, ';'); getline(ss, pass, ';'); getline(ss, nombre, ';');
                getline(ss, antiguedad, ';'); getline(ss, puntuacion, ';');

                if (doc == documento) {
                    int intentos = 3;
                    while (intentos-- > 0) {
                        iteraciones++;
                        cout << "Ingrese su clave: ";
                        cin >> contrasena;
                        if (contrasena == pass) {
                            user = new Usuarios(doc, pass, nombre, antiguedad);
                            archivo.close();
                            cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
                            iteraciones = 0;
                            return "user";
                        } else {
                            cout << "Contrasena incorrecta. Intentos restantes: " << intentos << endl;
                        }
                    }
                    archivo.close();
                    cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
                    iteraciones = 0;
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
    for (; i < 4; ++i){
        iteraciones++;
        buffer[j++] = strFecha[i];
    }
    buffer[j] = '\0';
    anio = atoi(buffer);

    j = 0;
    i++; // saltar el guion

    // Mes (2 caracteres)
    for (; i < 7; ++i){
        iteraciones++;
        buffer[j++] = strFecha[i];
    }
    buffer[j] = '\0';
    mes = atoi(buffer);

    j = 0;
    i++; // saltar el guion

    // Día (2 caracteres)
    for (; i < 10; ++i){
        iteraciones++;
        buffer[j++] = strFecha[i];
    }
    buffer[j] = '\0';
    dia = atoi(buffer);

    cout << "Iteraciones Realizadas en el metodo convertirAfecha: "<<iteraciones<<endl;
    iteraciones = 0;
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
        iteraciones++;
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
    cout << "Iteraciones Realizadas en metodo generarCodigoUnico: "<<iteraciones<<endl;
    iteraciones = 0;
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
        iteraciones++;
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
            cout << "Iteraciones Realizadas en metodo ObtenerCostolugar: "<<iteraciones<<endl;
            iteraciones = 0;
            return atoi(costoStr.c_str());
        }
    }

    archivo.close();
    cout << "Iteraciones Realizadas en metodo ObtenerCodigolugar: "<<iteraciones<<endl;
    iteraciones = 0;
    return 0;
}
void guardarComentarioReserva(const string& nombreUsuario, const string& codLugar, const fecha* inicio, const fecha* fin) {
    char opcion;
    cout << "\n  Desea dejar un comentario sobre esta reserva ? (s/n): ";
    cin >> opcion;
    cin.ignore(); // Limpiar salto de línea

    if (opcion == 's' || opcion == 'S') {
        string comentario;
        cout << "Ingrese su comentario (maximo 1000 caracteres) : \n";
        getline(cin, comentario);

        while (comentario.length() > 1000) {
            iteraciones++;
            cout << "El comentario excede los 1000 caracteres. Intente nuevamente:\n";
            getline(cin, comentario);
        }

        ofstream out("comentarios.txt", ios::app);
        if (!out) {
            cout << "Error al guardar el comentario.\n";
            cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
            iteraciones = 0;
            return;

        }

        out << nombreUsuario << ";" << codLugar << ";"
            << inicio->formatoCorto() << ";" << fin->formatoCorto() << ";"
            << comentario << "\n";

        out.close();
        cout << "Comentario guardado correctamente.\n";
    }
    cout << "Iteraciones Realizadas en metodo guardarComentarioReserva: "<<iteraciones<<endl;
    iteraciones = 0;
}
