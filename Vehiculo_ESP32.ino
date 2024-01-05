#include "Motores.h"
#include "IR.h"
#include "Bluetooth.h"
#include "Wifi.h"
#include "Web.h"

int TRIG1 = 16;
int ECHO1 = 17;
int TRIG2 = 2;
int ECHO2 = 4;
unsigned long tiempoDeParada = 0;
const unsigned long tiempoDeEspera = 1000; // 1 segundo de espera

void setup() {
  Serial.begin(115200);
  Wifi_setup();
  Web_setup();
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
  Serial.print("Frontal: ");
  Serial.print(distanciaFrontal);
  Serial.print(" Trasera: ");
  Serial.println(distanciaTrasera);
  if (distanciaFrontal <= 15 || distanciaTrasera <= 15) {
    if (tiempoDeParada == 0) { // Iniciar el temporizador de parada breve si no está activo
      tiempoDeParada = millis();
      Stop(); // Detenerse si el objeto está demasiado cerca en frente
    } else if (tiempoDeParada >= tiempoDeEspera) {
      RecibirIR();
      Bluetooth();
      Wifi_loop();
      Web();
    }
  } else {
    tiempoDeParada = 0;
    RecibirIR();
    Bluetooth();
    Wifi_loop();
    Web();
  }
  delay(50);
}
