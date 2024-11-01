/*  Sistema de seguridad inteligente  */

#include <LiquidCrystal.h>
#include <Keypad.h>

const byte rowsCount = 4;
const byte columsCount = 4;

char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '#','0','*', 'D' }
};

const byte rowPins[rowsCount] = { 28, 30, 32, 34 };
const byte columnPins[columsCount] = { 36, 38, 40, 42 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

String contrasena = "1234";
String txt = "";

LiquidCrystal lcd(2, 6, 8, 9, 10, 11);

const int Trigger = 4;   //Pin digital 2 para el Trigger del sensor
const int Echo = 5;   //Pin digital 3 para el Echo del sensor
int LED = 3;
int LEDVERDE = 31;
int LEDROJO = 33;

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);
  pinMode(LED, OUTPUT);   //pin de salida para el LED que simboliza la grabacion
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  lcd.begin(16, 2); // Establece el numero de columnas y filas del LCD
}

void loop(){
  long t; //tiempo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.print("cm");
  Serial.println();
  String firstRow = "Insert";
  String secondRow = "Password";
  
  if(d <= 20){
    // Se activa el sistema de grabacion
    digitalWrite(LED, HIGH);
    delay(400);
    digitalWrite(LED, LOW);
    delay(400);

    lcd.setCursor(0, 0);
    lcd.print(firstRow);
    lcd.setCursor(0, 1);
  	lcd.print(secondRow);

    // Se ingresa la contraseña de 4 caracteres
    char key;
    while(txt.length() != 4){
      key = keypad.getKey();
      if (key)      // Revisamos que sea una tecla valida
        txt += key;
    }
    // Se valida la contraseña
    if (txt == contrasena){
      digitalWrite(LEDVERDE, HIGH);
      firstRow = "Correct";
    }else{
      digitalWrite(LEDROJO, HIGH);
      firstRow = "Incorrect";
    }
    // Se muestra el mensaje correspondiente
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(firstRow);
    lcd.setCursor(0, 1);
    lcd.print(secondRow);
    delay(2000);
    // Se reestable el sistema de autenticacion
    lcd.clear();
    digitalWrite(LEDVERDE, LOW);
    digitalWrite(LEDROJO, LOW);
  }else{ 
    // Ahorro energetico
    digitalWrite(LED, LOW);
    lcd.clear();
  }
  
  delay(100);          //Hacemos una pausa de 100ms
}