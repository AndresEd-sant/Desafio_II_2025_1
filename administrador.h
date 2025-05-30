#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <string>
#include "lugar.h"

using namespace std;

class administrador {
private:
    string Nombre;
    string Documento;
    string Contrasena;
    unsigned int N_lugares;
    float Puntuacion;
    Lugar** lugares;
    int iteraciones=0;

public:
    administrador(string nombre, string documento, string contrasena,
                  unsigned int n_lugares, float puntuacion);
    void actualizarHistorico(const string& archivoReservas, const string& archivoHistorico);
    string getDocumento();
    string getNombre();
    unsigned int getN_lugares();
    Lugar** getLugares();
    void cargarLugaresDesdeArchivo(const string& nombreArchivo);
    void verYcancelarReservasActivas(const string& archivoReservas);
    ~administrador();
};

#endif
