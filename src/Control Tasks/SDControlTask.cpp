#include "SDControlTask.hpp"
#include "constants.hpp"
#include "sfr.hpp"

void SDControlTask::begin() {
    if (!SD.begin(SD_PIN)) {
        vlogln("Error: SD interface failed to initialize");
        return;
    }
    //remove old files
    if(SD.exists(constants::sd::filename)){
        SD.remove(constants::sd::filename);
    }

    File file = SD.open(constants::sd::filename, FILE_WRITE);
    String header = String("Time") + "," + String("Gyro Z") + "," +  String("Error") + "," +  String("Delta Error") + "," + String("Delta Time") + "," + String("Duty Cycle") + "," + String("Angle") + "," + String("Proportional") + "," + String("Derivative");
    file.println(header);
    file.flush();
    file.close();
}

void SDControlTask::execute() {
    //TODO Only record after spin up is done 
    file = SD.open(constants::sd::filename, FILE_WRITE);
    String data = String(millis()) + "," +   //row A
            String(sfr::imu::gyro_z) + "," + //row B
            String(sfr::controller::record_error) + "," +  //row C
            String(sfr::controller::record_delta_error) + "," + //row D
            String(sfr::controller::record_delta_time) + "," + //row E
            String(sfr::controller::record_duty_cycle) + "," + //row F
            String(sfr::controller::record_angle) + "," + //row G
            String(sfr::controller::record_prop)+ "," + //row H
            String(sfr::controller::record_derivative)+ "," + 
            String(sfr::controller::record_integral);
            //   String(sfr::motor::pulse_width) + "," + 
            //   String(sfr::imu::accel_x) + "," + 
            //   String(sfr::imu::accel_y) + "," + 
            //   String(sfr::imu::accel_z) + "," + 
            //   String(sfr::imu::gyro_x) + "," + 
            //   String(sfr::imu::gyro_y) + "," +

    file.println(data);

    file.flush();
    file.close();
}