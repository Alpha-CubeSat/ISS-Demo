#include "SDControlTask.hpp"
#include "constants.hpp"
#include "sfr.hpp"

void SDControlTask::begin() {
    if (!SD.begin(SD_PIN)) {
        vlogln("Error: SD interface failed to initialize");
        return;
    }
    //remove old files
}

void SDControlTask::execute() {
    file = SD.open(constants::sd::filename, FILE_WRITE);
    //TODO: add recording of error, delta error, time, delta time, and anything else 
    String data = String(millis()) + "," + 
            //   String(sfr::motor::pulse_width) + "," + 
            //   String(sfr::imu::accel_x) + "," + 
            //   String(sfr::imu::accel_y) + "," + 
            //   String(sfr::imu::accel_z) + "," + 
            //   String(sfr::imu::gyro_x) + "," + 
            //   String(sfr::imu::gyro_y) + "," + 
            String(sfr::imu::gyro_z) + "," + 
            String(sfr::controller::record_error) + "," + 
            String(sfr::controller::record_delta_error) + "," +
            String(sfr::controller::record_delta_time) + "," + 
            String(sfr::controller::record_duty_cycle) + "," + 
            String(sfr::controller::record_angle) + "," + 
            String(sfr::controller::record_prop)+ "," + 
            String(sfr::controller::record_derivative)+ "," + 
            String(sfr::controller::record_integral);

    file.println(data);

    file.flush();
    file.close();
}