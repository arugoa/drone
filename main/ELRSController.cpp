#include "ELRSController.h"

#define XAXIS_CHANNEL 3
#define YAXIS_CHANNEL 2
#define RX_CHANNEL 0
#define RY_CHANNEL 1

#define MIN_SIGNAL 190
#define MAX_SIGNAL 1790

void ELRSController::begin() {
    sBus.begin();
}

void ELRSController::update() {
    sBus.FeedLine();

    if (sBus.toChannels == 1) {
        sBus.UpdateChannels();
        sBus.toChannels = 0;

        updateTrackers();
    }
}

void ELRSController::updateTrackers() {
    xAxis.add(sBus.channels[XAXIS_CHANNEL]);
    yAxis.add(sBus.channels[YAXIS_CHANNEL]);
    rxAxis.add(sBus.channels[RX_CHANNEL]);
    ryAxis.add(sBus.channels[RY_CHANNEL]);
}

float ELRSController::getThrottle() {
    return (float)xAxis.get_estimated() / MAX_SIGNAL;
}

float ELRSController::getRoll() {
    return (float)rxAxis.get_estimated() / MAX_SIGNAL;
}

float ELRSController::getPitch() {
    return (float)yAxis.get_estimated() / MAX_SIGNAL;
}

float ELRSController::getYaw() {
    return (float)ryAxis.get_estimated() / MAX_SIGNAL;
}
