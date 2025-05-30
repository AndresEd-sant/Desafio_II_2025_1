#include "administrador.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "fecha.h"

administrador::administrador(string nombre, string documento, string contrasena,
                             unsigned int n_lugares, float puntuacion)
    : Nombre(nombre),
    Documento(documento),
    Contrasena(contrasena),
    N_lugares(n_lugares),
    Puntuacion(puntuacion)
{
    lugares = new Lugar*[N_lugares];
}

string administrador::getDocumento() {
    return Documento;
}

string administrador::getNombre() {
    return Nombre;
}

unsigned int administrador::getN_lugares() {
    return N_lugares;
}

Lugar** administrador::getLugares() {
    return lugares;
}

// Aquí se cargan en memoria dinamica solo los lugares que pertenecen al administrador actual
void administrador::cargarLugaresDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo de lugares.\n";
        return;
    }

    string linea;
    unsigned int index = 0;

    while (getline(archivo, linea) && index < N_lugares) {
        iteraciones++;
        stringstream ss(linea);
        string codigo, nombre, departamento, municipio, tipo, precioStr, docAdmin, puntuacionStr;
        iteraciones++;
        getline(ss, codigo, ';');
        getline(ss, nombre, ';');
        getline(ss, departamento, ';');
        getline(ss, municipio, ';');
        getline(ss, tipo, ';');
        getline(ss, precioStr, ';');
        getline(ss, docAdmin, ';');
        getline(ss, puntuacionStr, ';');

        if (docAdmin == Documento) {
            float precio = stof(precioStr);
            float puntuacion = stof(puntuacionStr);
            lugares[index++] = new Lugar(codigo, nombre, departamento, municipio, tipo, precio, docAdmin, puntuacion);
        }
    }

    archivo.close();
    cout<<endl << "Iteraciones para cargar los lugares de este administrador: "<<iteraciones<<endl;
    iteraciones = 0;
}

void administrador::verYcancelarReservasActivas(const string& archivoReservas) {
    ifstream archivo(archivoReservas);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de reservas activas.\n";
        return;
    }

    // Paso 1: Contar cuántas reservas son del administrador
    unsigned int reservasAdmin = 0;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string codRes, doc, nombreH, idLugar;
        getline(ss, codRes, ';');
        getline(ss, doc, ';');
        getline(ss, nombreH, ';');
        getline(ss, idLugar, ';');

        for (unsigned int i = 0; i < N_lugares; ++i) {
            iteraciones++;
            if (lugares[i]->getCodigo() == idLugar) {
                reservasAdmin++;
                break;
            }
        }
    }
    archivo.close();

    if (reservasAdmin == 0) {
        cout << "\nNo hay reservas activas para tus alojamientos actualmente.\n";
        cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
        iteraciones = 0;
        return;
    }

    // Paso 2: Cargar esas reservas en memoria
    archivo.open(archivoReservas);
    string** reservas = new string*[reservasAdmin];
    unsigned int index = 0;
    while (getline(archivo, linea)) {
        iteraciones++;
        stringstream ss(linea);
        string codRes, doc, nombreH, idLugar, fechaIni, fechaFin, costo;

        getline(ss, codRes, ';');
        getline(ss, doc, ';');
        getline(ss, nombreH, ';');
        getline(ss, idLugar, ';');
        getline(ss, fechaIni, ';');
        getline(ss, fechaFin, ';');
        getline(ss, costo, ';');

        for (unsigned int i = 0; i < N_lugares; ++i) {
            iteraciones++;
            if (lugares[i]->getCodigo() == idLugar) {
                reservas[index] = new string[7];
                reservas[index][0] = codRes;
                reservas[index][1] = doc;
                reservas[index][2] = nombreH;
                reservas[index][3] = idLugar;
                reservas[index][4] = fechaIni;
                reservas[index][5] = fechaFin;
                reservas[index][6] = costo;

                index++;
                break;
            }
        }
    }
    archivo.close();


    // Paso 3: Mostrar reservas
    for (unsigned int i = 0; i < reservasAdmin; ++i) {
        string nombreLugar = "Desconocido";
        for (unsigned int j = 0; j < N_lugares; ++j) {
            iteraciones++;
            if (lugares[j]->getCodigo() == reservas[i][3]) {
                nombreLugar = lugares[j]->getNombre();
                break;
            }
        }
        iteraciones++;
        cout << "\n[" << i + 1 << "] Reserva " << reservas[i][0] << ": " << reservas[i][2]
             << " | Lugar: " << nombreLugar
             << " | Fechas: " << reservas[i][4] << " -> " << reservas[i][5]
             << " | Costo: $" << reservas[i][6] << endl;
    }

    // Paso 4: Preguntar si desea cancelar
    cout << "\nDeseas cancelar alguna reserva (1 = Si, 0 = No): ";
    string opcion;
    cin >> opcion;

    if (opcion == "1") {
        cout << "Selecciona el numero de la reserva a cancelar: ";
        unsigned int num;
        cin >> num;

        if (num >= 1 && num <= reservasAdmin) {
            string codigoAEliminar = reservas[num - 1][0];
            cout << codigoAEliminar <<endl;

            // Paso 5: Reescribir archivo excluyendo esa reserva
            ifstream entrada(archivoReservas);
            ofstream salida("temp.txt");

            string tempLinea;
            while (getline(entrada, tempLinea)) {
                iteraciones++;
                if (tempLinea.substr(0, codigoAEliminar.length()) != codigoAEliminar) {
                    salida << tempLinea << endl;
                }
            }

            entrada.close();
            salida.close();

            remove(archivoReservas.c_str());
            rename("temp.txt", archivoReservas.c_str());

            cout << "Reserva cancelada exitosamente.\n";
        } else {
            cout << "Opcion invalida.\n";
        }

    }

    for (unsigned int i = 0; i < reservasAdmin; ++i)
    {
        iteraciones++;
        delete[] reservas[i];
    }
    delete[] reservas;
    cout << "Iteraciones Realizadas en este metodo: "<<iteraciones<<endl;
    iteraciones = 0;
}


