//LIBRERIAS-----------------------------------------------------------------------------
#include <Arduino.h>
#include <ESP32Servo.h>
//PINES---------------------------------------------------------------------------------
int IN1 = 25;
int IN2 = 26;
int INA = 33;
int IN3 = 27;
int IN4 = 14;
int INB = 12;
//VARIABLES-----------------------------------------------------------------------------
Servo servo;  // Crear un objeto Servo
//SETUP---------------------------------------------------------------------------------
void Motores_setup(){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(INA,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(INB,OUTPUT);
  servo.attach(32);  // Adjunta el servo al pin 32
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
void GradosServo(int grados){
  Serial.println(grados);
  servo.write(grados);
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
