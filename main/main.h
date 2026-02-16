#include "Drone.h"
// #include <Servo.h>
// #include "ELRSController.h"
Adafruit_BNO055 bno = Adafruit_BNO055(55);

Drone::config cfg = {3, 5, 6, 9, bno};

// ELRSController controller;

Drone drone_;

float throttle = 0;
float yaw = 0;
float pitch = 0;
float roll = 0;

unsigned long prev_time = 0;