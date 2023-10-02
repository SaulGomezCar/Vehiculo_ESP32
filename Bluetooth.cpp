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
        servoPositionTarget = Servoplus(servoPositionTarget);
        Serial.println(servoPositionTarget);
        break;
      case 'm':
        servoPositionTarget = Servominus(servoPositionTarget);
        Serial.println(servoPositionTarget);
        break;
      case 's':
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
      case '0':
        servoPositionTarget = 0;
        Serial.println(servoPositionTarget);
        break;
      case '1':
        servoPositionTarget = 45;
        Serial.println(servoPositionTarget);
        break;
      case '2':
        servoPositionTarget = 90;
        Serial.println(servoPositionTarget);
        break;
      case '3':
        servoPositionTarget = 135;
        Serial.println(servoPositionTarget);
        break;
      case '4':
        servoPositionTarget = 180;
        Serial.println(servoPositionTarget);
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
      case 'z':
        Bailar();
        break;
      default:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
    }
    Serial.write(btStatus);
  }
}
