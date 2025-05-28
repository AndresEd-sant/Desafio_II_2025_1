#ifndef UTILIDADES_H
#define UTILIDADES_H
#include "fecha.h"
#include "usuarios.h"
#include "administrador.h"
using namespace std;
void menuPrincipal();
void menuAdministrador();
void menuUsuario();
string login(administrador*& admin, Usuarios*& user);
fecha* convertirAFecha(const char* strFecha);
bool hayConflictoFechas(fecha* nuevaInicio, fecha* nuevaFin, fecha* existenteInicio, fecha* existenteFin);
string generarCodigoUnico();
unsigned int obtenerCostoLugar(const string& codigoLugar);
void guardarComentarioReserva(const string& nombreUsuario, const string& codLugar,
                              const fecha* inicio, const fecha* fin);

#endif
