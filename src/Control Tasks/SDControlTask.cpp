#include "SDControlTask.hpp"

#include "constants.hpp"
#include "sfr.hpp"

void SDControlTask::begin() {
    if (!SD.begin(SD_PIN)) {
        vlogln("Error: SD interface failed to initialize");
        return;
    }

    File root = SD.open("/");

    if (root) {
        while (true) {
            File entry = root.openNextFile();
            if (entry) {
                file_count++;
                entry.close();
            } else {
                break;
            }
        }
        root.close();
    }

    static char buffer[20];
    sprintf(buffer, "data%d.csv", file_count + 1);

    sfr::sd::filename = buffer;
}

void SDControlTask::execute() {
    file = SD.open(sfr::sd::filename, FILE_WRITE);

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