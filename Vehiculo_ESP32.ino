#include "Motores.h"
#include "IR.h"
#include "Bluetooth.h"

void setup() {
  IR_setup();
  Bluetooth_setup();
  Motores_setup();
}

void loop() {
  RecibirIR();
  Bluetooth();
  delay(100);
}
