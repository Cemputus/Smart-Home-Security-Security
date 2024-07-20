#include <SoftwareSerial.h>

// Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); // SIM800L Tx & Rx is connected to Arduino #3 & #2

int ledPin = 13;                // choose the pin for the LED
int inputPin = 8;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

void setup() {
  // Initialize pins
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input

  // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  // Begin serial communicat
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
  val = digitalRead(inputPin);  // read input value

  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH); // turn LED ON

    if (pirState == LOW) {
      Serial.println("Motion detected!"); // print on output change
      pirState = HIGH;
      sendSMS("+256741539324", "Motion detected!"); // send SMS on motion detected
    }
  } else {
    digitalWrite(ledPin, LOW);  // turn LED OFF

    if (pirState == HIGH) {
      Serial.println("Motion ended!");  // print on output change
      pirState = LOW;
      sendSMS("+256741539324", "Motion ended!"); // send SMS on motion ended
    }
  }

  updateSerial();
}

void sendSMS(const char* number, const char* message) {
  mySerial.println("AT+CMGS=\"" + String(number) + "\""); // send SMS to the specified number
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
