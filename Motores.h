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
void GradosServo(int grados);
int Servoplus();
int Servominus();
long Ultrasonico(int TRIG, int ECHO);
void Bailar();

#endif //MOTORES_H
