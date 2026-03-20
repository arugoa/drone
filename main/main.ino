#include "main.h"

void setup() {
  Serial.begin(115200);
  controller.begin();
  drone_.setup(cfg, true);
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

  if (controller.getLeftSwitch() == Switch::UP) {
    throttle = controller.getThrottle()*100;
    yaw = controller.getYaw();
    pitch = controller.getPitch();
    roll = controller.getRoll();
    // Serial.println("FLYING");

    pitch = clamp(pitch, -180, 180);
    yaw = clamp(yaw, -180, 180);
    roll = clamp(roll, -180, 180);

    drone_.fly(throttle, pitch, yaw, roll, dt, true);
  } 
  else if (controller.getLeftSwitch() == Switch::DOWN) {
    // Idk what to put here
  }
  else {
    throttle = 0;
    drone_.nofly();
    // Serial.println("NOT FLYING");
  }

  delay(10); // 100hz
}
