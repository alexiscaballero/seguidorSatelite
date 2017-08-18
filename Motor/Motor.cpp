#include <Arduino.h>;
#include <Motor.h>;
#define AZ A0
#define EL A1
#define UP 12
#define DOWN 11
#define LEFT 10
#define RIGHT 9

Motor::Motor(){
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  digitalWrite(UP, LOW);
  digitalWrite(DOWN, LOW);
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, LOW);
}

void Motor::moverAbajo(double ELSatelite)  {
  digitalWrite(DOWN, HIGH);
  while ((ELSatelite-posicionElevacion())<5){
    //Serial.println(analogRead(EL));
    delay(100);
  }
  digitalWrite(DOWN, LOW);
  delay(100);
}

void Motor::moverArriba(double ELSatelite)  {
  digitalWrite(UP, HIGH);
  while ((posicionElevacion()-ELSatelite)<5){
    //Serial.println(analogRead(EL));
    delay(100);
  }
  digitalWrite(UP, LOW);
  delay(100);
}

void Motor::moverDerecha(double AZSatelite)  {
  digitalWrite(RIGHT, HIGH);
  while ((posicionAzimuth()-AZSatelite)<5){
    //Serial.println(analogRead(AZ));
    delay(100);
  }
  digitalWrite(RIGHT, LOW);
  delay(100);
}

void Motor::moverIzquierda(double AZSatelite)  {
  digitalWrite(LEFT, HIGH);
  while ((posicionAzimuth()-AZSatelite)<5){
    //Serial.println(analogRead(AZ));
    delay(100);
  }
  digitalWrite(LEFT, LOW);
  delay(100);
}

double Motor::map_double(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


double Motor::posicionAzimuth() {
  //Leer voltaje para saber el azimuth del motor
  int voltajeAZ = analogRead(AZ);
  Serial.println(voltajeAZ);
  //Calcular azimuth en grados
  double azimuth;
    azimuth = map_double(voltajeAZ,5,765,0,360);
  Serial.println(azimuth);
  return azimuth;
}

double Motor::posicionElevacion() {
  //Leer voltaje para saber la elevacion del motor 
  int voltajeEL = analogRead(EL);
  Serial.println(voltajeEL);
  //Calcular la elevacion en grados
  double elevacion = map_double(voltajeEL,5,765,0,180);
  Serial.println(elevacion);
  return elevacion;
}

void Motor::moverMotor(double posicion[]) {
  //Posicion del satelite
  double AZSatelite = posicion[0];
  double ELSatelite = posicion[1];
  //Recalcular Azimuth Del Satelite Segun Coordenadas Del Motor
  double AZSateliteM;
  if (AZSatelite>181) {
    AZSateliteM = map_double(AZSatelite,181,359,0,179);
  } else {
    AZSateliteM = map_double(AZSatelite,5,178,180,359);
  }
  //Obtener posicion del motor
  double AZMotor = posicionAzimuth();  
  double ELMotor = posicionElevacion();
  //Calcular diferencia de grados
  double diferenciaAZ = AZSatelite - AZMotor; //Si da negativo hay que girar para la izquierda
  double diferenciaEL = ELSatelite - ELMotor; //Si da negativo hay que bajar el motor

  //Mover el motor segun el azimuth
  if (diferenciaAZ<0) {
    moverIzquierda(AZSatelite);
  } else {
    moverDerecha(AZSatelite);
  }
  //Mover el motor segun la elevacion
  if (diferenciaEL<0) {
    moverAbajo(ELSatelite);
  } else {
    moverArriba(ELSatelite);
  }
}