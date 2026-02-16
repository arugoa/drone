#include "Drone.h"

Drone::Drone()
{
    PID::config yawCfg(0.1, 0, 0, 180, 30);
    PID::config pitchCfg(0.1, 0, 0, 180, 30);
    PID::config rollCfg(0.1, 0, 0, 180, 30);

    yawPID = PID(yawCfg);
    pitchPID = PID(pitchCfg);
    rollPID = PID(rollCfg);

    PID::config flCfg(THROTTLE_SENS, 0, 0, ESC_MAX, 200);
    PID::config frCfg(THROTTLE_SENS, 0, 0, ESC_MAX, 200);
    PID::config blCfg(THROTTLE_SENS, 0, 0, ESC_MAX, 200);
    PID::config brCfg(THROTTLE_SENS, 0, 0, ESC_MAX, 200);

    flPID = PID(flCfg);
    frPID = PID(frCfg);
    blPID = PID(blCfg);
    brPID = PID(brCfg);

    flPID.feedForward = 1150;
    frPID.feedForward = 1000;
    blPID.feedForward = 1000;
    brPID.feedForward = 1150;
}

void Drone::setup(config cfg)
{
    front_left.attach(cfg.fl);
    front_right.attach(cfg.fr);
    back_left.attach(cfg.bl);
    back_right.attach(cfg.br);
    imu = cfg.imu;

    // ARM ESCs
    front_left.writeMicroseconds(ESC_MIN);
    front_right.writeMicroseconds(ESC_MIN);
    back_left.writeMicroseconds(ESC_MIN);
    back_right.writeMicroseconds(ESC_MIN);

    delay(5000);

    /* Initialize the sensor */
    if(!imu.begin())
    {
        Serial.print("Oops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    delay(1000);
    imu.setExtCrystalUse(true);
}

void Drone::updateIMU()
{
    imu.getEvent(&event);
}

void Drone::fly(float throttle, float pitch, float yaw, float roll, unsigned long dt)
{
    float deltapitch = pitchPID.calculate(pitch, curr_pitch(), dt);
    float deltayaw   = yawPID.calculate(  yaw,   curr_yaw(),   dt);
    float deltaroll  = rollPID.calculate( roll,  curr_roll(),  dt);

    Serial.print("p: ");
    Serial.print(deltapitch);

    Serial.print(", y: ");
    Serial.print(deltayaw);

    Serial.print(", r: ");
    Serial.println(deltaroll);

    int fl_micros = flPID.calculatePeriodic(throttle + deltapitch + deltayaw + deltaroll, dt);          // cw
    int fr_micros = frPID.calculatePeriodic(throttle + deltapitch - deltayaw - deltaroll, dt);          // ccw
    int bl_micros = blPID.calculatePeriodic(throttle - deltapitch - deltayaw + deltaroll, dt);          // ccw
    int br_micros = brPID.calculatePeriodic(throttle - deltapitch + deltayaw - deltaroll, dt);          // cw

    fl_micros = constrain(fl_micros, ESC_MIN, ESC_MAX);
    fr_micros = constrain(fr_micros, ESC_MIN, ESC_MAX);
    bl_micros = constrain(bl_micros, ESC_MIN, ESC_MAX);
    br_micros = constrain(br_micros, ESC_MIN, ESC_MAX);

    front_left.writeMicroseconds(fl_micros);
    front_right.writeMicroseconds(fr_micros);
    back_left.writeMicroseconds(bl_micros);
    back_right.writeMicroseconds(br_micros);
}

float Drone::curr_roll()
{
    return clamp(event.orientation.z, -180, 180);
}

float Drone::curr_yaw()
{
    return clamp(event.orientation.x, -180, 180);
}

float Drone::curr_pitch()
{
    return clamp(event.orientation.y, -180, 180);
}