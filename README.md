# Tyre-Inflator-Project
A tyre inflator project for the PIC18F45K22

## About the Project
This project is an automatic tire inflator designed to simplify and automate the inflation process. It features a GLCD display for real-time feedback, buttons for user interaction, and sensors to monitor temperature and pressure. The system uses a state machine for efficient operation, PWM for compressor control, and serial communication for debugging and potential extensions. It has been developed on the PIC18F45K22 microcontroller with the EASYPIC7 board.

## Features
### User Interaction
- **GLCD display** to present status, sensor readings, and animations.
- **Buttons for user input**:
  - **Increase Pressure**: Increment the desired tyre pressure (`RC0`).
  - **Decrease Pressure**: Decrement the desired tyre pressure (`RC1`).
  - **Confirm Selection**: Confirm the desired pressure (`RC2`).
  - **Emergency Stop**: Stop the inflator immediately (`RC3`).

### Control System
- **State machine** for managing operational states.
- Automatic adjustment of compressor power based on:
  - Desired pressure.
  - Initial pressure.
  - Ambient temperature.

### Sensors and Monitoring
- **Temperature Sensor (NTC)**: Monitors ambient temperature (`AN6`).
- **Pressure Sensor**: Simulated with a potentiometer to measure tyre pressure (1kΩ between 0V and 5V).
- **Detection of tyre punctures**:
  - Alerts if pressure decreases unexpectedly during inflation.

### Compressor Control
- **PWM output** to regulate compressor power (`RE0`).
- Power levels based on pressure:
  - ≤30 PSI: 40%.
  - ≤60 PSI: 80%.
  - ≤90 PSI: 95%.

### Status Indication
- **Digital outputs for LED indicators**:
  - Selection State: `RA0`.
  - Inflation in Progress: `RA1`.
  - Process Completed: `RA2`.

### Visual Feedback
- **Progress bar** indicating remaining time for inflation.
- **Animations** for:
  - Inflation process.
  - Button interactions.
  - Process completion.
  - Alerts for puncture detection.

### Serial Communication
- **USART communication** for debugging and future extensions:
  - Transmit (`Tx1`): `RC6`.
  - Receive (`Rx1`): `RC7`.
