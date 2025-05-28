#include <iostream>
#include <fstream>
#include <sstream>
#include "fecha.h"
#include "usuarios.h"
#include "utilidades.h"
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
        iteraciones++;
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
        cout << "Iteraciones realizadas al hacer la reserva: "<<iteraciones<<endl;
        iteraciones =0;
        return;
    }
    unsigned int costoUniLugar = 0;
    string codSeleccionado;

    cout << "\nIngrese el codigo del lugar que desea reservar: ";
    cin >> codSeleccionado;

    fecha* inicio = nullptr;
    fecha* fin = nullptr;

    // Ingreso validado de fechas
    do {
        iteraciones++;
        unsigned short anio, mes, dia;
        cout << "\n=== Ingrese la FECHA DE INICIO ===\n";
        cout << "Anio: "; cin >> anio;
        cout << "Mes: "; cin >> mes;
        cout << "Dia: "; cin >> dia;
        inicio = new fecha(dia, mes, anio);

        if (!inicio->esValida()) {
            cout << " Fecha de inicio inválida. Intente de nuevo.\n";
            delete inicio;
            inicio = nullptr;
        }
    } while (inicio == nullptr);

    do {
        iteraciones++;
        unsigned short anio, mes, dia;
        cout << "\n=== Ingrese la FECHA DE FIN ===\n";
        cout << "Anio: "; cin >> anio;
        cout << "Mes: "; cin >> mes;
        cout << "Dia: "; cin >> dia;
        fin = new fecha(dia, mes, anio);

        if (!fin->esValida()) {
            cout << " Fecha de fin invalida. Intente de nuevo.\n";
            delete fin;
            fin = nullptr;
        }
    } while (fin == nullptr);

    // Validación lógica entre fechas
    if (!(*inicio < *fin)) {
        cout << " La fecha de inicio debe ser anterior a la fecha de fin.\n";
        delete inicio;
        delete fin;
        cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
        iteraciones = 0;
        return;
    }

    ifstream archivoReservas("reservas_activas.txt");
    if (!archivoReservas) {
        cout << "Error al abrir reservas_activas.txt\n";
        delete inicio;
        delete fin;
        cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
        iteraciones = 0;
        return;
    }

    string lineaReserva;
    while (getline(archivoReservas, lineaReserva)) {
        iteraciones++;
        stringstream ss(lineaReserva);
        string codR, cedulaU, nombreU, codL, fInicio, fFin, costoStr;
        getline(ss, codR, ';');
        getline(ss, cedulaU, ';');
        getline(ss, nombreU, ';');
        getline(ss, codL, ';');
        getline(ss, fInicio, ';');
        getline(ss, fFin, ';');
        getline(ss, costoStr, ';');

        if (codL == codSeleccionado || cedulaU == Documento) {
            fecha* reservadaInicio =convertirAFecha(fInicio.c_str());
            fecha* reservadaFin = convertirAFecha(fFin.c_str());

            if (hayConflictoFechas(inicio, fin, reservadaInicio, reservadaFin)) {
                cout << "\n Conflicto de fechas con una reserva existente:\n";
                cout << "Usuario: " << nombreU << ", Lugar: " << codL
                     << " desde " << reservadaInicio->formatoExtendido()
                     << " hasta " << reservadaFin->formatoExtendido() << "\n";
                delete reservadaInicio;
                delete reservadaFin;
                delete inicio;
                delete fin;
                cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
                iteraciones = 0;
                return;
            }
            delete reservadaInicio;
            delete reservadaFin;
        }
    }
    archivoReservas.close();
    unsigned int costoTotal =inicio->diasHasta(*fin)* costoUniLugar;
    string nuevoCodigo = generarCodigoUnico() ;

    ofstream out("reservas_activas.txt", ios::app);
    if (!out) {
        cout << "Error al guardar la reserva.\n";
        delete inicio;
        delete fin;
        cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
        iteraciones = 0;
        return;
    }

    // Guardar usando los métodos de la clase fecha
    out << nuevoCodigo << ";" << Documento << ";" << Nombre << ";" << codSeleccionado << ";"
        << inicio->formatoCorto() << ";" << fin->formatoCorto() << ";" << costoTotal << ";\n";
    out.close();
    guardarComentarioReserva(Nombre, codSeleccionado, inicio, fin);
    cout << "\n Reserva registrada exitosamente.\n";
    cout << " Su reserva esta para el " << inicio->formatoExtendido() << " hasta el "
         << fin->formatoExtendido() << ".\n";

    delete inicio;
    delete fin;
    cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
    iteraciones = 0;
}

void Usuarios::cancelarReserva() {
    ifstream inFile("reservas_activas.txt");
    if (!inFile.is_open()) {
        cout << "No se pudo abrir el archivo de reservas.\n";
        return;
    }

    int capacidad = 10; // capacidad inicial
    int totalIDs = 0;
    string* idsValidos = new string[capacidad];

    string linea;
    bool encontrada = false;

    cout << "\n=== TUS RESERVAS ===\n";
    while (getline(inFile, linea)) {
        iteraciones++;
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

            // Si el arreglo está lleno, ampliar capacidad
            if (totalIDs == capacidad) {
                capacidad *= 2; // duplicar capacidad
                string* temp = new string[capacidad];
                for (int i = 0; i < totalIDs; i++) {
                    temp[i] = idsValidos[i];
                }
                delete[] idsValidos;
                idsValidos = temp;
            }

            idsValidos[totalIDs++] = id;
            encontrada = true;
        }
    }

    if (!encontrada) {
        cout << "No tienes reservas activas para cancelar.\n";
        inFile.close();
        delete[] idsValidos;
        cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
        iteraciones = 0;
        return;
    }

    // Validar ID ingresado
    string idCancel;
    bool valido = false;

    do {
        iteraciones++;
        cout << "\nIngrese el ID de la reserva que desea cancelar: ";
        cin >> idCancel;
        valido = false;
        for (int i = 0; i < totalIDs; i++) {
            iteraciones++;
            if (idsValidos[i] == idCancel) {
                valido = true;
                break;
            }
        }
        if (!valido) cout << " ID invalido. Intenta nuevamente.\n";
    } while (!valido);

    inFile.clear();
    inFile.seekg(0);

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        cout << "No se pudo crear archivo temporal.\n";
        inFile.close();
        delete[] idsValidos;
        cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
        iteraciones = 0;
        return;
    }

    bool eliminada = false;
    while (getline(inFile, linea)) {
        iteraciones++;
        istringstream ss(linea);
        string id, doc;
        getline(ss, id, ';');
        getline(ss, doc, ';');

        if (id == idCancel && doc == Documento) {
            eliminada = true;
            continue;
        }
        tempFile << linea << "\n";
    }

    inFile.close();
    tempFile.close();
    delete[] idsValidos;

    if (eliminada) {
        remove("reservas_activas.txt");
        rename("temp.txt", "reservas_activas.txt");
        cout << " Reserva cancelada exitosamente.\n";
    } else {
        remove("temp.txt");
        cout << " No se encontro la reserva con ese ID.\n";
    }
    cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
    iteraciones = 0;
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
        iteraciones++;
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
    cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
    iteraciones = 0;
}
