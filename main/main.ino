#include "main.h"

void setup() {
  Serial.begin(115200);
  drone_.setup(cfg);
  
  // escFL.attach(3);
  // escFR.attach(5);
  // escRR.attach(6);
  // escRL.attach(9);
}

float throttle = 0;
float yaw = 0;
float pitch = 0;
float roll = 0;

void loop() {
  // sensors_event_t event;
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    char armID = input.charAt(0);

    if (armID == 'T') {
      throttle = input.substring(1).toFloat();
    } 
    else if (armID == 'Y') {
      yaw = input.substring(1).toFloat();
    }
    else if (armID == 'P') {
      pitch = input.substring(1).toFloat();
    }
    else if (armID = 'R') {
      roll = input.substring(1).toFloat();
    }
  } 

  drone_.fly(throttle, pitch, yaw, roll);

  // int throttle = 1200;

  // escFL.writeMicroseconds(throttle);
  // escFR.writeMicroseconds(throttle);
  // escRR.writeMicroseconds(throttle);
  // escRL.writeMicroseconds(throttle);

  delay(20); // 50Hz
  Serial.println("Loop Ran");
}
