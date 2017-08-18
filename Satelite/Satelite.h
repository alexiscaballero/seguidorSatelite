#ifndef Satelite_h
#define Satelite_h
#include "Arduino.h"
#include "Plan13.h"

class Satelite {
    public:
	Satelite();
        void iniciarSatelite(double longitud, double latitud, int alturaSobreElMar);
        void calcularPosicion(double posicion[],int fecha[]);
	boolean esVisibleSatelite(int fecha[]);
	boolean sateliteCerca(int fecha[]);
    private:
        double EL, AZ;
        Plan13 p13;
        double posicion[];
	int fecha[];
};

#endif