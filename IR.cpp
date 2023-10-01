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
  Serial.begin(115200);
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
        Avanzar();
        break;
      case 0xE0E08679:
        Retroceder();
        break;
      case 0xE0E046B9:
        Derecha();
        break;
      case 0xE0E0A659:
        Izquierda();
        break;
      case 0xE0E01AE5:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido Servo Plus
        break;
      case 0xE0E0B44B:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido Servo Minus
        break;
      case 0xE0E0D22D:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido 0
        break;
      case 0xE0E031CE:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido 45
        break;
      case 0xE0E058A7:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido 90
        break;
      case 0xE0E0C03F:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido 135
        break;
      case 0xE0E0F807:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido 180
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
