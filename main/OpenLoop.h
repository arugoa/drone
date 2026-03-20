class OpenLoop {
public:
    struct config
    {
        float a_0 = 0;
        float a_1 = 1;
        float a_2 = 0;
        float outCap = 2000;

        config(float _a0, float _a1, float _a2, float _outCap)
        : a_0(_a0), a_1(_a1), a_2(_a2), outCap(_outCap) {}
    };

    OpenLoop();
    OpenLoop(config cfg);
    double setPower(double power);
    double setSpeed(double speed);

private:
    float a_0, a_1, a_2;
    float outCap;
};