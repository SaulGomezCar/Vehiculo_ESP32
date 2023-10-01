#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>

void Motores_setup();
void Avanzar();
void Retroceder();
void Derecha();
void Izquierda();
void Stop();
long Ultrasonico(int TRIG, int ECHO);
void Bailar();

#endif //MOTORES_H
