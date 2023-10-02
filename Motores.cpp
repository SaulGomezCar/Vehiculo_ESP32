//LIBRERIAS-----------------------------------------------------------------------------
#include <Arduino.h>
#include <ESP32Servo.h>
#include <Robojax_L298N_DC_motor.h>
//PINES---------------------------------------------------------------------------------
int IN1 = 25;
int IN2 = 26;
int ENA = 33;
int IN3 = 27;
int IN4 = 14;
int ENB = 12;
//VARIABLES-----------------------------------------------------------------------------
Servo servo;  // Crear un objeto Servo
int velocidad = 70;
const int CHA = 0;
const int CHB = 1;
const int CCW = 2; // do not change
const int CW  = 1; // do not change
#define motor1 1 // do not change
#define motor2 2 // do not change
Robojax_L298N_DC_motor vehiculo(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB,true);
//SETUP---------------------------------------------------------------------------------
void Motores_setup(){
  vehiculo.begin();
  servo.attach(32);  // Adjunta el servo al pin 32
}
//FUNCIONES-----------------------------------------------------------------------------
void Avanzar(int velocidad){ //Funcion para avanzar (motores)
  Serial.print("Avanzar ");
  Serial.println(velocidad);
  vehiculo.rotate(motor1, velocidad, CW);//run motor1 at % speed in CW direction
  vehiculo.rotate(motor2, velocidad, CW);//run motor1 at % speed in CW direction
}
void Retroceder(int velocidad){ //Funcion para retroceder (motores)
  Serial.print("Retroceder ");
  Serial.println(velocidad);
  vehiculo.rotate(motor1, velocidad, CCW);//run motor1 at % speed in CCW direction
  vehiculo.rotate(motor2, velocidad, CCW);//run motor1 at % speed in CCW direction
}
void Derecha(int velocidad){ //Funcion para girar a la derecha (motores)
  Serial.print("Derecha ");
  Serial.println(velocidad);
  vehiculo.rotate(motor1, velocidad, CW);//run motor1 at % speed in CW direction
  vehiculo.rotate(motor2, velocidad, CCW);//run motor1 at % speed in CCW direction
}
void Izquierda(int velocidad){ //Funcion para girar a la izquierda (motores)
  Serial.print("Izquierda ");
  Serial.println(velocidad);
  vehiculo.rotate(motor1, velocidad, CCW);//run motor1 at % speed in CCW direction
  vehiculo.rotate(motor2, velocidad, CW);//run motor1 at % speed in CW direction
}
void Stop(){
  Serial.println("Stop");
  vehiculo.brake(1);
  vehiculo.brake(2); 
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
  Avanzar(60);
  delay(2000);
  Stop();
  delay(1000);
  Retroceder(60);
  delay(2000);
  Izquierda(60);
  delay(2000);
  Derecha(60);
  delay(2000);
  Stop();
}
