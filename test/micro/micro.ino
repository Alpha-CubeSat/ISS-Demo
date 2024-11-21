#include <Arduino.h>
#include <SD.h>

#define SD_PIN 4
#define BUILTIN_LED_PIN 13

int counter = 0;

void setup() {
    Serial.begin(9600);
    
    pinMode(BUILTIN_LED_PIN, OUTPUT);
    digitalWrite(BUILTIN_LED_PIN, HIGH);

    while (!Serial);

    if (!SD.begin(SD_PIN)) {
        while (true) {
            Serial.println("Error: SD interface failed to initialize");
            delay(1000);
        }
    }
}

void loop() {
    File writeFile = SD.open("test.txt", FILE_WRITE);
    writeFile.print("Line ");
    writeFile.println(counter);
    writeFile.flush();
    writeFile.close();

    File readFile = SD.open("test.txt", FILE_READ);
    if (readFile) {
        while (readFile.available()) {
            char data = readFile.read();
            Serial.print(data);
        }
        Serial.println();
    } else {
        Serial.println("Error: Failed to read file");
    }

    counter++;

    delay(3000);
}