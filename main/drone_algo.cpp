#include "drone_algo.h"

Drone::Drone()
{
    PID::config yawCfg;
    yawCfg.p = 1;
    yawCfg.i = 0;
    yawCfg.d = 0;

    PID::config pitchCfg;
    pitchCfg.p = 1;
    pitchCfg.i = 0;
    pitchCfg.d = 0;

    PID::config rollCfg;
    rollCfg.p = 1;
    rollCfg.i = 0;
    rollCfg.d = 0;

    yawPID = PID(yawCfg);
    pitchPID = PID(pitchCfg);
    rollPID = PID(rollCfg);
}

void Drone::setup(config cfg)
{
    front_left.attach(cfg.fl);
    front_right.attach(cfg.fr);
    back_left.attach(cfg.bl);
    back_right.attach(cfg.br);
    // imu = cfg.imu;

    // ARM ESCs
    front_left.writeMicroseconds(ESC_MIN);
    front_right.writeMicroseconds(ESC_MIN);
    back_left.writeMicroseconds(ESC_MIN);
    back_right.writeMicroseconds(ESC_MIN);

    delay(5000);

    /* Initialize the sensor */
    // if(!imu.begin())
    // {
    //     Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    //     while(1);
    // }

    delay(1000);

    // imu.setExtCrystalUse(true);
}

void Drone::fly(float throttle, float pitch, float yaw, float roll)
{
    // imu.getEvent(&event);
    // float deltapitch = pitchPID.calculate(pitch, curr_pitch(event), dt);
    // float deltayaw = yawPID.calculate(yaw, curr_yaw(event), dt);
    // float deltaroll = rollPID.calculate(roll, curr_roll(event), dt);

    float deltapitch = pitchPID.calculate(pitch, 0, dt);
    float deltayaw = yawPID.calculate(yaw, 0, dt);
    float deltaroll = rollPID.calculate(roll, 0, dt);


    // need to put PID into all of these
    int fl_micros = 1000 + (throttle + deltapitch + deltayaw + deltaroll)*THROTTLE_SENS;        // cw
    int fr_micros = 1000 + (throttle + deltapitch - deltayaw - deltaroll)*THROTTLE_SENS;        // ccw
    int bl_micros = 1000 + (throttle - deltapitch - deltayaw + deltaroll)*THROTTLE_SENS;        // ccw
    int br_micros = 1000 + (throttle - deltapitch + deltayaw - deltaroll)*THROTTLE_SENS;        // cw

    front_left.writeMicroseconds(fl_micros);
    front_right.writeMicroseconds(fr_micros);
    back_left.writeMicroseconds(bl_micros);
    back_right.writeMicroseconds(br_micros);
}

float Drone::curr_yaw(sensors_event_t event)
{
    return event.orientation.z;
}

float Drone::curr_pitch(sensors_event_t event)
{
    return event.orientation.x;
}

float Drone::curr_roll(sensors_event_t event)
{
    return event.orientation.y;
}