void administrador::actualizarHistorico(const string& archivoReservas, const string& archivoHistorico) {
    cout << "Ingrese la fecha de corte (formato YYYY-MM-DD): ";
    unsigned short int dia, mes, anio;
    cout << "\n Ingrese el anio: ";
    cin >> anio;
    cout << "\n Ingrese el mes: ";
    cin >> mes;
    cout << "\n Ingrese el Dia: ";
    cin >> dia;

    fecha fechaCorte(anio, mes, dia);

    ifstream entrada(archivoReservas);
    ofstream historico(archivoHistorico, ios::app);
    ofstream temporal("temp.txt");

    if (!entrada.is_open() || !historico.is_open() || !temporal.is_open()) {
        cout << "Error abriendo los archivos.\n";
        return;
    }

    string linea;
    int movidas = 0;


    while (getline(entrada, linea)) {

        iteraciones++;
        // Separar los 7 campos usando posiciones y substrings
        int indices[7];
        int count = 0;

        for (int i = 0; i < linea.length() && count < 7; ++i) {
            iteraciones++;
            if (linea[i] == ';') {
                indices[count++] = i;
            }
        }

        // Si no tiene 7 campos, se omite
        if (count < 6) continue;

        // Extraer campo[5] que es la fechaFinal (delimitado por índices)
        string fechaFinal = linea.substr(indices[4] + 1, indices[5] - indices[4] - 1);

        // Extraer año, mes, día manualmente
        unsigned short int fa, fm, fd;
        int pos1 = fechaFinal.find('-');
        int pos2 = fechaFinal.find('-', pos1 + 1);

        fa = stoi(fechaFinal.substr(0, pos1));
        fm = stoi(fechaFinal.substr(pos1 + 1, pos2 - pos1 - 1));
        fd = stoi(fechaFinal.substr(pos2 + 1));

        if (fa < anio || (fa == anio && fm < mes) || (fa == anio && fm == mes && fd < dia)) {
            historico << linea << endl;
            movidas++;
        } else {
            temporal << linea << endl;
        }
    }

    entrada.close();
    historico.close();
    temporal.close();

    remove(archivoReservas.c_str());
    rename("temp.txt", archivoReservas.c_str());

    cout << "Histórico actualizado exitosamente. " << movidas << " reservas movidas.\n";
    cout << "Iteraciones realizadas en este metodo: "<<iteraciones<<endl;
}


administrador::~administrador() {
    for (unsigned int i = 0; i < N_lugares; ++i) {
        delete lugares[i];
    }
    delete[] lugares;
}
