#include <Arduino.h>
#include <IRremote.hpp> // include the library

#define IRPin 11
// test script for our NEC encoded remote. Decodes the button presses.

void handleOverflow() {
    Serial.println("Overflow detected");
    //Serial.println(F("Try to increase the \"RAW_BUFFER_LENGTH\" value of " STR(RAW_BUFFER_LENGTH) " in " __FILE__));
    // see also https://github.com/Arduino-IRremote/Arduino-IRremote#compile-options--macros-for-this-library
    IrReceiver.stopTimer();
    IrReceiver.restartTimer(100000); // to compensate for 100 ms stop of receiver. This enables a correct gap measurement.
}

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IRPin, ENABLE_LED_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {
      if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            handleOverflow();
        }
        else{ 
        IrReceiver.resume();
        if (IrReceiver.decodedIRData.command == 0xA) {
            Serial.println("Upper Right");
        } 
        else if (IrReceiver.decodedIRData.command == 0xB) {
            Serial.println("Lower Right");
        } 
        else if (IrReceiver.decodedIRData.command == 0xC){
            Serial.println("Upper Left");
        }
        else if (IrReceiver.decodedIRData.command == 0xD){
            Serial.println("Lower Left");
        }
        else if (IrReceiver.decodedIRData.command == 0xF){
            Serial.println("Power Button");
        }
        else if (IrReceiver.decodedIRData.command == 0xE){
            Serial.println("Mute Button");
        }
        else if (IrReceiver.decodedIRData.command == 0x1C){
            Serial.println("CC Button");
        }
        else if (IrReceiver.decodedIRData.command == 0x18){
            Serial.println("OK Button");
        }
        else{
          Serial.println(IrReceiver.decodedIRData.command);
        }
      }
    }
  }

