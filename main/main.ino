#include "main.h"

void setup() {
  Serial.begin(115200);
  controller.begin();
  drone_.setup(cfg);
  prev_time = millis()/1000;

  pitch = drone_.curr_pitch();
  yaw = drone_.curr_yaw();
  roll = drone_.curr_roll();
}

void loop() {
  unsigned long dt = millis()/1000 - prev_time;
  prev_time = millis()/1000;
  drone_.updateIMU();
  controller.update();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    char armID = input.charAt(0);

    if (armID == 'T') {
      throttle = input.substring(1).toFloat();
    } 
    else if (armID == 'Y') {
      yaw += input.substring(1).toFloat();
    }
    else if (armID == 'P') {
      pitch += input.substring(1).toFloat();
    }
    else if (armID == 'R') {
      roll += input.substring(1).toFloat();
    }
  }

  pitch = clamp(pitch, -180, 180);
  yaw = clamp(yaw, -180, 180);
  roll = clamp(roll, -180, 180);

  // drone_.fly(throttle, pitch, yaw, roll, dt);

  delay(20);
}
