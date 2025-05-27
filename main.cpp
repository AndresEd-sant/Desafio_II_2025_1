#include <iostream>
#include <string>
#include "usuarios.h"
#include "utilidades.h"
#include "lugar.h"

using namespace std;

int main() {
    while (true) {
        unsigned short int selec = 0;

        do {
            menuPrincipal();
            cin >> selec;
        } while (selec != 1 && selec != 2);

        if (selec == 2) {
            cout << "Saliendo del sistema. Hasta luego\n";
            break;
        }

        Usuarios* usuario = nullptr;
        string tipo = login(usuario);

        if (tipo == "admin") {
            cout << "\nInicio de sesion exitoso como ADMINISTRADOR\n";
            // cout << "Bienvenido " << adminObj->getNombre() << endl;
            // adminObj->cargarLugaresDesdeArchivo("lugares.txt");

            unsigned int opcion;
            do {
                menuAdministrador();
                cin >> opcion;
                switch (opcion) {
                case 1:
                    cout << "(Simulacion de cambio de día no implementada aun)\n";
                    break;
                case 2: {
                    // Lugar** lugares = adminObj->getLugares();
                    // for (unsigned int i = 0; i < adminObj->getN_lugares(); ++i)
                    //     cout << lugares[i]->getNombre() << " en " << lugares[i]->getMunicipio() << endl;
                    break;
                }
                case 3:
                    // adminObj->verYcancelarReservasActivas("reservas_activas.txt");
                    break;
                case 4:
                    // cout << "Cerrando sesión de " << adminObj->getNombre() << ".\n";
                    break;
                default:
                    cout << "Opcion invalida.\n";
                }
            } while (opcion != 4);

            // delete adminObj;

        } else if (tipo == "user") {
            cout << "\nInicio de sesion exitoso como USUARIO\n";
            cout << "Bienvenido, " << usuario->getNombre() << endl;

            unsigned int opcion;
            do {
                menuUsuario();
                cin >> opcion;
                switch (opcion) {
                case 1:
                    usuario->hacerReserva();
                    break;
                case 2:
                    usuario->verReservas();
                    break;
                case 3:
                    usuario->cancelarReserva();
                    break;
                case 4:
                    cout << "Cerrando sesión de " << usuario->getNombre() << ".\n";
                    break;
                default:
                    cout << "Opción inválida.\n";
                }
            } while (opcion != 4);

            delete usuario;

        } else {
            cout << "\nCredenciales invalidas o usuario no encontrado.\n";
        }
    }

    return 0;
}
