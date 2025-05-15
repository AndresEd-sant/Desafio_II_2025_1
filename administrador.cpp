#include "administrador.h"
#include <string>

administrador::administrador(string nombre,string documento,string contrasena, unsigned int n_lugares,float puntuacion){
    Nombre = nombre;
    Documento = documento;
    Contrasena = contrasena;
    N_lugares = n_lugares;
    Puntuacion = puntuacion;
}

string administrador::getNombre(){
    return Nombre;
}
string administrador::getDocumento(){
    return Documento;
}
string administrador::getContrasena(){
    return Contrasena;
}
unsigned int administrador::getN_lugares(){
    return N_lugares;
}
float administrador::getPuntuacion(){
    return Puntuacion;
}
administrador::~administrador(){
}
