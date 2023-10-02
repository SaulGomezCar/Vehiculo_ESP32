//LIBRERIAS-----------------------------------------------------------------------------
#include <Arduino.h>
#include "BluetoothSerial.h"
#include "Motores.h"
//VARIABLES-----------------------------------------------------------------------------
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED) //indica si funciona o no la conexion bluetooth
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
char btStatus;
//SETUP---------------------------------------------------------------------------------
void Bluetooth_setup(){
  SerialBT.begin("ESP32_Saul"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}
//FUNCIONES-----------------------------------------------------------------------------
void Bluetooth(){
  if (Serial.available()) {
    SerialBT.write(Serial.read()); //si recibimos el valor el mensaje se muestra
  }
  if (SerialBT.available()) {
    btStatus= SerialBT.read(); //si el mensaje va desde el esp32 hacia el telefono se muestra
    switch (btStatus) {
      case 'u':
        Avanzar(velocidad);
        break;
      case 'd':
        Retroceder(velocidad);
        break;
      case 'r':
        Derecha(velocidad);
        break;
      case 'l':
        Izquierda(velocidad);
        break;
      case 'k':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido Servo Plus
        break;
      case 'm':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido Servo Minus
        break;
      case 's':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case '0':
        GradosServo(0);
        break;
      case '1':
        GradosServo(45);
        break;
      case '2':
        GradosServo(90);
        break;
      case '3':
        GradosServo(135);
        break;
      case '4':
        GradosServo(180);
        break;
      case 'a':
        velocidad = 37;
        break;
      case 'b':
        velocidad = 44;
        break;
      case 'c':
        velocidad = 99;
        break;
      case 'e':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case 'f':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case 'g':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case 'h':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case 'i':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case 'j':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case 'w':
        Bailar(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case 'x':
        Stop();
        break;
      case 'y':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case 'z':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      default:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
    }
    Serial.write(btStatus);
  }
}
