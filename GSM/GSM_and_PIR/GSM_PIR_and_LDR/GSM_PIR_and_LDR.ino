#include <SoftwareSerial.h>

// Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); // SIM800L Tx & Rx is connected to Arduino #3 & #2

// Define pin constants
const int ledPin = 13;         // LED for motion detection
const int inputPin = 8;        // PIR sensor
const int ldrLedPin = 12;      // LED for LDR
const int ldrPin = A0;         // LDR sensor

// Initialize variables
int pirState = LOW;            // Start assuming no motion detected
int val = 0;                   // Variable for reading PIR sensor status
int ldrStatus = 0;             // Variable for reading LDR sensor status

void setup() {
  // Initialize pins
  pinMode(ledPin, OUTPUT);     // Declare motion detection LED as output
  pinMode(inputPin, INPUT);    // Declare PIR sensor as input
  pinMode(ldrLedPin, OUTPUT);  // Declare LDR LED as output
  pinMode(ldrPin, INPUT);      // Declare LDR sensor as input

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
}

void loop() {
  // Motion detection
  val = digitalRead(inputPin);  // Read input value from PIR sensor

  if (val == HIGH) {            // Check if the input is HIGH
    digitalWrite(ledPin, HIGH); // Turn motion detection LED ON

    if (pirState == LOW) {
      Serial.println("⚠️ Intruder Alert ⚠️ | ensubga019@gmail.com!"); // Print on output change
      pirState = HIGH;
      sendSMS("+256741539324", "⚠️ Intruder Alert ⚠️ | ensubga019@gmail.com!"); // Send SMS on motion detected
    }
  } else {
    digitalWrite(ledPin, LOW);  // Turn motion detection LED OFF

    if (pirState == HIGH) {
      Serial.println("Motion ended!");  // Print on output change
      pirState = LOW;
      sendSMS("+256741539324", "Motion ended!"); // Send SMS on motion ended
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

  updateSerial(); // Update serial communication
}

void sendSMS(const char* number, const char* message) {
  mySerial.println("AT+CMGS=\"" + String(number) + "\""); // Send SMS to the specified number
  updateSerial();
  mySerial.print(message); // SMS content
  updateSerial();
  mySerial.write(26); // ASCII code for Ctrl+Z to send the message
  updateSerial();
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port
  }
}
