// Copy of test_qbrain.ino

#include "main.h"

void setup() {
  Serial.begin(115200);
  escFL.attach(3);
  escFR.attach(5);
  escRR.attach(6);
  escRL.attach(9);

  // ARM ESCs
  escFL.writeMicroseconds(ESC_MIN);
  escFR.writeMicroseconds(ESC_MIN);
  escRR.writeMicroseconds(ESC_MIN);
  escRL.writeMicroseconds(ESC_MIN);

  delay(5000);
}

void loop() {
  int throttle = 1200;

  escFL.writeMicroseconds(throttle);
  escFR.writeMicroseconds(throttle);
  escRR.writeMicroseconds(throttle);
  escRL.writeMicroseconds(throttle);

  //delay(20); // 50Hz
  Serial.println("Loop Ran");
}
