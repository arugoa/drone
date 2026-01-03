#include "drone_algo.h"

Drone::Drone(config cfg)
{
    front_left.attach(cfg.fl);
    front_right.attach(cfg.fr);
    back_left.attach(cfg.bl);
    back_right.attach(cfg.br);

    // imu = cfg.imu;
}

void Drone::fly(float throttle, float pitch, float yaw, float roll)
{
    float deltapitch = pitchPID.calculate(pitch, curr_pitch(), dt);
    float deltayaw = yawPID.calculate(yaw, curr_yaw(), dt);
    float deltaroll = rollPID.calculate(roll, curr_roll(), dt);

    // need to put PID into all of these
    int fl_micros = throttle*MAX_THROTTLE + deltapitch + deltayaw + deltaroll;      // cw
    int fr_micros = -(throttle*MAX_THROTTLE + deltapitch - deltayaw - deltaroll);   // ccw
    int bl_micros = -(throttle*MAX_THROTTLE - deltapitch - deltayaw + deltaroll);   // ccw
    int br_micros = throttle*MAX_THROTTLE - deltapitch + deltayaw - deltaroll;      // cw

    front_left.writeMicroseconds(fl_micros);
    front_right.writeMicroseconds(fr_micros);
    back_left.writeMicroseconds(bl_micros);
    back_right.writeMicroseconds(br_micros);
}