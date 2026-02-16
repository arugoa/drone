#include "ELRSController.h"

ELRSController::ELRSController(int rx, int tx) : elrsSerial(rx, tx), crsf() {
    // throttle = 0;
    // yaw = 0;
    // pitch = 0;
    // roll = 0;
    left_switch = Switch::MID;
    right_switch = Switch::MID;
}

void ELRSController::begin() {
    elrsSerial.begin(115200);
    crsf.begin(elrsSerial);
}

void ELRSController::update() {
    crsf.update();

    // yaw = (crsf.getChannel(YAW_CHANNEL) - CHANNEL_MID) / CHANNEL_RANGE;
    // pitch = (crsf.getChannel(PITCH_CHANNEL) - CHANNEL_MID) / CHANNEL_RANGE;
    // roll = (crsf.getChannel(ROLL_CHANNEL) - CHANNEL_MID) / CHANNEL_RANGE;
    // throttle = (crsf.getChannel(THROTTLE_CHANNEL) - CHANNEL_MIN) / CHANNEL_RANGE;

    if (crsf.getChannel(LEFT_BUTTON_CHANNEL) > CHANNEL_MID) {
        left_button = true;
    } else {
        left_button = false;
    }

    if (crsf.getChannel(RIGHT_BUTTON_CHANNEL) > CHANNEL_MID) {
        right_button = true;
    } else {
        right_button = false;
    }

    int left_switch_val = crsf.getChannel(LEFT_SWITCH_CHANNEL);
    if (left_switch_val == 1000) {
        left_switch = Switch::DOWN;
    } else if (left_switch_val == 1503) {
        left_switch = Switch::MID;
    } else if (left_switch_val == 2000) {
        left_switch = Switch::UP;
    }

    int right_switch_val = crsf.getChannel(RIGHT_SWITCH_CHANNEL);
    if (right_switch_val == 1000) {
        right_switch = Switch::DOWN;
    } else if (right_switch_val == 1503) {
        right_switch = Switch::MID;
    } else if (right_switch_val == 2000) {
        right_switch = Switch::UP;
    }
}

float ELRSController::getThrottle() {
    return ((crsf.getChannel(THROTTLE_CHANNEL) - CHANNEL_MIN) / CHANNEL_RANGE);
}

float ELRSController::getYaw() {
    return ((crsf.getChannel(YAW_CHANNEL) - CHANNEL_MID) / CHANNEL_RANGE) * 180;
}

float ELRSController::getPitch() {
    return ((crsf.getChannel(PITCH_CHANNEL) - CHANNEL_MID) / CHANNEL_RANGE) *15;
}

float ELRSController::getRoll() {
    return ((crsf.getChannel(ROLL_CHANNEL) - CHANNEL_MID) / CHANNEL_RANGE) * 15;
}

bool ELRSController::getLeftButton() {
    return left_button;
}

bool ELRSController::getRightButton() {
    return right_button;
}

Switch ELRSController::getLeftSwitch() {
    return left_switch;
}

Switch ELRSController::getRightSwitch() {
    return right_switch;
}