#include "Drone.h"

Drone::Drone()
{
    PID::config yawCfg(0.1, 0, 0, 180, 30);
    PID::config pitchCfg(0.1, 0, 0, 180, 30);
    PID::config rollCfg(0.1, 0, 0, 180, 30);

    yawPID = PID(yawCfg);
    pitchPID = PID(pitchCfg);
    rollPID = PID(rollCfg);

    OpenLoop::config flCfg(1145, 0.568*THROTTLE_SENS, 0.000104, ESC_MAX);
    OpenLoop::config frCfg(1000, 1.2*THROTTLE_SENS, 0, ESC_MAX);
    OpenLoop::config blCfg(1000, THROTTLE_SENS, 0, ESC_MAX);
    OpenLoop::config brCfg(1140, 1.5*THROTTLE_SENS, 0, ESC_MAX);

    flPID = OpenLoop(flCfg);
    frPID = OpenLoop(frCfg);
    blPID = OpenLoop(blCfg);
    brPID = OpenLoop(brCfg);
}

void Drone::setup(config cfg, bool no_imu)
{
    front_left.attach(cfg.fl);
    front_right.attach(cfg.fr);
    back_left.attach(cfg.bl);
    back_right.attach(cfg.br);
    if (!no_imu) {
        imu = Adafruit_BNO055(cfg.imu);
    }

    // ARM ESCs
    front_left.writeMicroseconds(ESC_MIN);
    front_right.writeMicroseconds(ESC_MIN);
    back_left.writeMicroseconds(ESC_MIN);
    back_right.writeMicroseconds(ESC_MIN);

    delay(5000);

    if (!no_imu) {
        /* Initialize the sensor */
        if(!imu.begin())
        {
            Serial.print("Oops, no BNO055 detected ... Check your wiring or I2C ADDR!");
            while(1);
        }
        delay(1000);
        imu.setExtCrystalUse(true);
    }
}

void Drone::updateIMU()
{
    imu.getEvent(&event);
}

void Drone::fly(float throttle, float pitch, float yaw, float roll, unsigned long dt, bool no_imu)
{
    if (no_imu) {
        int fl_micros = flPID.setSpeed(throttle);
        Serial.println(fl_micros);
        front_left.writeMicroseconds(fl_micros);

        return;
    }

    float deltapitch = pitchPID.calculate(pitch, curr_pitch(), dt);
    float deltayaw   = yawPID.calculate(  yaw,   curr_yaw(),   dt);
    float deltaroll  = rollPID.calculate( roll,  curr_roll(),  dt);

    // Serial.print("t: ");
    // Serial.print(throttle);
    // Serial.print("p: ");
    // Serial.print(deltapitch);
    // Serial.print(", y: ");
    // Serial.print(deltayaw);
    // Serial.print(", r: ");
    // Serial.println(deltaroll);

    int fl_micros = flPID.setSpeed(throttle + deltapitch + deltayaw + deltaroll);          // cw
    int fr_micros = frPID.setSpeed(throttle + deltapitch - deltayaw - deltaroll);          // ccw
    int bl_micros = blPID.setSpeed(throttle - deltapitch - deltayaw + deltaroll);          // ccw
    int br_micros = brPID.setSpeed(throttle - deltapitch + deltayaw - deltaroll);          // cw

    Serial.print("1: ");
    Serial.print(fl_micros);
    Serial.print(" 2: ");
    Serial.print(fr_micros);
    Serial.print(" 3: ");
    Serial.print(bl_micros);
    Serial.print(" 4: ");
    Serial.println(br_micros);

    front_left.writeMicroseconds(fl_micros);
    front_right.writeMicroseconds(fr_micros);
    back_left.writeMicroseconds(bl_micros);
    back_right.writeMicroseconds(br_micros);
}

void Drone::nofly()
{
    front_left.writeMicroseconds(1000);
    front_right.writeMicroseconds(1000);
    back_left.writeMicroseconds(1000);
    back_right.writeMicroseconds(1000);
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
    // To fix the pitch frame
    return clamp(-1 * event.orientation.y, -180, 180);
}