//#include <SoftwareSerial.h>
//#include <Servo.h>
//#include <LiquidCrystal_I2C.h>
//
//// Create software serial object to communicate with SIM800L
//SoftwareSerial mySerial(3, 2); // SIM800L Tx & Rx is connected to Arduino #3 & #2
//
//// Define pin constants
//const int motionLedPin = 13;   // LED for motion detection
//const int inputPin = A3;        // PIR sensor
//const int ldrLedPin = A1;      // LED for LDR
//const int ldrPin = A0;         // LDR sensor
//const int buttonPin = 5;       // Pushbutton pin
//const int servoPin = 4;        // Servo pin
//const int buzzer = 11;         // Buzzer pin
//const int trigPin1 = 12;       // Ultrasonic sensor 1 trig pin
//const int echoPin1 = 10;       // Ultrasonic sensor 1 echo pin
//const int trigPin2 = 6;        // Ultrasonic sensor 2 trig pin
//const int echoPin2 = 7;        // Ultrasonic sensor 2 echo pin
//const int trigPin3 = 9;        // Ultrasonic sensor 3 trig pin
//const int echoPin3 = 8;        // Ultrasonic sensor 3 echo pin
//
//// Initialize variables
//int pirState = LOW;            // Start assuming no motion detected
//int val = 0;                   // Variable for reading PIR sensor status
//int ldrStatus = 0;             // Variable for reading LDR sensor status
//int counter = 0;               // Counter for button presses
//long duration1, duration2, duration3;
//int distance1, distance2, distance3;
//const int safetyDistance = 5;  // Safety distance in cm
//
//Servo servo;                   // Create Servo object
//LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display
//
//void setup() {
//  // Initialize pins
//  pinMode(motionLedPin, OUTPUT);  // Declare motion detection LED as output
//  pinMode(inputPin, INPUT);       // Declare PIR sensor as input
//  pinMode(ldrLedPin, OUTPUT);     // Declare LDR LED as output
//  pinMode(ldrPin, INPUT);         // Declare LDR sensor as input
//  pinMode(buttonPin, INPUT);      // Declare button as input
//  pinMode(buzzer, OUTPUT);        // Declare buzzer as output
//  pinMode(trigPin1, OUTPUT);      // Declare ultrasonic sensor 1 trig pin as output
//  pinMode(echoPin1, INPUT);       // Declare ultrasonic sensor 1 echo pin as input
//  pinMode(trigPin2, OUTPUT);      // Declare ultrasonic sensor 2 trig pin as output
//  pinMode(echoPin2, INPUT);       // Declare ultrasonic sensor 2 echo pin as input
//  pinMode(trigPin3, OUTPUT);      // Declare ultrasonic sensor 3 trig pin as output
//  pinMode(echoPin3, INPUT);       // Declare ultrasonic sensor 3 echo pin as input
//
//  // Attach the servo
//  servo.attach(servoPin);
//
//  // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
//  Serial.begin(9600);
//
//  // Begin serial communication with Arduino and SIM800L
//  mySerial.begin(9600);
//
//  Serial.println("Initializing...");
//  delay(1000);
//
//  // Handshake with SIM800L
//  mySerial.println("AT"); // Once the handshake test is successful, it will return OK
//  updateSerial();
//  
//  // Configure SIM800L in TEXT mode
//  mySerial.println("AT+CMGF=1");
//  updateSerial();
//  
//  // Configure how newly arrived SMS messages should be handled
//  mySerial.println("AT+CNMI=1,2,0,0,0");
//  updateSerial();
//  
//  // Send an initial SMS
//  sendSMS("+256741539324", "System initialized. Monitoring started.");
//
//  // Initialize the LCD
//  lcd.init();
//  lcd.clear();
//  lcd.backlight(); // Make sure backlight is on
//  
//  // Print a welcome message on the LCD
//  lcd.setCursor(2, 0); // Set cursor to character 2 on line 0
//  lcd.print("WELCOME TO!");
//  lcd.setCursor(2, 1); // Move cursor to character 2 on line 1
//  lcd.print("GROUP D");
//  delay(5000); // Display the welcome message for 5 seconds
//  lcd.clear(); // Clear the screen
//}
//
//void loop() {
//  // Motion detection
//  val = digitalRead(inputPin);  // Read input value from PIR sensor
//
//  if (val == HIGH) {            // Check if the input is HIGH
//    digitalWrite(motionLedPin, HIGH); // Turn motion detection LED ON
//
//    if (pirState == LOW) {
//      Serial.println("⚠️ Intruder Alert ⚠️ | ensubga019@gmail.com!"); // Print on output change
//      pirState = HIGH;
//      sendSMS("+256741539324", "⚠️ Intruder Alert ⚠️ | ensubga019@gmail.com!"); // Send SMS on motion detected
//    }
//  } else {
//    digitalWrite(motionLedPin, LOW);  // Turn motion detection LED OFF
//
//    if (pirState == HIGH) {
//      Serial.println("Motion ended!");  // Print on output change
//      pirState = LOW;
//      sendSMS("+256741539324", "Motion ended!"); // Send SMS on motion ended
//    }
//  }
//
//  // LDR sensor detection
//  ldrStatus = analogRead(ldrPin); // Read LDR sensor value
//
//  if (ldrStatus <= 300) { // Check if LDR sensor detects darkness
//    digitalWrite(ldrLedPin, HIGH); // Turn LDR LED ON
//    Serial.println("LDR is DARK, LED is ON");
//  } else {
//    digitalWrite(ldrLedPin, LOW); // Turn LDR LED OFF
//    Serial.println("---------------");
//  }
//
//  // Ultrasonic sensor distance measurement
//  distance1 = measureDistance(trigPin1, echoPin1); // Measure distance for sensor 1 (Backdoor)
//  distance2 = measureDistance(trigPin2, echoPin2); // Measure distance for sensor 2 (Compound)
//  distance3 = measureDistance(trigPin3, echoPin3); // Measure distance for sensor 3 (Maindoor)
//
//  // Check distances and take appropriate action
//  if (distance1 <= safetyDistance) {
//    displayAlert("Backdoor");
//    sendSMS("+256741539324", "Intruder detected at Backdoor!");
//  } else if (distance2 <= safetyDistance) {
//    displayAlert("Compound");
//    sendSMS("+256741539324", "Intruder detected in Compound!");
//  } else if (distance3 <= safetyDistance) {
//    displayAlert("Maindoor");
//    sendSMS("+256741539324", "Intruder detected at Maindoor!");
//  } else {
//    clearAlert();
//  }
//
//  // Print distances on the Serial Monitor
//  Serial.print("Distance1: ");
//  Serial.print(distance1);
//  Serial.print(" cm, Distance2: ");
//  Serial.print(distance2);
//  Serial.print(" cm, Distance3: ");
//  Serial.println(distance3);
//  delay(100);
//
//  updateSerial(); // Update serial communication
//
//  // Servo control with pushbutton (separate logic)
//  int buttonState = digitalRead(buttonPin); // Read button state
//
//  if (buttonState == LOW) { // Button pressed
//    counter++;
//    delay(150); // Debounce delay
//  }
//
//  // Control servo based on button presses
//  if (counter == 1) {
//    servo.write(90);  // Open door (90 degrees)
//    delay(5000);      // Keep the door open for 5 seconds
//    servo.write(0);   // Close door (0 degrees)
//    counter = 0;      // Reset counter
//  }
//}
//
//// Function to measure distance
//int measureDistance(int trigPin, int echoPin) {
//  long duration;
//  int distance;
//
//  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//
//  // Sets the trigPin on HIGH state for 10 microseconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  duration = pulseIn(echoPin, HIGH);
//
//  // Calculating the distance
//  distance = duration * 0.034 / 2;
//
//  return distance;
//}
//
//// Function to display alert
//void displayAlert(String location) {
//  tone(buzzer, 1000);  // Produce a 1kHz tone on the passive buzzer
//  digitalWrite(motionLedPin, HIGH);
//  lcd.clear();
//  lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
//  lcd.print(location + " Intruder");
//  lcd.setCursor(0, 1); // Set cursor to character 0 on line 1
//  lcd.print("Alert!");
//}
//
//// Function to clear alert
//void clearAlert() {
//  noTone(buzzer);  // Stop the tone
//  digitalWrite(motionLedPin, LOW);
//  lcd.clear();
//  lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
//  lcd.print("No Intruders");
//}
//
//// Function to send SMS
//void sendSMS(const char* number, const char* message) {
//  mySerial.println("AT+CMGS=\"" + String(number) + "\""); // Send SMS to the specified number
//  updateSerial();
//  mySerial.print(message); // SMS content
//  updateSerial();
//  mySerial.write(26); // ASCII code for Ctrl+Z to send the message
//  updateSerial();
//}
//
//// Function to update serial communication
//void updateSerial() {
//  delay(500);
//  while (Serial.available()) {
//    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
//  }
//  while (mySerial.available()) {
//    Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port
//  }
//}


