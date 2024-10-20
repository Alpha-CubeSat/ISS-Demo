#include "SDControlTask.hpp"

#include "constants.hpp"
#include "sfr.hpp"

void SDControlTask::begin() {
    if (!SD.begin(SD_PIN)) {
        vlogln("Error: SD interface failed to initialize");
    }
}

void SDControlTask::execute() {
    file = SD.open(constants::sd::filename, FILE_WRITE);

    String data = String(millis()) + "," +
                  String(sfr::motor::pulse_width_angle) + "," +
                  String(sfr::imu::accel_x) + "," +
                  String(sfr::imu::accel_y) + "," +
                  String(sfr::imu::accel_z) + "," +
                  String(sfr::imu::gyro_x) + "," +
                  String(sfr::imu::gyro_y) + "," +
                  String(sfr::imu::gyro_z);

    file.println(data);

    file.flush();
    file.close();
}