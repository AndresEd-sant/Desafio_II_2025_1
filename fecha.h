#ifndef FECHA_H
#define FECHA_H

#include <string>
using namespace std;

class fecha {
private:
    unsigned short int dia, mes, anio;

public:
    fecha(unsigned short int d, unsigned short int m, unsigned short int a);
    fecha(const char* formato);
    fecha(const string& formato);

    void cargarDesdeCadena(const char* formato);
    void cargarDesdeCadena(const string& formato);

    void mostrar() const;
    const char* formatoExtendido();

    unsigned short int getDia();
    unsigned short int getMes();
    unsigned short int getAnio();

    void sumarDias(int n); // nuevo

    bool operator<(const fecha& otra) const;
    bool operator>(const fecha& otra) const;
    bool operator==(const fecha& otra) const;
};

#endif // FECHA_H
