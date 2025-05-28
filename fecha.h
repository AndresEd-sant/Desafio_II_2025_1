#ifndef FECHA_H
#define FECHA_H

#include <string>
using namespace std;

class fecha {
private:
    unsigned short int dia, mes, anio;

public:
    fecha(unsigned short int d, unsigned short int m, unsigned short int a);

    string formatoCorto() const;
    const char* formatoExtendido();
    bool esValida() const;

    unsigned short int getDia();
    unsigned short int getMes();
    unsigned short int getAnio();

    void sumarDias(int n);
    unsigned int diasHasta(const fecha& otra) const;


    bool operator<(const fecha& otra) const;
    bool operator>(const fecha& otra) const;
    bool operator==(const fecha& otra) const;

    ~fecha();

};

#endif // FECHA_H
