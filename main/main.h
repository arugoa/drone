#include "./algorithms/drone_algo.h"
#include <Servo.h>

Servo escFL;
Servo escFR;
Servo escRR;
Servo escRL;

#define ESC_MIN 1000
#define ESC_MAX 2000