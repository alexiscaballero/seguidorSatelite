#include <EEPROM.h>

#include <Plan13.h>
double EL, AZ;

//#include <avr/sleep.h>
//#include <avr/power.h>
#define ONEPPM 1.0e-6
#define DEBUG true
Plan13 p13;
long tiempo_inicial, tiempo_final, segundos_enteros;
int tiempo, anio, mes, dia, minutos, segundos, hora, diferencia;

void setup () {
 p13.setFrequency(435300000, 145920000);//AO-51  frequency
  p13.setLocation(-58.15, -32.30, 16); // C. del Uruguay, NB
Serial.begin(115200);
}
void loop() { 
  anio = 2015;
  mes = 10;
  dia = 26;
  hora = 21;
  minutos = 35;
  segundos = 0;
///  p13.setTime(anio, mes, dia, hora, minutos, segundos); ////2015, 10, 20, 21, 1, 0); //Oct 1, 2009 19:05:00 UTC
  p13.setElements(2009, 232.55636497, 98.0531, 238.4104, 83652*1.0e-7, 290.6047,
  68.6188, 14.406497342, -0.00000001, 27022, 180.0); //fairly recent keps for AO-51 //readElements();
  p13.initSat();
  while (1){
  p13.setTime(anio, mes, dia, hora, minutos, segundos);
  Serial.print("Minutos: ");
  Serial.print(minutos);
  Serial.print(" Segundos: ");
  Serial.print(segundos);
  tiempo_inicial = millis();  
  ////p13.setTime(2009, 10, 1, 19, 5, 0);
  ///p13.calculate();
  p13.satvec();
  p13.rangevec(&AZ, &EL);
  /*
  A partir de aqui tengo los valores del azimuth y de la altura del satelite:
  AZ: azimuth
  EL: elevacion
  */
  ///p13.printdata();
  //Serial.println();
  //Serial.println("Should be:\n");
  //Serial.println("AZ:57.07 EL: 4.05 RX 435301728 TX 145919440\n");
  Serial.print(" Altura: ");
  Serial.print(EL);
  Serial.print(" Azimuth: ");
  Serial.println(AZ);
  delay(1000);
  diferencia = millis() - tiempo_inicial;
  tiempo = (int)(diferencia / 1000);
  segundos = segundos + tiempo;
  if (segundos > 60){
    tiempo = (int)(segundos / 60);
    minutos = minutos + tiempo;
    segundos = segundos - (tiempo * 60);
   }
   if (minutos > 60){
   tiempo = (int)(minutos / 60);
   hora = hora + tiempo;
   minutos = minutos - (tiempo * 60);
   }
   if (hora > 24){
   tiempo = (int)(hora / 24);
   dia = dia + tiempo;
   hora = hora - (tiempo * 24);
   }
  }
 exit(1);
}




