#include <Wire.h>
#include <Arduino.h>
#include "actuatorController.h"
 
// Define the I2C Address
// NOTE: CHANGE FOR EACH DEVICE
#define I2C_ADDRESS 0x12
// 0x10: Receive L1, L6 (L1 sent to right, L6 sent to left))
// 0x11: Receive L2, L3 (L2 sent to left, L3 sent to right))
// 0x12: Receive L4, L5 (L4 sent to left, L5 sent to right)
 
// Now, initialize the floats that will be received:
float leftLeg = 0.0;
float rightLeg = 0.0;
 
// Define the Pin Numbers

// Right Actuator Pins (from the Perspective of the MCU)
int RILI = 1; // Right Internal Logic Input
int RELI = 2; // Right External Logic Input
int RPotPin = 3; // Right Potentiometer Feedback Pin

// Left Actuator Pins (from the Perspective of the MCU)
int LILI = 9; // Left Internal Logic Input
int LELI = 8; // Left External Logic Input
int LPotPin = 7; // Left Potentiometer Feedback Pin

// Create Instances of the Actuator Controller Class for the Left and Right Actuators
ActuatorController leftActuatorController(LPotPin, LILI, LELI);
ActuatorController rightActuatorController(RPotPin, RILI, RELI);

// Define the function to be called when data is received, receiveEvent
void receiveEvent(int numBytes) {
  if (numBytes != 9) {
    Serial.print("Received wrong number of bytes: ");
    Serial.println(numBytes);
    return;
  }
 
  Wire.read(); // Discard the first "command" byte
 
  byte buffer[8];
  int i = 0;
  while (Wire.available() && i < 8) {
    buffer[i++] = Wire.read();
  }
 
  memcpy(&leftLeg, &buffer[0], 4);
  memcpy(&rightLeg, &buffer[4], 4);
 
  Serial.println("Data Received");
}
 
void setup() {
  Wire.begin(I2C_ADDRESS);  // join I2C as slave
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  Serial.println("I2C Slave Initialized");

  // Set the Command Output Pins

    // Left Actuator Pins (from the Perspective of the MCU)
    pinMode(LILI, OUTPUT);
    pinMode(LELI, OUTPUT);
    pinMode(LPotPin, INPUT);

    // Right Actuator Pins (from the Perspective of the MCU)
    pinMode(RILI, OUTPUT);
    pinMode(RELI, OUTPUT);
    pinMode(RPotPin, INPUT);
}
 
void loop() {
  // Print for debugs
  Serial.print("Left Leg: "); Serial.print(leftLeg);
  Serial.print(" | Right Leg: "); Serial.println(rightLeg);
  delay(5);

  // Output Motion Commands (mm conversion and base height subtraction already occur in ros2)
  leftActuatorController.setTargetPosition(leftLeg);
  rightActuatorController.setTargetPosition(rightLeg);

  leftActuatorController.update();
  rightActuatorController.update();
}