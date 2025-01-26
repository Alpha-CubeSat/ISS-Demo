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
    if (millis() - start_time >= duration) {
        active = false;
        return true;
    }
    return false;
}

bool Timer::is_past(unsigned long interval) {
    if (!active) {
        return false;
    }
    if (millis() - start_time >= interval) {
        return true;
    }
    return false;
}

void Timer::reset() {
    active = false;
}