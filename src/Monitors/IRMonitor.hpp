/**
 * @file IRMonitor.hpp
 * @author csg83
 *
 * @brief Reads IR data and updates the SFR
 */

#ifndef IR_MONITOR_HPP
#define IR_MONITOR_HPP

#include "sfr.hpp"
#include "timer.hpp"
#include <stdint.h>

class IRMonitor {
public:
    void begin();
    void execute();

private:
    void parse_command();
    Event get_event(uint16_t button);
    void handle_overflow();

    uint16_t button_selected = -1;
};

#endif // IR_MONITOR_HPP