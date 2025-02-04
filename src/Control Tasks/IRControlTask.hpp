#ifndef IR_CONTROL_TASK_HPP
#define IR_CONTROL_TASK_HPP

#include "sfr.hpp"
#include "timer.hpp"
#include <stdint.h>

class IRControlTask {
public:
    void begin();
    void execute();

private:
    void parse_command();
    Event get_event(uint8_t button);
    void handle_overflow();

    uint16_t button_selected = -1;
};

#endif