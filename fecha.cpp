#include "fecha.h"
#include <cstdio>

fecha::fecha(unsigned short int d, unsigned short int m, unsigned short int a) {
    dia = d;
    mes = m;
    anio = a;
}


unsigned short int fecha::getDia() { return dia; }
unsigned short int fecha::getMes() { return mes; }
unsigned short int fecha::getAnio() { return anio; }

bool fecha::operator<(const fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}

bool fecha::operator>(const fecha& otra) const {
    if (anio != otra.anio) return anio > otra.anio;
    if (mes != otra.mes) return mes > otra.mes;
    return dia > otra.dia;
}

bool fecha::operator==(const fecha& otra) const {
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

void fecha::mostrar() const {
    printf("%04d-%02d-%02d", anio, mes, dia);
}
bool fecha::esValida() const {
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1){
        return false;
    }
    static const int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    int diasEnEsteMes = diasMes[mes - 1];

    if (mes == 2 && bisiesto)
        diasEnEsteMes = 29;

    return dia <= diasEnEsteMes;
}


const char* fecha::formatoExtendido() {
    static const char* diasSemana[] = {"Sabado", "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"};
    static const char* meses[] = {
        "enero", "febrero", "marzo", "abril", "mayo", "junio",
        "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"
    };

    unsigned short int d = dia, m = mes, y = anio;
    if (m < 3) {
        m += 12;
        y -= 1;
    }

    int h = (d + 13*(m+1)/5 + y + y/4 - y/100 + y/400) % 7;

    static char resultado[100];
    snprintf(resultado, sizeof(resultado), "%s, %d de %s del %d",
             diasSemana[h], dia, meses[mes - 1], anio);
    return resultado;
}

void fecha::sumarDias(int n) {
    // Días por mes común
    static const int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    for (int i = 0; i < n; ++i) {
        dia++;

        bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        int diasDelMes = diasMes[mes - 1];
        if (mes == 2 && bisiesto) diasDelMes = 29;

        if (dia > diasDelMes) {
            dia = 1;
            mes++;
            if (mes > 12) {
                mes = 1;
                anio++;
            }
        }
    }
}


