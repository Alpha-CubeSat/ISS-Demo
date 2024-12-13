#include "timer.hpp"
#include <Arduino.h>

void Timer::start(unsigned long interval) {
    start_time = millis();
    duration = interval;
    active = true;
}

bool Timer::is_elapsed() {
    if (!active) {
        return false;
    }
    return millis() - start_time >= duration;
}

void Timer::reset() {
    active = false;
}