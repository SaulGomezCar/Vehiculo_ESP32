#ifndef MOTORES_H
#define MOTORES_H

extern int velocidad;
extern int servoPosition;
extern int servoPositionTarget;
extern int servoSpeed;
extern int CW;
extern int CCW;

void Motores_setup();
void MoverMotores(int velocidad,int direccion1,int direccion2);
void Stop();
void ActualizarServo();
int Servoplus(int currentPos);
int Servominus(int currentPos);
long Ultrasonico(int TRIG, int ECHO);
void Bailar();

#endif //MOTORES_H
