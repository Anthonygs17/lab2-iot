/*  Sistema de riego inteligente  */

const int sensorHumedadPin = A5;
const int ledAzulPin = 41;
const int ledRojoPin = 45;
const int buzzerPin = 47;
const int relePin = 49;

const int humedadBaja = 20;
const int humedadAlta = 80;

void setup() {
  pinMode(ledAzulPin, OUTPUT);
  pinMode(ledRojoPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relePin, OUTPUT);
  pinMode(sensorHumedadPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int nivelHumedad = analogRead(sensorHumedadPin);
  int porcentajeHumedad = map(nivelHumedad, 0, 1023, 0, 100);
  
  // Modo de riego si la humedad está por debajo de 20%
  if (porcentajeHumedad < humedadBaja) {
    digitalWrite(relePin, HIGH);
    Serial.println("Alerta: sobre-hidratación detectada.");
    Serial.print(100 - porcentajeHumedad);
    digitalWrite(ledRojoPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(ledRojoPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }

  // Alerta si la humedad está por encima de 80%
  else if (porcentajeHumedad > humedadAlta) {
    digitalWrite(ledAzulPin, HIGH);
    digitalWrite(relePin, LOW);
    Serial.print("Humedad de la tierra: ");
    Serial.print(100 - porcentajeHumedad);
    Serial.println("%");
    delay(10000);
    digitalWrite(relePin, HIGH);
    digitalWrite(ledAzulPin, LOW);
    Serial.println("Modo IDLE.");
    delay(15000);
  }

  else{ // Modo normal, no hacer nada si la humedad está en rango adecuado
    Serial.print(100 - porcentajeHumedad);
    delay(5000);
    Serial.println("\n");
  }
}