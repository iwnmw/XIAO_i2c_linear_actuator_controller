#include "actuatorController.h"
#include <Arduino.h>

// Define Error Tolerance
#define errorTolerance 1.0f // 5mm Tolerance for Position Control

// Define Maximum Position and Minimum Position
#define maxPosition 200.0f // Maximum Position in mm (Adjust if Stroke Length is Different)
#define minPosition 1.0f // Measure Your Actuator's Extension when Fully Retracted to Improve Position Accuracy

// ActuatorController class implementation

ActuatorController::ActuatorController(int potPin, int ILI, int ELI)
    : potPin(potPin), ILI(ILI), ELI(ELI), targetPosition(0.0f) {
    pinMode(ILI, OUTPUT);
    pinMode(ELI, OUTPUT);
    pinMode(potPin, INPUT);
    stop(); // Initially Stop Actuator
}

// Define the setTargetPosition Function to Set the Commanded Position
void ActuatorController::setTargetPosition(float target) {
    targetPosition = target;
}

// Define the readPosition Function to Read the Position of the Linear Actuator
float ActuatorController::readPosition() {
    // Read the potentiometer value and map it to a position in mm
    int potValue = analogRead(potPin);
    // Assuming the potentiometer gives a range of 0-1023 corresponding to 0-200mm
    float position = map(potValue, 7, 1023, minPosition, maxPosition); // Computed Some Calibration Constants in Matlab
    // Testing Block:
    /*
    Serial.print("Potentiometer Feedback: ");
    Serial.println(potValue);
    Serial.print("Actuator Position: ");
    Serial.println(position);
    */

    // Return Computed Position
    return position;
}

// Define the Update Function to Constantly Update the Controller with New Feedback
void ActuatorController::update() {
    float currentPosition = readPosition();
    if (currentPosition < targetPosition - errorTolerance) { // If Current Position is 5mm Below Target
        extend();
    } else if (currentPosition > targetPosition + errorTolerance) { // If Current Position is 5mm Above Target
        retract();
    } else {
        stop(); // If Within 5mm of Target, Stop
    }
}

// Extension Function
void ActuatorController::extend() {
    digitalWrite(ILI, LOW); // Set Internal Logic Input Low
    digitalWrite(ELI, HIGH);  // Set External Logic Input High
}

// Retraction Function
void ActuatorController::retract() {
    digitalWrite(ILI, HIGH);  // Set Internal Logic Input High
    digitalWrite(ELI, LOW); // Set External Logic Input Low
}

// Stop Function
void ActuatorController::stop() {
    digitalWrite(ILI, LOW);  // Set Internal Logic Input Low
    digitalWrite(ELI, LOW);  // Set External Logic Input Low
}