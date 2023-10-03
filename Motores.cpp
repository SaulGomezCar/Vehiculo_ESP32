//LIBRERIAS-----------------------------------------------------------------------------
#include <ESP32Servo.h>
#include <Robojax_L298N_DC_motor.h>
//PINES---------------------------------------------------------------------------------
const int IN1 = 25;
const int IN2 = 26;
const int ENA = 33;
const int IN3 = 27;
const int IN4 = 14;
const int ENB = 12;
//VARIABLES-----------------------------------------------------------------------------
Servo servo;  // Crear un objeto Servo
int servoPosition = 90;
int servoPositionTarget = 90;
int servoSpeed = 2; // Velocidad de movimiento del servo (ajusta según sea necesario)
int velocidad = 44;
int CW = 1;
int CCW = 2;
const int CHA = 0;
const int CHB = 1;
#define motor1 1 // do not change
#define motor2 2 // do not change
Robojax_L298N_DC_motor vehiculo(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB,true);
//SETUP---------------------------------------------------------------------------------
void Motores_setup(){
  vehiculo.begin();
  servo.attach(32);  // Adjunta el servo al pin 32
  servo.write(servoPosition); // Inicializar el servo en la posición central
  servoPositionTarget = servoPosition; // Inicializar la posición objetivo
}
//FUNCIONES---CW-CW(U),CCW-CCW(D),CW-CCW(R),CCW-CW(L)----CW=1--CCW=2--------------------
void MoverMotores(int velocidad, int direccion1, int direccion2) {
  Serial.print("MoverMotores ");
  Serial.println(velocidad);
  vehiculo.rotate(motor1, velocidad, direccion1);
  vehiculo.rotate(motor2, velocidad, direccion2);
}
void Stop(){
  Serial.println("Stop");
  vehiculo.brake(1);
  vehiculo.brake(2); 
}
void GradosServo(int grados) {
  servoPositionTarget = grados;
  servoPosition = grados; // Establece la posición actual igual a la posición objetivo
  servo.write(servoPosition);
}
void Servoplus() {
  int newPos = servoPositionTarget + 15;
  if (newPos > 180) {
    newPos = 180; // Limitar la posición máxima a 180 grados
  }
  servoPositionTarget = newPos; // Actualizar la posición objetivo
  servo.write(servoPositionTarget); // Mover el servo a la nueva posición
}

void Servominus() {
  int newPos = servoPositionTarget - 15;
  if (newPos < 0) {
    newPos = 0; // Limitar la posición mínima a 0 grados
  }
  servoPositionTarget = newPos; // Actualizar la posición objetivo
  servo.write(servoPositionTarget); // Mover el servo a la nueva posición
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
  MoverMotores(44,CW,CW);
  delay(2000);
  Stop();
  delay(1000);
  MoverMotores(44,CCW,CCW);
  delay(2000);
  MoverMotores(44,CW,CCW);
  delay(2000);
  MoverMotores(44,CCW,CW);
  delay(2000);
  Stop();
}
