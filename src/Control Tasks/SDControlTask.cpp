#include "SDControlTask.hpp"

#include "sfr.hpp"
#include "constants.hpp"

void SDControlTask::begin() {
    if (!SD.begin(SD_PIN)) {
        Serial.println("Error: SD interface failed to initialize");
    }
}

void SDControlTask::execute() {
    file = SD.open(constants::sd::filename, FILE_WRITE);
    file.printf("%lu,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", 
        millis(), 
        sfr::motor::pulse_width,
        sfr::imu::accel_x, 
        sfr::imu::accel_y, 
        sfr::imu::accel_z,
        sfr::imu::gyro_x,
        sfr::imu::gyro_y,
        sfr::imu::gyro_z);

    file.flush();
}