#pragma once // Prevent Multiple Inclusions of the Header File

class ActuatorController {
    public:
        ActuatorController(int potPin, int ILI, int ELI); // Sets Pins for the Potentiometer Feedback and the Internal/External Logic Inputs (ILI and ELI, Respectively)
        void setTargetPosition(float target); // Set the Commanded Position
        void update(); // This Gets Called in the Loop to Constantly Update the Controller with New Feedback

    private:
        int potPin; // Pin for Potentiometer Feedback
        int ILI; // Pin for Internal Logic Input
        int ELI; // Pin for External Logic Input
        float targetPosition; // Float Value that Represents the Commanded Actuator Position

        float readPosition(); // Function to Read the Position of the Linear Actuator
        void extend(); // Extension Function
        void retract(); // Retraction Function
        void stop(); // Function to Pause Actuator Motion Once It's Close Enough to the Desired Position
};