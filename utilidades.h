#ifndef UTILIDADES_H
#define UTILIDADES_H
#include <iostream>
#include "fecha.h"
using namespace std;

#include "usuarios.h"
void menuPrincipal();
void menuAdministrador();
void menuUsuario();
string login( Usuarios*& usuario);
fecha* convertirAFecha(const char* strFecha);
bool hayConflictoFechas(fecha* nuevaInicio, fecha* nuevaFin, fecha* existenteInicio, fecha* existenteFin);
string generarCodigoUnico();
unsigned int obtenerCostoLugar(const string& codigoLugar);
void guardarComentarioReserva(const string& nombreUsuario, const string& codLugar,
                              const fecha* inicio, const fecha* fin);

#endif
