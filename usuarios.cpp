#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "fecha.h"
using namespace std;

Usuarios::Usuarios(string documento, string contrasena, string nombre, string antiguedad)
    : Documento(documento), Contrasena(contrasena), Nombre(nombre), Antiguedad(antiguedad) {}

Usuarios::~Usuarios() {}

// Getters
string Usuarios::getDocumento() { return Documento; }
string Usuarios::getNombre() { return Nombre; }
string Usuarios::getContrasena() { return Contrasena; }

void Usuarios::hacerReserva() {
    ifstream archivoLugares("lugares.txt");
    if (!archivoLugares) {
        cout << "Error al abrir lugares.txt\n";
        return;
    }

    int criterio = 0;
    cout << "\n----Desea aplicar un filtro?----\n";
    cout << "1. Filtrar por puntuacion minima\n";
    cout << "2. Filtrar por costo maximo por noche\n";
    cout << "0. No aplicar filtros\n";
    cout << "Seleccione una opcion: ";
    cin >> criterio;

    float filtroPuntuacion = 0.0f;
    int filtroCosto = 0;

    if (criterio == 1) {
        cout << "Ingrese la puntuación minima (0.0 a 5.0): ";
        cin >> filtroPuntuacion;
    } else if (criterio == 2) {
        cout << "Ingrese el costo maximo por noche: ";
        cin >> filtroCosto;
    }

    cout << "\n--- LUGARES DISPONIBLES ---\n";
    string linea, codLugar, nombreLugar, depto, municipio, tipo;
    int costo;
    string contacto;
    float puntuacion;
    bool seMostroAlMenosUno = false;

    while (getline(archivoLugares, linea)) {
        stringstream ss(linea);
        getline(ss, codLugar, ';');
        getline(ss, nombreLugar, ';');
        getline(ss, depto, ';');
        getline(ss, municipio, ';');
        getline(ss, tipo, ';');
        ss >> costo;
        ss.ignore();
        getline(ss, contacto, ';');
        ss >> puntuacion;
        ss.ignore();

        bool mostrar = true;
        if (criterio == 1 && puntuacion < filtroPuntuacion) {
            mostrar = false;
        } else if (criterio == 2 && costo > filtroCosto) {
            mostrar = false;
        }

        if (mostrar) {
            seMostroAlMenosUno = true;
            cout << "Codigo: " << codLugar << " | Nombre: " << nombreLugar << " | " << tipo
                 << " en " << municipio << ", " << depto << " | $" << costo
                 << " por noche | Puntuacion: " << puntuacion << "\n";
        }
    }
    archivoLugares.close();

    if (!seMostroAlMenosUno) {
        cout << "\nNo se encontraron lugares con los filtros seleccionados.\n";
        return;
    }

    cout << "\nIngrese el código del lugar que desea reservar: ";
    string codSeleccionado;
    cin >> codSeleccionado;

    unsigned short anioInicio, mesInicio, diaInicio;
    unsigned short anioFin, mesFin, diaFin;

    cout << "\n=== Ingrese la FECHA DE INICIO ===\n";
    cout << "Anio: ";
    cin >> anioInicio;
    cout << "Mes: ";
    cin >> mesInicio;
    cout << "Dia: ";
    cin >> diaInicio;

    fecha inicio(anioInicio, mesInicio, diaInicio);

    cout << "\n=== Ingrese la FECHA DE FIN ===\n";
    cout << "Anio: ";
    cin >> anioFin;
    cout << "Mes: ";
    cin >> mesFin;
    cout << "Dia: ";
    cin >> diaFin;

    fecha fin(anioFin, mesFin, diaFin);

    // Validaciones
    if (!inicio.esValida() || !fin.esValida()) {
        cout << "Una o ambas fechas ingresadas no son válidas.\n";
        return;
    }

    if (!(inicio < fin)) {
        cout << "La fecha de inicio debe ser anterior a la fecha de fin.\n";
        return;
    }

    ifstream archivoReservas("reservas_activas.txt");
    if (!archivoReservas) {
        cout << "Error al abrir reservas_activas.txt\n";
        return;
    }

    string lineaReserva;
    while (getline(archivoReservas, lineaReserva)) {
        stringstream ss(lineaReserva);
        string codR, cedulaU, nombreU, codL, fInicio, fFin, costoStr;
        getline(ss, codR, ';');
        getline(ss, cedulaU, ';');
        getline(ss, nombreU, ';');
        getline(ss, codL, ';');
        getline(ss, fInicio, ';');
        getline(ss, fFin, ';');
        getline(ss, costoStr, ';');

        // Verificar conflicto fechas
        if (codL == codSeleccionado) {
           // if (!((fechaFin < fInicio) || (fechaInicio > fFin))) {
               // cout << "\nEl lugar seleccionado ya tiene una reserva en esas fechas.\n";
               // return;
           // }
        }
    }
    archivoReservas.close();

    // Calcular costoTotal - ejemplo simplificado 
    int costoTotal = 100000;

    // Generar código reserva sencillo
    string nuevoCodigo = "R" + Documento.substr(Documento.length() - 3) + "01";

    ofstream out("reservas_activas.txt", ios::app);
    if (!out) {
        cout << "Error al guardar la reserva.\n";
        return;
    }

    out << nuevoCodigo << ";" << Documento << ";" << Nombre << ";" << codSeleccionado << ";"
        << inicio.getAnio() << ";" << fin.getAnio()<< ";" << costoTotal << ";\n";
    out.close();

    cout << "\nReserva registrada exitosamente.\n";
}

void Usuarios::verReservas() {
    ifstream inFile("reservas_activas.txt");
    if (!inFile.is_open()) {
        cout << "No se pudo abrir el archivo de reservas.\n";
        return;
    }

    string linea;
    bool encontrada = false;
    cout << "\n=== TUS RESERVAS ===\n";
    while (getline(inFile, linea)) {
        istringstream ss(linea);
        string id, doc, nombreU, codLugar, fechaIni, fechaFin, precio;
        getline(ss, id, ';');
        getline(ss, doc, ';');
        getline(ss, nombreU, ';');
        getline(ss, codLugar, ';');
        getline(ss, fechaIni, ';');
        getline(ss, fechaFin, ';');
        getline(ss, precio, ';');

        if (doc == Documento) {
            cout << "ID: " << id << " | Lugar: " << codLugar
                 << " | Fecha: " << fechaIni << " a " << fechaFin
                 << " | Precio: $" << precio << "\n";
            encontrada = true;
        }
    }

    if (!encontrada) {
        cout << "No tienes reservas activas.\n";
    }

    inFile.close();
}

