#include <iostream>
#include "administrador.h"
#include "utilidades.h"

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

        //usuario* userObj = nullptr;
        administrador* adminObj = nullptr;
        string tipo = login(adminObj);

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
                    break;
                case 2: {
                    Lugar** lugares = adminObj->getLugares();
                    for (unsigned int i = 0; i < adminObj->getN_lugares(); ++i)
                        cout <<"["<<i+1<<"] "<< lugares[i]->getNombre() << " en " << lugares[i]->getMunicipio() << endl;
                    break;
                }
                case 3:
                    adminObj->verYcancelarReservasActivas("reservas_activas.txt");
                    break;
                case 4:
                    cout << "Cerrando sesion de " << adminObj->getNombre() << ".\n";
                    break;
                default:
                    cout << "Opcion invalida.\n";
                }
            } while (opcion != 4);

            delete adminObj;
        }
        else if (tipo == "usuario"){

            cout << "\nInicio de sesion exitoso como USUARIO\n";
            //cout << "Bienvenido " << userObj->getNombre() << endl;


            unsigned int opcion;
            do {
                menuUsuario();
                cin >> opcion;
                switch (opcion) {
                case 1:
                    cout << "(  )\n";
                    break;
                case 2: {
                    //userObj->verYcancelarReservasActivas("reservas_activas.txt");
                    break;
                }
                case 3:

                    //cout << "Cerrando sesion de " << UserObj->getNombre() << ".\n";

                    break;
                default:
                    cout << "Opcion invalida.\n";
                }
            } while (opcion != 3);

            delete adminObj;

        }

        else {
            cout << "\nCredenciales invalidas o usuario no encontrado.\n";
        }
    }

    return 0;
}
