#ifndef LUGAR_H
#define LUGAR_H

#include <string>
using namespace std;

class Lugar {
private:
    string codigo;
    string nombre;
    string departamento;
    string municipio;
    string tipo; // "Casa" o "Apartamento"
    float precioNoche;
    string documentoAdmin; // vínculo al dueño (administrador)

public:
    Lugar(string codigo, string nombre, string departamento, string municipio,
          string tipo, float precioNoche, string documentoAdmin);

    string getCodigo();
    string getNombre();
    string getDepartamento();
    string getMunicipio();
    string getTipo();
    float getPrecioNoche();
    string getDocumentoAdmin();

    ~Lugar();
};

#endif // LUGAR_H
