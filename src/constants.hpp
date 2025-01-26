#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <Arduino.h>

#ifdef VERBOSE
#define vlogln(...) Serial.println(__VA_ARGS__)
#define vlog(...) Serial.print(__VA_ARGS__)
#define vlogf(...) Serial.printf(__VA_ARGS__)
#else
#define vlogln(...)
#define vlog(...)
#define vlogf(...)
#endif

namespace constants {
    namespace mission {
        constexpr unsigned long deployment_length = 5000;
        constexpr unsigned long open_loop_length = 5000;
        constexpr unsigned long despin_length = 5000;
        constexpr unsigned long controller_timeout_length = 5000;
    } // namespace mission
    namespace flight {
        constexpr unsigned long initial_hold_time = 5000;
        constexpr unsigned long initial_spin_time = 10000; // TODO: This is kinda hacky but I'm lazy rn
    } // namespace flight
    namespace ir {
        // TODO: Move some of these
        constexpr unsigned long arm_timeout = 2000;
        constexpr unsigned long deploy_led_timeout = 3000;
    } // namespace ir
    namespace motor {
        constexpr int spinup_increment = 150;
    }
    namespace imu {
        constexpr uint8_t max_failed_reads = 10;
    }

    namespace sd {
        constexpr char const *boot_filename = "boot.txt";
    }
} // namespace constants

#endif