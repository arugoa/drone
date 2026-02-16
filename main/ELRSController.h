#pragma once
#include <Arduino.h>
#include "FUTABA_SBUS.h"
#include "SBusTracker.h"

class ELRSController {
public:
    void begin();
    void update();

    float getThrottle();
    float getRoll();
    float getPitch();
    float getYaw();

    bool getButton(int index);

private:
    FUTABA_SBUS sBus;

    SBusTracker xAxis;
    SBusTracker yAxis;
    SBusTracker rxAxis;
    SBusTracker ryAxis;

    void updateTrackers();
};
