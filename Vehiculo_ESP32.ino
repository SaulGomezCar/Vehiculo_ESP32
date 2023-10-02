#include "Motores.h"
#include "IR.h"
#include "Bluetooth.h"

int TRIG1 = 16;
int ECHO1 = 17;
int TRIG2 = 2;
int ECHO2 = 4;

void setup() {
  Serial.begin(115200);
  IR_setup();
  Bluetooth_setup();
  Motores_setup();
  pinMode(TRIG1, OUTPUT); 
  pinMode(ECHO1, INPUT); 
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
}

void loop() {
  long distanciaFrontal = Ultrasonico(TRIG1, ECHO1);
  long distanciaTrasera = Ultrasonico(TRIG2, ECHO2);
  ActualizarServo(); // Llamar a la función para actualizar el servo
  if (distanciaFrontal < 10 || distanciaTrasera < 10) {
    Stop(); // Detenerse si el objeto está demasiado cerca en frente
  } else {
    Bluetooth();
    RecibirIR(); // Leer comandos infrarrojos
  }
  delay(100);
}
