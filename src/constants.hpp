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
    namespace timer {
        constexpr unsigned long initial_spinup_duration = 5000;
        constexpr unsigned long deployment_total_duration = 7000;
        constexpr unsigned long despin_duration = 5000;
        constexpr unsigned long open_loop_duration = 5000;

        constexpr unsigned long arm_timeout = 2000;
        constexpr unsigned long controller_timeout = 5000;

    } // namespace timer
    namespace motor {
        constexpr int initial_spin_dc = 1300;
        constexpr int open_loop_spin_dc = 1600;
    } // namespace motor
    namespace imu {
        constexpr uint8_t max_failed_reads = 10;
    }
    namespace sd {
        constexpr char const *boot_filename = "boot.txt";
    }
} // namespace constants

#endif