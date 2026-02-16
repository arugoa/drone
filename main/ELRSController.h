#include <SoftwareSerial.h>
#include <AlfredoCRSF.h>

constexpr int YAW_CHANNEL = 1;
constexpr int PITCH_CHANNEL = 2;
constexpr int ROLL_CHANNEL = 4;
constexpr int THROTTLE_CHANNEL = 3;

constexpr int LEFT_BUTTON_CHANNEL = 5;
constexpr int RIGHT_BUTTON_CHANNEL = 8;
constexpr int LEFT_SWITCH_CHANNEL = 6;
constexpr int RIGHT_SWITCH_CHANNEL = 7;

constexpr float CHANNEL_MIN = 990;
constexpr float CHANNEL_MAX = 2011;
constexpr float CHANNEL_RANGE = CHANNEL_MAX - CHANNEL_MIN;
constexpr float CHANNEL_MID = 1500;

enum Switch {UP, MID, DOWN};

class ELRSController {
    public:
        ELRSController(int rx, int tx);

        void begin();
        void update();

        float getThrottle();
        float getYaw();
        float getPitch();
        float getRoll();

        bool getLeftButton();
        bool getRightButton();
        Switch getLeftSwitch();
        Switch getRightSwitch();

    private:
        SoftwareSerial elrsSerial;
        AlfredoCRSF crsf;
        
        bool left_button;
        bool right_button;

        Switch left_switch;
        Switch right_switch;
};