#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); // SIM800L Tx & Rx is connected to Arduino #3 & #2

// Define pin constants
const int motionLedPin = 13;   // LED for motion detection
const int inputPin = A3;       // PIR sensor
const int ldrLedPin = A1;      // LED for LDR
const int ldrPin = A0;         // LDR sensor
const int buttonPin = 5;       // Pushbutton pin
const int servoPin = 4;        // Servo pin
const int buzzer = 11;         // Buzzer pin
const int trigPin1 = 12;       // Ultrasonic sensor 1 trig pin
const int echoPin1 = 10;       // Ultrasonic sensor 1 echo pin
const int trigPin2 = 6;        // Ultrasonic sensor 2 trig pin
const int echoPin2 = 7;        // Ultrasonic sensor 2 echo pin
const int trigPin3 = 9;        // Ultrasonic sensor 3 trig pin
const int echoPin3 = 8;        // Ultrasonic sensor 3 echo pin

// Initialize variables
int pirState = LOW;            // Start assuming no motion detected
int val = 0;                   // Variable for reading PIR sensor status
int ldrStatus = 0;             // Variable for reading LDR sensor status
int counter = 0;               // Counter for button presses
long duration1, duration2, duration3;
int distance1, distance2, distance3;
const int safetyDistance = 5;  // Safety distance in cm

