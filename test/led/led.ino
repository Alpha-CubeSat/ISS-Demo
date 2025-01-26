#include <Arduino.h>

#define RED_LED_PIN A0
#define GREEN_LED_PIN A2
#define BLUE_LED_PIN A1

inline void setWhite() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
}

inline void setRed() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

inline void setGreen() {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

inline void setBlue() {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
}

inline void setYellow() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

inline void setPurple() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
}

inline void setOff() {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

void setup() {
    Serial.begin(9600);

    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
    setRed();
    delay(1000);

    setGreen();
    delay(1000);

    setBlue();
    delay(1000);

    setYellow();
    delay(1000);

    setPurple();
    delay(1000);

    setWhite();
    delay(1000);
    
    setOff();
    delay(5000);
}