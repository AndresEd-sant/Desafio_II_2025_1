#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <string>
using namespace std;

class administrador {
private:
    string Nombre;
    string Documento;
    string Contrasena;
    unsigned int N_lugares;
    float Puntuacion;
    string* lugares;

public:
    administrador(string nombre, string documento, string contrasena, unsigned int n_lugares, float puntuacion);
    string getNombre();
    string getDocumento();
    string getContrasena();
    unsigned int getN_lugares();
    float getPuntuacion();
    ~administrador();
};

#endif // ADMINISTRADOR_H