Servo servo;                   // Create Servo object
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  // Initialize pins
  pinMode(motionLedPin, OUTPUT);  // Declare motion detection LED as output
  pinMode(inputPin, INPUT);       // Declare PIR sensor as input
  pinMode(ldrLedPin, OUTPUT);     // Declare LDR LED as output
  pinMode(ldrPin, INPUT);         // Declare LDR sensor as input
  pinMode(buttonPin, INPUT);      // Declare button as input
  pinMode(buzzer, OUTPUT);        // Declare buzzer as output
  pinMode(trigPin1, OUTPUT);      // Declare ultrasonic sensor 1 trig pin as output
  pinMode(echoPin1, INPUT);       // Declare ultrasonic sensor 1 echo pin as input
  pinMode(trigPin2, OUTPUT);      // Declare ultrasonic sensor 2 trig pin as output
  pinMode(echoPin2, INPUT);       // Declare ultrasonic sensor 2 echo pin as input
  pinMode(trigPin3, OUTPUT);      // Declare ultrasonic sensor 3 trig pin as output
  pinMode(echoPin3, INPUT);       // Declare ultrasonic sensor 3 echo pin as input

  // Attach the servo
  servo.attach(servoPin);

  // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  // Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  // Handshake with SIM800L
  mySerial.println("AT"); // Once the handshake test is successful, it will return OK
  updateSerial();
  
  // Configure SIM800L in TEXT mode
  mySerial.println("AT+CMGF=1");
  updateSerial();
  
  // Configure how newly arrived SMS messages should be handled
  mySerial.println("AT+CNMI=1,2,0,0,0");
  updateSerial();
  
  // Send an initial SMS
  sendSMS("+256741539324", "System initialized. Monitoring started.");

  // Initialize the LCD
  lcd.init();
  lcd.clear();
  lcd.backlight(); // Make sure backlight is on
  
  // Print a welcome message on the LCD
  lcd.setCursor(2, 0); // Set cursor to character 2 on line 0
  lcd.print("WELCOME TO!");
  lcd.setCursor(2, 1); // Move cursor to character 2 on line 1
  lcd.print("GROUP D");
  delay(5000); // Display the welcome message for 5 seconds
  lcd.clear(); // Clear the screen
}

