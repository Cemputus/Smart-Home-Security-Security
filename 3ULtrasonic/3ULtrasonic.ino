#include <LiquidCrystal_I2C.h>

// defines pins numbers
const int trigPin1 = 12;       // Ultrasonic sensor 1 trig pin
const int echoPin1 = 10;       // Ultrasonic sensor 1 echo pin
const int trigPin2 = 6;        // Ultrasonic sensor 2 trig pin
const int echoPin2 = 7;        // Ultrasonic sensor 2 echo pin
const int trigPin3 = 9;        // Ultrasonic sensor 3 trig pin
const int echoPin3 = 8;        // Ultrasonic sensor 3 echo pin

const int buzzer = 11;
const int ledPin = 13;

// defines variables
long duration1, duration2, duration3;
int distance1, distance2, distance3;
const int safetyDistance = 5; // Safety distance in cm

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

  lcd.init();
  lcd.clear();
  lcd.backlight(); // Make sure backlight is on
  
  // Print a welcome message on the LCD.
  lcd.setCursor(2, 0); // Set cursor to character 2 on line 0
  lcd.print("Hello world!");
  
  lcd.setCursor(2, 1); // Move cursor to character 2 on line 1
  lcd.print("GROUP D");
  delay(2000); // Display the welcome message for 2 seconds
  lcd.clear(); // Clear the screen
}

void loop() {
  // Measure distance for sensor 1 (Backdoor)
  distance1 = measureDistance(trigPin1, echoPin1);

  // Measure distance for sensor 2 (Compound)
  distance2 = measureDistance(trigPin2, echoPin2);

  // Measure distance for sensor 3 (Maindoor)
  distance3 = measureDistance(trigPin3, echoPin3);

  // Check distances and take appropriate action
  if (distance1 <= safetyDistance) {
    displayAlert("Backdoor");
  } else if (distance2 <= safetyDistance) {
    displayAlert("Compound");
  } else if (distance3 <= safetyDistance) {
    displayAlert("Maindoor");
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
  digitalWrite(ledPin, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
  lcd.print(location + " Intruder");
  lcd.setCursor(0, 1); // Set cursor to character 0 on line 1
  lcd.print("Alert!");
}

// Function to clear alert
void clearAlert() {
  noTone(buzzer);  // Stop the tone
  digitalWrite(ledPin, LOW);
  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to character 0 on line 0
  lcd.print("No Intruders");
}
