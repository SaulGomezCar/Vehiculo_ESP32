//LIBRERIAS-----------------------------------------------------------------------------
#include <Arduino.h>
//PINES---------------------------------------------------------------------------------
int IN1 = 25;
int IN2 = 26;
int INA = 33;
int IN3 = 27;
int IN4 = 14;
int INB = 12;
//VARIABLES-----------------------------------------------------------------------------
//SETUP---------------------------------------------------------------------------------
void Motores_setup(){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(INA,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(INB,OUTPUT);
}
//FUNCIONES-----------------------------------------------------------------------------
void Avanzar(){ //Funcion para avanzar (motores)
  Serial.println("Avanzar");
  digitalWrite(INA,HIGH);
  digitalWrite(INB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void Retroceder(){ //Funcion para retroceder (motores)
  Serial.println("Retroceder");
  digitalWrite(INA,HIGH);
  digitalWrite(INB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void Derecha(){ //Funcion para girar a la derecha (motores)
  Serial.println("Derecha");
  digitalWrite(INA,HIGH);
  digitalWrite(INB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void Izquierda(){ //Funcion para girar a la izquierda (motores)
  Serial.println("Izquierda");
  digitalWrite(INA,HIGH);
  digitalWrite(INB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void Stop(){
  Serial.println("Stop");
  digitalWrite(INA,LOW);
  digitalWrite(INB,LOW);
}
void Bailar(){
  Serial.println("Bailar");
  Avanzar();
  delay(2000);
  Stop();
  delay(1000);
  Retroceder();
  delay(2000);
  Izquierda();
  delay(2000);
  Derecha();
  delay(2000);
  Stop();
}
