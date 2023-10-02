#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>

extern int velocidad;
extern int servoPosition;
extern int servoPositionTarget;
extern int servoSpeed;

void Motores_setup();
void Avanzar(int velocidad);
void Retroceder(int velocidad);
void Derecha(int velocidad);
void Izquierda(int velocidad);
void Stop();
void ActualizarServo();
int Servoplus(int currentPos);
int Servominus(int currentPos);
long Ultrasonico(int TRIG, int ECHO);
void Bailar();

#endif //MOTORES_H
