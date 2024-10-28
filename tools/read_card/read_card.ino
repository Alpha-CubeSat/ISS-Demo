#include <Arduino.h>
#include <SD.h>

#define SD_PIN 4

void setup() {
    Serial.begin(9600);

    delay(10000);

    if (!SD.begin(SD_PIN)) {
        Serial.println("Error: SD interface failed to initialize");
        return;
    }

    File dataFile = SD.open("data.csv");
    if (dataFile) {
        while (dataFile.available()) {
            char data = dataFile.read();
            Serial.write(data);
        }
        dataFile.close();
    } else {
        Serial.println("Error: Failed to open file");
    }
    Serial.print("~");
}

void loop() {

}
