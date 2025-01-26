

#ifndef MISSION_MODE_HPP
#define MISSION_MODE_HPP

#include "timer.hpp"
#include <Arduino.h>

class MissionMode {
public:
    virtual void enter() = 0;
    virtual void execute();
    virtual void exit() = 0;

    virtual String get_name() = 0;
};

class InitialSpinupMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    String get_name() { return "Initial Spinup"; };

private:
    Timer initial_spinup_timer;
};

class StandbyMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    String get_name() { return "Standby"; };
};

class ArmedMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    String get_name() { return "Armed"; };

private:
    Timer arm_timer;
};

class DeploymentMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    String get_name() { return "Deployment"; };

private:
    Timer deploy_timer;
};

class DespinMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    String get_name() { return "Despin"; };

private:
    Timer despin_timer;
};

class ControllerSpinupMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    String get_name() { return "Controller Spinup"; };

private:
    Timer controller_timeout_timer;
};

class OpenLoopMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    String get_name() { return "Open Loop"; };

private:
    Timer open_loop_timer;
};

void to_mode(MissionMode *mode);

#endif // MISSION_MODE_HPP