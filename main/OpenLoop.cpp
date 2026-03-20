#include "OpenLoop.h"

OpenLoop::OpenLoop()
{
    a_0 = 0;
    a_1 = 1;
    a_2 = 0;
    outCap = 2000;
}

OpenLoop::OpenLoop(config cfg)
{
    a_0 = cfg.a_0;
    a_1 = cfg.a_1;
    a_2 = cfg.a_2;
    outCap = cfg.outCap;
}

double OpenLoop::setPower(double power)
{
    return power;
}

double OpenLoop::setSpeed(double speed)
{
    double power = a_0 + a_1*speed + a_2*speed*speed;
    if (power > outCap) {
        power = outCap;
    }

    return power;
}