# Seeeduino XIAO I2C Linear Actuator Controllers

A small stack developed to control 6 linear actuator controllers with potentiometer feedback for a Stewart platform using 3 Seeeduino XIAO (SAMD21) microcontrollers and I2C communication from a separate controller responsible for motion planning. The microcontrollers provide simple extend or retract commands to L298 motor drivers, which drive Actuonix P16 linear actuators.

## Usage
L298 motor drivers provide a positive or negative voltage output to a motor depending on what logic they receive. Each motor driver has capacity to handle two motors. The logic inputs for both motors are four pins grouped together: rightmost logic inputs handle the rightmost motor, and the leftmost logic inputs handle the leftmost motor. Thus, each motor receives an external logic input (the logic input on the outside of the group of 4 logic pins) and an internal logic input (the logic input on the inside of the group of 4 logic pins).

Each logic input operates on simple, HI/LO logic. If the internal logic input (ILI) is set to LO while the external logic input (ELI) is set to HI, a positive voltage is sent to the linear actuator and the actuator extends. If the ILI is HI while the ELI is low, the actuator retracts as a negative voltage is sent. If both pins are set to LO, the actuator remains stationary.

The stack requires potentiometer feedback from actuators to run successfully. Each microcontroller reads the potentiometer feedback from the two actuators it controls and compares it to the commanded position. If the error tolerance (which may be changed in the actuatorController.cpp class file) is not met, the actuator will either extend or retract as necessary to meet it.

The sketch must be individually uploaded to every microcontroller, and to ensure that each microcontroller has the correct I2C address, the address defined on line 7 of main.cpp MUST be manually changed for every upload. With the correct addresses, each MCU will successfully receive whatever values are sent over the I2C bus and control the motor drivers!