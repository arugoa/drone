#include "Drone.h"
#inculde "ELRSController.h"

// Use Pin 10 for RX (Connect to Receiver TX)
// Use Pin 11 for TX (Connect to Receiver RX via voltage divider)
ELRSController controller(10, 11);
Adafruit_BNO055 bno = Adafruit_BNO055(55);

Drone::config cfg = {3, 5, 6, 9, bno};
Drone drone_;

float throttle = 0;
float yaw = 0;
float pitch = 0;
float roll = 0;

unsigned long prev_time = 0;