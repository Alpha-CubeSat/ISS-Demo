#include "SDControlTask.hpp"
#include "constants.hpp"
#include "sfr.hpp"

void SDControlTask::begin() {
    if (!SD.begin(SD_PIN)) {
        vlogln("Error: SD interface failed to initialize");
        return;
    }

    File boot = SD.open(constants::sd::boot_filename, O_RDWR);
    if (boot) {
        String read_out = boot.readStringUntil('\n');
        file_count = read_out.toInt();
        boot.seek(0);
        file_count++;
        boot.println(file_count);
        boot.close();
    } else {
        boot = SD.open(constants::sd::boot_filename, FILE_WRITE);
        boot.println(file_count);
        boot.flush();
        boot.close();
    }

    static char buffer[20];
    sprintf(buffer, "data_%d.csv", file_count);

    sfr::sd::log_filename = buffer;
}

void SDControlTask::execute() {
    file = SD.open(sfr::sd::log_filename, FILE_WRITE);

    String data = String(millis()) + "," +
                  String(sfr::motor::pulse_width) + "," +
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