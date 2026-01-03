#include "PID.h"
#include <Servo.h>
// #include <BNO055.h>

// Find out what this is supposed to be
constexpr float MAX_THROTTLE = 1200;

class Drone
{
public:
    struct config
    {
        int fl;
        int fr;
        int bl;
        int br;
        // BNO055 imu;
    };

    Drone(config cfg);

    void setup();

    void fly(float throttle, float pitch, float yaw, float roll);

    float curr_yaw();

    float curr_pitch();

    float curr_roll();

private:
    Servo front_left;
    Servo front_right;
    Servo back_left;
    Servo back_right;

    // BNO055 imu;

    PID pitchPID;
    PID yawPID;
    PID rollPID;

    float dt;
};