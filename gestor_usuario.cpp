#include "gestor_usuario.h"
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std ;

int contarLineas(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo);
    int contador = 0;
    char linea[256];

    while (archivo.getline(linea, 256)) {
        contador++;
    }

    archivo.close();
    return contador;
}

void cargarUsuariosDesdeArchivo(const char* nombreArchivo, Usuarios**& arreglo, int& cantidadUsuarios) {
    cantidadUsuarios = contarLineas(nombreArchivo);
    arreglo = new Usuarios*[cantidadUsuarios];

    ifstream archivo(nombreArchivo);
    char linea[256];
    int i = 0;

    while (archivo.getline(linea, 256)) {
        char* token = strtok(linea, ";"); // Documento
        string documento = token;

        token = strtok(NULL, ";"); // Contraseña
        string contrasena = token;

        token = strtok(NULL, ";"); // Nombre
        string nombre = token;

        arreglo[i] = new Usuarios(documento, contrasena, nombre);
        i++;
    }

    archivo.close();

}

void liberarUsuarios(Usuarios** arreglo, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        delete arreglo[i];
    }
    delete[] arreglo;
}
Usuarios* buscarUsuarioEnArchivo(const char* archivo, const string& doc, Usuarios**& arreglo, int& cantidad) {
    cargarUsuariosDesdeArchivo(archivo, arreglo, cantidad);

    for (int i = 0; i < cantidad; i++) {
        if (arreglo[i]->getDocumento() == doc) {
            return arreglo[i];
        }
    }

    // No encontrado: liberar arreglo
    liberarUsuarios(arreglo, cantidad);
    arreglo = nullptr;
    cantidad = 0;
    return nullptr;
}



Usuarios* buscarUsuarioEnArchivo(const char* archivo, const string& doc, Usuarios**& arreglo, int& cantidad, int& posEncontrado) {
    cargarUsuariosDesdeArchivo(archivo, arreglo, cantidad);

    for (int i = 0; i < cantidad; i++) {
        if (arreglo[i]->getDocumento() == doc) {
            posEncontrado = i;
            return arreglo[i];
        }
    }

    liberarUsuarios(arreglo, cantidad);
    arreglo = nullptr;
    cantidad = 0;
    return nullptr;
}

Usuarios* loginDesdeArchivos(const char* archivoAdmins,
                             const char* archivoUsuarios,
                             string& tipoUsuario) {
    string doc, clave;
    cout << "Ingrese su documento: ";
    cin >> doc;

    Usuarios** arreglo = nullptr;
    int cantidad = 0;
    int pos = -1;

    // Buscar en admins
    Usuarios* encontrado = buscarUsuarioEnArchivo(archivoAdmins, doc, arreglo, cantidad, pos);

    if (encontrado != nullptr) {
        tipoUsuario = "admin";
        for (int intentos = 3; intentos > 0; intentos--) {
            cout << "Ingrese su clave: ";
            cin >> clave;
            if (encontrado->getcontrasena() == clave) {
                // Crear copia
                Usuarios* copia = new Usuarios(encontrado->getDocumento(),
                                               encontrado->getcontrasena(),
                                               encontrado->getNombre());
                liberarUsuarios(arreglo, cantidad);
                return copia;
            } else {
                cout << "Clave incorrecta. Intentos restantes: " << intentos - 1 << endl;
            }
        }

        liberarUsuarios(arreglo, cantidad);
        return nullptr;
    }

    // Buscar en usuarios normales
    encontrado = buscarUsuarioEnArchivo(archivoUsuarios, doc, arreglo, cantidad, pos);

    if (encontrado != nullptr) {
        tipoUsuario = "usuario";
        for (int intentos = 3; intentos > 0; intentos--) {
            cout << "Ingrese su clave: ";
            cin >> clave;
            if (encontrado->getcontrasena() == clave) {
                Usuarios* copia = new Usuarios(encontrado->getDocumento(),
                                               encontrado->getcontrasena(),
                                               encontrado->getNombre());
                liberarUsuarios(arreglo, cantidad);
                return copia;
            } else {
                cout << "Clave incorrecta. Intentos restantes: " << intentos - 1 << endl;
            }
        }

        liberarUsuarios(arreglo, cantidad);
        return nullptr;
    }

    tipoUsuario = "ninguno";
    cout << "El usuario no se encuentra registrado." << endl;
    return nullptr;
}
