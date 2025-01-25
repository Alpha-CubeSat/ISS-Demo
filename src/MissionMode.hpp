

#ifndef MISSION_MODE_HPP
#define MISSION_MODE_HPP

#include "timer.hpp"

class MissionMode {
public:
    virtual void enter() = 0;
    virtual void execute();
    virtual void exit() = 0;
};

class StandbyMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();
};

class ArmedMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

private:
    Timer arm_timer;
};

class DeploymentMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

private:
    Timer deploy_timer;
};

class DespinMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

private:
    Timer despin_timer;
};

class ControllerSpinupMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

private:
    Timer controller_timeout_timer;
};

class OpenLoopMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

private:
    Timer open_loop_timer;
};

void to_mode(MissionMode *mode);

#endif // MISSION_MODE_HPP