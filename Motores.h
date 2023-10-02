#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>

extern int velocidad;

void Motores_setup();
void Avanzar(int velocidad);
void Retroceder(int velocidad);
void Derecha(int velocidad);
void Izquierda(int velocidad);
void Stop();
void GradosServo(int grados);
long Ultrasonico(int TRIG, int ECHO);
void Bailar();

#endif //MOTORES_H
