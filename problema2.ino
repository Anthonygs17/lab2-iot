/*  Sistema de deteccion de movimiento  */

#include <LiquidCrystal.h>

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

int pir = 7;
int ledverde = 8;
int ledrojo = 9;

int personas = 1;
int elapsedTime = 0;

void setup(){
  pinMode(pir, INPUT);
  pinMode(ledverde, OUTPUT);
  pinMode(ledrojo, OUTPUT);
  lcd_1.begin(16, 2); // Establece el numero de columnas y filas del LCD
}

void loop(){
  // Hacemos la lectura del sensor PIR
  int value = digitalRead(pir);
  
  if(value == LOW){ // No hay movimiento
    digitalWrite(ledrojo, LOW);
    digitalWrite(ledverde, HIGH);
    delay(200);
    digitalWrite(ledverde, LOW);
    delay(200);
  }else{ // Hay movimiento
  	digitalWrite(ledverde, LOW);
    digitalWrite(ledrojo, HIGH);
    
    if(elapsedTime > 5000){
    	personas += 1;
      elapsedTime = 0;
    }
    // Muestra la cantidad de incidencias en la pantalla LCD
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("INCIDENCIAS ");
    lcd_1.print(personas);
    
    delay(500);
    elapsedTime += 500;
  }
  
}