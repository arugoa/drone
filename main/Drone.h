#include "PID.h"
#include "OpenLoop.h"
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define ESC_MIN 1000
#define ESC_MAX 2000

#define clamp(amt, low, high)                                              \
  ((amt) < (low) ? (amt+2*high) : ((amt) > (high) ? (amt-2*high) : (amt)))

constexpr float MAX_THROTTLE = 2000;
constexpr float THROTTLE_SENS = 6;  // Set based on the lowest max thrust of ur motors

class Drone
{
public:
    struct config
    {
        int fl;
        int fr;
        int bl;
        int br;
        int imu;
    };

    Drone();

    void setup(config cfg, bool no_imu=false);

    void updateIMU();

    void fly(float throttle, float pitch, float yaw, float roll, unsigned long dt, bool no_imu=false);

    void thrust(float throttle);

    void nofly();

    float curr_yaw();

    float curr_pitch();

    float curr_roll();
    
private:
    Servo front_left;
    Servo front_right;
    Servo back_left;
    Servo back_right;
    
    Adafruit_BNO055 imu;
    sensors_event_t event;

    PID pitchPID;
    PID yawPID;
    PID rollPID;

    OpenLoop flPID;
    OpenLoop frPID;
    OpenLoop blPID;
    OpenLoop brPID;
};