#ifndef USUARIOS_H
#define USUARIOS_H
#include <iostream>
#include <string>
using namespace std;

class Usuarios {
private:
    string Documento;
    string Nombre;
    string Contrasena;
    string Antiguedad;
    string Calificacion;
    string* ReservasT; // Arreglo dinámico de strings (reservas)
    unsigned int N_reservaciones;

public:
    Usuarios(string documento, string contrasena, string nombre ,string Antiguedad);

    string getDocumento();
    string getNombre();
    string getContrasena();
    string getAntiguedad();
    unsigned int getN_reservaciones();
    void cancelarReserva();
    void hacerReserva();
    void verReservas();

    ~Usuarios();
};

#endif // USUARIOS_H
