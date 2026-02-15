#include "PID.h"
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define ESC_MIN 1000
#define ESC_MAX 2000
// Find out what this is supposed to be
constexpr float MAX_THROTTLE = 2000;
constexpr float THROTTLE_SENS = 100;

class Drone
{
public:
    struct config
    {
        int fl;
        int fr;
        int bl;
        int br;

        // Adafruit_BNO055 imu;
    };

    Drone();

    void setup(config cfg);

    void fly(float throttle, float pitch, float yaw, float roll);

    float curr_yaw(sensors_event_t event);

    float curr_pitch(sensors_event_t event);

    float curr_roll(sensors_event_t event);

private:
    Servo front_left;
    Servo front_right;
    Servo back_left;
    Servo back_right;

    // Adafruit_BNO055 imu;

    PID pitchPID;
    PID yawPID;
    PID rollPID;

    float dt;
};