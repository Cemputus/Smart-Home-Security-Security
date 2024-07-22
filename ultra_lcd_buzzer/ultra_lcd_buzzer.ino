//#include <LiquidCrystal_I2C.h>
//
//// defines pins numbers
//const int trigPin = 9;
//const int echoPin = 10;
//const int buzzer = 11;
//const int ledPin = 13;
//
//// defines variables
//long duration;
//int distance;
//int safetyDistance;
//
//LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
//
//void setup() {
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//  pinMode(buzzer, OUTPUT);
//  pinMode(ledPin, OUTPUT);
//  Serial.begin(9600); // Starts the serial communication
//
//  lcd.init();
//  lcd.clear();         
//  lcd.backlight();      // Make sure backlight is on
//  
//  // Print a message on both lines of the LCD.
//  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
//  lcd.print("Hello world!");
//  
//  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
//  lcd.print("GROUP D");
//}
//
//void loop() {
//  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//
//  // Sets the trigPin on HIGH state for 10 micro seconds
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
//  safetyDistance = distance;
//  if (safetyDistance <= 5) {
//    tone(buzzer, 1000);  // Produce a 1kHz tone on the passive buzzer
//    digitalWrite(ledPin, HIGH);
//    lcd.setCursor(0,0);   //Set cursor to character 0 on line 0
//    lcd.print("Intrusion detected");
//  } else {
//    noTone(buzzer);  // Stop the tone
//    digitalWrite(ledPin, LOW);
//    lcd.setCursor(0,0);   //Set cursor to character 0 on line 0
//    lcd.print("                ");  // Clear the line
//  }
//
//  // Prints the distance on the Serial Monitor
//  Serial.print("Distance: ");
//  Serial.println(distance);
//  delay(100);
//}
//
//




#include <LiquidCrystal_I2C.h>

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;

// defines variables
long duration;
int distance;
const int safetyDistance = 5; // Safety distance in cm

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a welcome message on the LCD.
  lcd.setCursor(2, 0);   // Set cursor to character 2 on line 0
  lcd.print("Hello world!");
  
  lcd.setCursor(2, 1);   // Move cursor to character 2 on line 1
  lcd.print("GROUP D");
  delay(6000);           // Display the welcome message for 2 seconds
  lcd.clear();           // Clear the screen
}

void loop() {
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

  // If the distance is less than or equal to the safety distance, activate buzzer and LED, and display message
  if (distance <= safetyDistance) {
    tone(buzzer, 1000);  // Produce a 1kHz tone on the passive buzzer
    digitalWrite(ledPin, HIGH);
    lcd.setCursor(0, 0);   // Set cursor to character 0 on line 0
    lcd.print("Intruder Alert!");
  } else {
    noTone(buzzer);  // Stop the tone
    digitalWrite(ledPin, LOW);
    lcd.setCursor(0, 0);   // Set cursor to character 0 on line 0
    lcd.print("                ");  // Clear the line
  }

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
