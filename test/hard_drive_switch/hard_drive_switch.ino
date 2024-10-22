// Including Libraries
#include <Arduino.h>
#include <SAMD21turboPWM.h>
TurboPWM pwm;
//Pins on Adafruit Feather M0
#define PWMPin 10 // PWM pin for ESC control
#define IRPin 11
#define SwitchPin 6
// Global Variables
int input = 0;
int val = 0;
int PWM = 0;
char rx_byte = 0;
String rx_str = "";
int rx_cmd = 0;


//type in a command into the serial monitor
// 1 turns the switch on
// 2 turns the switch off
// 3 initializes the hard drive (need to do each time it is powered) the hard drive will not spin.
// 4 sets the hard drive to a pwm input of 90 (spinning it)

int getCommand() {
  rx_byte = Serial.read();     // reads and stores the character
  // Tell microcontroller how to read commands
  if ((rx_byte >= '0') && (rx_byte <= '9')) {  // if the character is a positive number
    rx_str += rx_byte; // put the numbers together in a string
    // ex. "2" "2" becomes "22"
  }
  else if (rx_byte == '\n') {   // if end of command
    // Convert number string into an actual number
    rx_cmd = rx_str.toInt(); //ex. "22" becomes 22
    // only comment in one of the two lines below
    input = rx_cmd; Serial.print("INPUT = "); Serial.println(input); // use this line to try new PWM ranges
    rx_str = ""; // clears memory for next command
    rx_cmd = 0;
  }
  else { // if enterted byte is not 0-9 or \n
    Serial.println("Invalid character in user input");
  }
  return input;
}


void setup() {
  Serial.begin(9600);
  // TCC Timer 0 for ESC, IR Receiver on timer 2 (default for IRremote library)
  pwm.setClockDivider(1, false); // not dividing main clock anymore 
  // changing frequency on TCC clock fo pwm pin
  pwm.timer(0, 8, 60000, false); 
  // Declaring Switch Pin as an output
  pinMode(SwitchPin,OUTPUT); 
}

void loop() {
  if (Serial.available() > 0) {   // checks if a command is typed in
    val = getCommand();
  }
  if (val == 1){
    digitalWrite(SwitchPin, HIGH);
    Serial.println("ESC is ON");
    Serial.println("PWM: "); Serial.print(PWM);
  }
  if (val == 2){
    digitalWrite(SwitchPin, LOW);
    Serial.println("ESC is OFF");
  }
  if (val == 3){
    Serial.println("Initializing Hard Drive");
    Serial.println("PWM = 40");
    PWM = 40;
  }
  if (val == 4){
    Serial.println("Spinning Hard Drive");
    Serial.println("PWM = 90");
    PWM = 90;
  }
  if (val == 0){
    Serial.println("No Command Typed!");
  }
  pwm.analogWrite(PWMPin, PWM);
  delay(30);
}
