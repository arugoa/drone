#include <Servo.h>

Servo escFL;
Servo escFR;
Servo escRR;
Servo escRL;

#define ESC_MIN 1000
#define ESC_MAX 2000

void setup() {
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

  delay(20);  // 50 Hz
}
