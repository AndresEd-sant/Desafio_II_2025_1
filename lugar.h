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
    float puntuacion;

public:
    Lugar(string codigo, string nombre, string departamento, string municipio,
          string tipo, float precioNoche, string documentoAdmin, float puntuacion);

    string getCodigo();
    string getNombre();
    string getDepartamento();
    string getMunicipio();
    string getTipo();
    float getPrecioNoche();
    string getDocumentoAdmin();
    float getPuntuacion();

    ~Lugar();
};

#endif // LUGAR_H
