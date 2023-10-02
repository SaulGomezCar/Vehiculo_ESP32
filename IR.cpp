//LIBRERIAS-----------------------------------------------------------------------------
#include <IRremote.h>
#include "Motores.h"
//PINES---------------------------------------------------------------------------------
int IR_RECEIVE_PIN = 15;
//VARIABLES-----------------------------------------------------------------------------
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;
#if defined(ARDUINO_ARCH_SAMD)// On the Zero and others we switch explicitly to SerialUSB
#define Serial SerialUSB
#endif
//SETUP---------------------------------------------------------------------------------
void IR_setup(){
  #if defined(__AVR_ATmega32U4__)
  while (!Serial); //delay for Leonardo, but this loops forever for Maple Serial
  #endif
  #if defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
    delay(2000); // To be able to connect Serial monitor after reset and before first printout
  #endif
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__));
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
}
//FUNCIONES-----------------------------------------------------------------------------
void RecibirIR(){
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0xE0E006F9:
        MoverMotores(velocidad,CW,CW);
        break;
      case 0xE0E08679:
        MoverMotores(velocidad,CCW,CCW);
        break;
      case 0xE0E046B9:
        MoverMotores(velocidad,CW,CCW);
        break;
      case 0xE0E0A659:
        MoverMotores(velocidad,CCW,CW);
        break;
      case 0xE0E020DF:
        velocidad = 37;
        break;
      case 0xE0E0A05F:
        velocidad = 44;
        break;
      case 0xE0E0609F:
        velocidad = 99;
        break;
      case 0xE0E01AE5:
        servoPositionTarget = Servominus(servoPositionTarget);
        Serial.println(servoPositionTarget);
        break;
      case 0xE0E0B44B:
        servoPositionTarget = Servoplus(servoPositionTarget);
        Serial.println(servoPositionTarget);
        break;
      case 0xE0E0D22D:
        servoPositionTarget = 0;
        Serial.println(servoPositionTarget);
        break;
      case 0xE0E031CE:
        servoPositionTarget = 45;
        Serial.println(servoPositionTarget);
        break;
      case 0xE0E058A7:
        servoPositionTarget = 90;
        Serial.println(servoPositionTarget);
        break;
      case 0xE0E0C03F:
        servoPositionTarget = 135;
        Serial.println(servoPositionTarget);
        break;
      case 0xE0E0F807:
        servoPositionTarget = 180;
        Serial.println(servoPositionTarget);
        break;
      case 0xE0E06897:
        Bailar();
        break;
      default:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
