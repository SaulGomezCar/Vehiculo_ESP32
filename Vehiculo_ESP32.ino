#include "Motores.h"
#include "IR.h"
#include "Bluetooth.h"

int TRIG1 = 16;
int ECHO1 = 17;
int TRIG2 = 2;
int ECHO2 = 4;

void setup() {
  IR_setup();
  Bluetooth_setup();
  Motores_setup();
  pinMode(TRIG1, OUTPUT); 
  pinMode(ECHO1, INPUT); 
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);;
}

void loop() {
  long distanciaFrontal = Ultrasonico(TRIG1, ECHO1);
  long distanciaTrasera = Ultrasonico(TRIG2, ECHO2);
  if (distanciaFrontal < 10 || distanciaTrasera < 10) {
    Stop(); // Detenerse si el objeto está demasiado cerca en frente
  } else {
    Bluetooth();
    RecibirIR(); // Leer comandos infrarrojos
  }
  delay(100);
}
long Ultrasonico(int TRIG, int ECHO){
  long t; //tiempo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(TRIG, LOW); //Inicializamos el pin con 0
  delayMicroseconds(2); //Parecida a delay pero trabaja con microsegundos
  digitalWrite(TRIG, HIGH); //Endendemos para que envíe la onda ultrasónica
  delayMicroseconds(10); //Durante 10 microsegundos
  digitalWrite(TRIG, LOW); //Apagar el sensor
  t = pulseIn(ECHO, HIGH); //obtenemos el tiempo del pulso
  d = t/59; //escalamos el tiempo a una distancia en cm
  return d;
}
