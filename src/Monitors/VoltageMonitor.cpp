/**
 * @file VoltageMonitor.cpp
 * @author csg83
 *
 * @brief Reads battery voltage data and updates the SFR
 */

#include "VoltageMonitor.hpp"
#include "pins.hpp"
#include "sfr.hpp"

void VoltageMonitor::execute() {
    int analog_read = analogRead(VOLTAGE_PIN);
    float pin_voltage = ((float)analog_read / 1023.0) * 3.3;
    sfr::voltage::battery = pin_voltage * (9550.0 + 3088.0) / 3088.0;
}