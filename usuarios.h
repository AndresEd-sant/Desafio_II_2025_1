#ifndef USUARIOS_H
#define USUARIOS_H
#include <iostream>
#include <string>
using namespace std;

class Usuarios {
private:
    string Documento;
    string Contrasena;
    string Nombre;
    string Antiguedad;
    string Calificacion;

public:
    Usuarios(string documento, string contrasena, string nombre ,string Antiguedad);

    string getDocumento();
    string getNombre();
    string getContrasena();
    string getAntiguedad();
    void cancelarReserva();
    void hacerReserva();
    void verReservas();

    ~Usuarios();
};

#endif // USUARIOS_H