void loop() {
  // Motion detection
  val = digitalRead(inputPin);  // Read input value from PIR sensor

  if (val == HIGH) {            // Check if the input is HIGH
    digitalWrite(motionLedPin, HIGH); // Turn motion detection LED ON
    lcd.clear(); // Clear the screen
    lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
    lcd.print("Intruder in");
    lcd.setCursor(0, 1); // Set cursor to character 0 on line 1
    lcd.print("the garden");

    if (pirState == LOW) {
      Serial.println("⚠️ Intruder Alert ⚠️ | ensubga019@gmail.com!"); // Print on output change
      pirState = HIGH;
      sendSMS("+256741539324", "⚠️ Intruder Alert ⚠️ | ensubga019@gmail.com!"); // Send SMS on motion detected
    }
  } else {
    digitalWrite(motionLedPin, LOW);  // Turn motion detection LED OFF

    if (pirState == HIGH) {
      Serial.println("Motion ended!");  // Print on output change
      pirState = LOW;
      sendSMS("+256741539324", "Motion ended!"); // Send SMS on motion ended
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
      lcd.print("No Intruders");
    }
  }

  // LDR sensor detection
  ldrStatus = analogRead(ldrPin); // Read LDR sensor value

  if (ldrStatus <= 300) { // Check if LDR sensor detects darkness
    digitalWrite(ldrLedPin, HIGH); // Turn LDR LED ON
    Serial.println("LDR is DARK, LED is ON");
  } else {
    digitalWrite(ldrLedPin, LOW); // Turn LDR LED OFF
    Serial.println("---------------");
  }

  // Ultrasonic sensor distance measurement
  distance1 = measureDistance(trigPin1, echoPin1); // Measure distance for sensor 1 (Backdoor)
  distance2 = measureDistance(trigPin2, echoPin2); // Measure distance for sensor 2 (Compound)
  distance3 = measureDistance(trigPin3, echoPin3); // Measure distance for sensor 3 (Maindoor)

  // Check distances and take appropriate action
  if (distance1 <= safetyDistance) {
    displayAlert("Backdoor");
    sendSMS("+256741539324", "Intruder detected at Backdoor!");
  } else if (distance2 <= safetyDistance) {
    displayAlert("Compound");
    sendSMS("+256741539324", "Intruder detected in Compound!");
  } else if (distance3 <= safetyDistance) {
    displayAlert("Maindoor");
    sendSMS("+256741539324", "Intruder detected at Maindoor!");
  } else {
    clearAlert();
  }

  // Print distances on the Serial Monitor
  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distance2: ");
  Serial.print(distance2);
  Serial.print(" cm, Distance3: ");
  Serial.println(distance3);
  delay(100);

  updateSerial(); // Update serial communication

  // Servo control with pushbutton (separate logic)
  int buttonState = digitalRead(buttonPin); // Read button state

  if (buttonState == LOW) { // Button pressed
    counter++;
    delay(150); // Debounce delay
  }

  // Control servo based on button presses
  if (counter == 1) {
    servo.write(90);  // Open door (90 degrees)
    delay(5000);      // Keep the door open for 5 seconds
    servo.write(0);   // Close door (0 degrees)
    counter = 0;      // Reset counter
  }
}

// Function to measure distance
int measureDistance(int trigPin, int echoPin) {
  long duration;
  int distance;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  return distance;
}

// Function to display alert
void displayAlert(String location) {
  tone(buzzer, 1000);  // Produce a 1kHz tone on the passive buzzer
  digitalWrite(motionLedPin, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
  lcd.print(location + " Intruder");
  lcd.setCursor(0, 1); // Set cursor to character 0 on line 1
  lcd.print("Alert!");
}

// Function to clear alert
void clearAlert() {
  noTone(buzzer);  // Stop the tone
  digitalWrite(motionLedPin, LOW);
  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
  lcd.print("No Intruders");
}

// Function to send SMS
void sendSMS(const char* number, const char* message) {
  mySerial.println("AT+CMGS=\"" + String(number) + "\""); // Send SMS to the specified number
  updateSerial();
  mySerial.print(message); // SMS content
  updateSerial();
  mySerial.write(26); // ASCII code for Ctrl+Z to send the message
  updateSerial();
}

// Function to update serial communication
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port
  }
}
