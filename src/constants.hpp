/**
 * @file constants.hpp
 * @author csg83
 *
 * @brief Constants and other definitions
 */

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

enum class Event : uint8_t {
    arm_button_received = 0,
    cs_button_received = 1,
    deploy_button_received = 2,
    despin_button_received = 3,
    open_loop_button_received = 4,
    unknown_button_received = 5,
    ir_overflow_detected = 6,

    imu_init_failure = 7,
    imu_read_failure = 8,

    first_burn_started = 9,
    second_burn_started = 10
};

namespace constants {
    namespace mission {
        constexpr uint32_t cycle_time = 50;
    } // namespace mission
    namespace timer {
        constexpr unsigned long initial_spinup_duration = 5000;

        constexpr unsigned long deployment_total_duration = 7000;
        constexpr unsigned long deployment_standby_duration = 3000;
        constexpr unsigned long deployment_actuate_duration = 400;
        constexpr unsigned long deployment_break = deployment_standby_duration + deployment_actuate_duration + 500;

        constexpr unsigned long despin_duration = 7000;
        constexpr unsigned long open_loop_duration = 7000;

        constexpr unsigned long as_hold_duration = 15000;
        constexpr unsigned long as_start_blink = 10000;
        constexpr unsigned long as_break_duration = 3000;

        constexpr unsigned long ir_invalid_led_duration = 3000;

        constexpr unsigned long arm_timeout = 2000;
        constexpr unsigned long controller_spinup_duration = 60000;

        constexpr unsigned long blink_duration = 200;

    } // namespace timer
    namespace motor {
        constexpr int initial_spin_dc = 1230;
        constexpr int open_loop_spin_dc = 1600;
    } // namespace motor
    namespace imu {
        constexpr uint8_t max_failed_reads = 10;
    }
    namespace sd {
        constexpr char const *boot_filename = "boot.txt";
    }
} // namespace constants

#endif // CONSTANTS_HPP