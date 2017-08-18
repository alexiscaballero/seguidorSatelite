#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Motor.h>
#define TIME_HEADER  "AZ"
Motor motor;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
double posicionSatelite[2];

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.display();
}

void loop() {
  if (Serial.available()>0) {
    if (Serial.find(TIME_HEADER)) {
      String AZEL = Serial.readStringUntil('\n');
      
      int posicionSeparador = AZEL.indexOf('E');
      String aux1 = AZEL.substring(0,posicionSeparador);
      String aux2 = AZEL.substring(posicionSeparador+2,AZEL.length());
      
      posicionSatelite[0]=aux1.toInt();
      posicionSatelite[1]=aux2.toInt();
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(posicionSatelite[0]);
      lcd.setCursor(0,1);
      lcd.print(posicionSatelite[1]);
      if (posicionSatelite[1]>=0) {  
        motor.moverMotor(posicionSatelite);
      }
    }
  }
  delay(1500);
}
