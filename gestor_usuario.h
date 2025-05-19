#ifndef GESTOR_USUARIOS_H
#define GESTOR_USUARIOS_H

#include "usuarios.h"

// Cuenta cuántas líneas hay en el archivo (una por usuario)
int contarLineas(const char* nombreArchivo);

// Carga usuarios desde el archivo, reserva el arreglo dinámicamente y actualiza el puntero y la cantidad
void cargarUsuariosDesdeArchivo(const char* nombreArchivo, Usuarios**& arreglo, int& cantidadUsuarios);

// Libera memoria del arreglo de punteros a Usuarios

void liberarUsuarios(Usuarios** arreglo, int cantidad);

Usuarios* buscarUsuarioEnArchivo(const char* archivo, const string& doc,
                            Usuarios**& arreglo, int& cantidad);

Usuarios* loginDesdeArchivos(const char* archivoAdmins,
                             const char* archivoUsuarios,
                             std::string& tipoUsuario);





#endif // GESTOR_USUARIOS_H
