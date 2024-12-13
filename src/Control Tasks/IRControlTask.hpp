#ifndef IR_CONTROL_TASK_HPP
#define IR_CONTROL_TASK_HPP

#include <stdint.h>
#include "timer.hpp"

class IRControlTask {
public:
    void begin();
    void execute();

private:
    void parse_command();
    void handle_overflow();

    uint16_t button_selected = -1;

    Timer arm_timer;
    Timer deploy_led_timer;
};

#endif