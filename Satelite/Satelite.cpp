#include <Arduino.h>;
#include <Satelite.h>;
#include <EEPROM.h>;
#include <Plan13.h>;
double EL, AZ;
#define ONEPPM 1.0e-6;
#define DEBUG true;
Plan13 p13;

Satelite::Satelite() {}

void Satelite::iniciarSatelite(double longitud, double latitud, int alturaSobreElMar) {
  p13.setFrequency(435300000, 145920000);
  p13.setLocation(longitud, latitud, alturaSobreElMar);
  p13.setElements(2015.0, 307.62102318, 51.6448, 108.1798, 0.0006744,104.1138, 348.5383, 15.54781295, 0.0, 0, 180.0);
  p13.initSat();
}
 
void Satelite::calcularPosicion(double posicion[], int fecha[]) { 
  p13.setTime(fecha[0], fecha[1], fecha[2], fecha[3], fecha[4], fecha[5]);
  p13.calculate();
  Serial.print(">");
  Serial.print("+"); 
  Serial.println("\r");
  p13.satvec();
  p13.rangevec(&AZ, &EL);
  posicion[0]=AZ;
  posicion[1]=EL;
  Serial.print(">");
  Serial.print(posicion[0]); 
  Serial.println("\r");
  Serial.print(">");
  Serial.print(posicion[1]); 
  Serial.println("\r");
}

boolean Satelite::esVisibleSatelite(int fecha[]) {
  double posicion[2];
  calcularPosicion(posicion, fecha);
  if (posicion[1]>=0 && posicion[1]<=180) {
    return true;
  } else {
    return false;
  }
}

boolean Satelite::sateliteCerca(int fecha[]) {
  return false;
}