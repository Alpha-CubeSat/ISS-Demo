#include "SDControlTask.hpp"
#include "constants.hpp"
#include "pins.hpp"
#include "sfr.hpp"

void SDControlTask::begin() {
    if (!SD.begin(SD_PIN)) {
        sfr::sd::failed_init = true;
        return;
    } else {
        sfr::sd::failed_init = false;
    }

    File boot = SD.open(constants::sd::boot_filename, O_RDWR);
    if (boot) {
        String read_out = boot.readStringUntil('\n');
        file_count = read_out.toInt();
        boot.seek(0);
        file_count++;
        if (boot.println(file_count) == 0) {
            vlogln("Error: SD boot write failed (existing)");
        }
        boot.close();
    } else {
        boot = SD.open(constants::sd::boot_filename, FILE_WRITE);
        if (!boot) {
            vlogln("Error: SD boot open failed");
        }
        if (boot.println(file_count) == 0) {
            vlogln("Error: SD boot write failed (new)");
        }
        boot.flush();
        boot.close();
    }

    static char buffer[20];
    sprintf(buffer, "data_%d.csv", file_count);

    sfr::sd::log_filename = buffer;
}

void SDControlTask::execute() {
    if (sfr::sd::failed_init) {
        return;
    }

    file = SD.open(sfr::sd::log_filename, FILE_WRITE);
    if (!file) {
        vlogln("Error: SD file open failed");
        return;
    }

    String data = String(sfr::mission::timestamp) + "," +
                  String(sfr::mission::mode->get_id()) + "," +
                  String(sfr::controller::record_duty_cycle) + "," +
                  String(sfr::imu::accel_x) + "," +
                  String(sfr::imu::accel_y) + "," +
                  String(sfr::imu::accel_z) + "," +
                  String(sfr::imu::gyro_x) + "," +
                  String(sfr::imu::gyro_y) + "," +
                  String(sfr::imu::gyro_z);

    if (file.println(data) == 0) {
        vlogln("Error: SD write failed");
    }

    file.flush();
    file.close();
}