#include <iostream>
#include "administrador.h"
#include "usuarios.h"
#include "utilidades.h"

using namespace std;

int iteracionesMain = 0;

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

        Usuarios* userObj = nullptr;
        administrador* adminObj = nullptr;
        string tipo = login(adminObj, userObj);

        if (tipo == "admin") {
            cout << "\nInicio de sesion exitoso como ADMINISTRADOR\n";
            cout << "Bienvenido " << adminObj->getNombre() << endl;
            adminObj->cargarLugaresDesdeArchivo("lugares.txt");

            unsigned int opcion;
            do {
                menuAdministrador();
                cin >> opcion;

                switch (opcion) {
                case 1:
                    adminObj->actualizarHistorico("reservas_activas.txt", "historico.txt");
                    iteracionesMain++;
                    break;

                case 2: {
                    Lugar** lugares = adminObj->getLugares();
                    for (unsigned int i = 0; i < adminObj->getN_lugares(); ++i) {
                        cout << "[" << i + 1 << "] " << lugares[i]->getNombre()
                        << " en " << lugares[i]->getMunicipio() << endl;
                        iteracionesMain++;
                    }
                    cout << "Iteraciones realizadas en esta opcion: " << iteracionesMain << endl;
                    iteracionesMain = 0;
                    break;
                }

                case 3:
                    adminObj->verYcancelarReservasActivas("reservas_activas.txt");
                    iteracionesMain++;
                    break;

                case 4:
                    cout << "Cerrando sesion de " << adminObj->getNombre() << ".\n";
                    break;

                default:
                    cout << "Opcion invalida.\n";
                    iteracionesMain++;
                }

            } while (opcion != 4);

            delete adminObj;
        }

        else if (tipo == "user") {
            cout << "\nInicio de sesion exitoso como USUARIO\n";
            cout << "Bienvenido, " << userObj->getNombre() << endl;

            unsigned int opcion;
            do {
                menuUsuario();
                cin >> opcion;
                switch (opcion) {
                case 1:
                    userObj->hacerReserva();
                    break;
                case 2:
                    userObj->verReservas();
                    break;
                case 3:
                    userObj->cancelarReserva();
                    break;
                case 4:
                    cout << "Cerrando sesion de " << userObj->getNombre() << ".\n";
                    break;
                default:
                    cout << "Opcion invalida.\n";
                }
            } while (opcion != 4);

            delete userObj;
        }

        else {
            cout << "\nCredenciales invalidas o usuario no encontrado.\n";
        }
    }

    return 0;
}
