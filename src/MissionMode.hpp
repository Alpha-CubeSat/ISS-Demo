

#ifndef MISSION_MODE_HPP
#define MISSION_MODE_HPP

#include "timer.hpp"
#include <Arduino.h>

class MissionMode {
public:
    virtual void enter() = 0;
    virtual void execute();
    virtual void exit();

    virtual uint8_t get_id() = 0;
    virtual String get_name() = 0;
};

class InitialSpinupMode : public MissionMode {
public:
    void enter();
    void execute();

    uint8_t get_id() { return 0; };
    String get_name() { return "Initial Spinup"; };

private:
    Timer initial_spinup_timer;
};

class StandbyMode : public MissionMode {
public:
    void enter();
    void execute();

    uint8_t get_id() { return 1; };
    String get_name() { return "Standby"; };
};

class ArmedMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    uint8_t get_id() { return 2; };
    String get_name() { return "Armed"; };

private:
    Timer arm_timer;
};

class DeploymentMode : public MissionMode {
public:
    void enter();
    void execute();
    void exit();

    uint8_t get_id() { return 3; };
    String get_name() { return "Deployment"; };

private:
    Timer deploy_timer;
};

class DespinMode : public MissionMode {
public:
    void enter();
    void execute();

    uint8_t get_id() { return 4; };
    String get_name() { return "Despin"; };

private:
    Timer despin_timer;
};

class ControllerSpinupMode : public MissionMode {
public:
    void enter();
    void execute();

    uint8_t get_id() { return 5; };
    String get_name() { return "Controller Spinup"; };

private:
    Timer controller_timeout_timer;
};

class OpenLoopMode : public MissionMode {
public:
    void enter();
    void execute();

    uint8_t get_id() { return 6; };
    String get_name() { return "Open Loop"; };

private:
    Timer open_loop_timer;
};

enum as_action {
    SPINUP = 0,
    DEPLOY = 1,
    DESPIN = 2
};

class AutomatedSequenceMode : public MissionMode {
public:
    void enter();
    void execute();

    uint8_t get_id() { return 7; };
    String get_name() { return "Automated Sequence"; };

private:
    as_action current_action = SPINUP;

    bool as_open_loop_init = false;
    void as_open_loop_spinup();

    bool as_deploy_init = false;
    void as_deploy();

    bool as_despin_init = false;
    void as_despin();

    Timer open_loop_timer;
    Timer deploy_timer;
    Timer despin_timer;
};

void to_mode(MissionMode *mode);

#endif // MISSION_MODE_HPP