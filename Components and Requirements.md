# Smart Home Security System

This project is a comprehensive smart home security system using Arduino, featuring multiple sensors and components to detect intruders and alert the homeowner via SMS. The system integrates a PIR motion sensor, LDR light sensor, multiple ultrasonic sensors, a servo motor, a push button, a buzzer, and an LCD display for real-time notifications.

## Components Used

- Arduino Uno
- SIM800L GSM Module
- PIR Motion Sensor
- LDR Sensor
- Ultrasonic Sensors (3 units)
- Servo Motor
- Push Button
- Buzzer
- LiquidCrystal I2C Display
- LEDs
- Resistors
- Breadboard and Jumper Wires

## Circuit Diagram

Provide a circuit diagram here or a link to an image of the circuit diagram.

## Setup

1. **Hardware Setup:**
   - Connect the components to the Arduino as per the pin configuration defined in the code.
   - Ensure the SIM800L GSM module is properly powered and has a SIM card installed.

2. **Software Setup:**
   - Install the required libraries:
     - `SoftwareSerial`
     - `Servo`
     - `LiquidCrystal_I2C`
   - Upload the provided code to the Arduino using the Arduino IDE.

## Functionality

The system provides the following functionalities:
- **PIR Motion Sensor:** Detects motion and triggers an SMS alert and updates the LCD display with the message "Intruder in the garden."
- **LDR Sensor:** Detects light changes and turns an LED on/off accordingly.
- **Ultrasonic Sensors:** Measures distances and triggers an SMS alert and buzzer if an intruder is detected within the safety distance for the locations: Backdoor, Compound, and Maindoor.
- **Push Button:** Controls the servo motor to simulate opening/closing a door.
- **LCD Display:** Displays real-time notifications about the system status and intruder alerts.

## Usage

1. Power the Arduino and all connected components.
2. The system will initialize, and you should receive an SMS indicating that monitoring has started.
3. The LCD will display a welcome message for 5 seconds.
4. The system continuously monitors for motion, light changes, and proximity:
   - **PIR Sensor:** Detects motion and triggers an SMS alert and updates the LCD display.
   - **LDR Sensor:** Detects light changes and turns an LED on/off accordingly.
   - **Ultrasonic Sensors:** Measures distances and triggers an SMS alert and buzzer if an intruder is detected within the safety distance.
5. The push button controls the servo motor to simulate opening/closing a door.

## Authors

- [Emmanuel Nsubuga](https://github.com/Cemputus)
- [Emmanuel Kisa](https://github.com/yourusername)
- [Nicole Johnson](https://github.com/emmje)
- Group D Members

## Acknowledgments

- Special thanks to the contributors and the open-source community for their valuable resources and support
