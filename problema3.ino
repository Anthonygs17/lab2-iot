/*  Monitoreo de refrigeracion para alimentos  */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorHumedadPin1 = A1;
const int sensorHumedadPin2 = A2;
const int sensorTempPin = A0;
const int ledRojo = 7;
const int buzzer = 6;

float humedad;
float temperatura;

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
   
  pinMode(sensorHumedadPin1, OUTPUT);
  pinMode(sensorHumedadPin2, INPUT);
  pinMode(sensorTempPin, INPUT);
  
  lcd.begin(16, 2);
  lcd.print("TEMP HUMED");

  Serial.begin(9600);
}

void loop() {
  // Hacemos la lectura del sensor de humedad
  int valorHumedad = analogRead(sensorHumedadPin2);
  humedad = map(valorHumedad, 0, 1023, 0, 100);
  Serial.print("Humedad: ");
  Serial.println(humedad);
  
  // Hacemos la lectura del sensor de temperatura
  int valorTemp = analogRead(sensorTempPin);
  temperatura = (valorTemp * 5.0 * 100.0) / 1024.0;
  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  lcd.setCursor(0, 1);
  lcd.print(temperatura);
  lcd.print("C ");
  lcd.print(humedad);
  lcd.print("%");
  
  // Verificamos si la temperatura o la humedad están fuera de las condiciones optimas
  if (temperatura < 0 || temperatura > 10 || humedad < 80 || humedad > 90) { 
    // Dado que aca no lo estan, emitimos una alerta
    digitalWrite(ledRojo, HIGH);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(ledRojo, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(1000);  // Pausa para volver a hacer las mediciones
}