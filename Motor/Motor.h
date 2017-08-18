#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor {
    public:
        Motor();
        void moverAbajo(double ELSatelite);
        void moverArriba(double ELSatelite);
        void moverDerecha(double AZSatelite);
        void moverIzquierda(double AZSatelite);
	void moverMotor(double posicion[]);
	double posicionElevacion();
	double posicionAzimuth();
	double map_double(double x, double in_min, double in_max, double out_min, double out_max);
    private:
	double angulosAMover,ELSatelite,AZSatelite;
	double posicion[];
	double x,in_min,in_max,out_min,out_max;
};

#endif