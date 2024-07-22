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
//void setup() {
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//  pinMode(buzzer, OUTPUT);
//  pinMode(ledPin, OUTPUT);
//  Serial.begin(9600); // Starts the serial communication
//}
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
//  } else {
//    noTone(buzzer);  // Stop the tone
//    digitalWrite(ledPin, LOW);
//  }
//
//  // Prints the distance on the Serial Monitor
//  Serial.print("Distance: ");
//  Serial.println(distance);
//  delay(100);
//}




// defines pins numbers
const int trigPin = 12;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;

// defines variables
long duration;
int distance;
const int safetyDistance = 5; // Safety distance in cm

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT); // Sets the buzzer as an Output
  pinMode(ledPin, OUTPUT); // Sets the ledPin as an Output
  Serial.begin(9600); // Starts the serial communication
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

  // If the distance is less than the safety distance, activate buzzer and LED
  if (distance <= safetyDistance) {
    tone(buzzer, 1000); // Produce a 1kHz tone on the passive buzzer
    digitalWrite(ledPin, HIGH); // Turn on the LED
  } else {
    noTone(buzzer); // Stop the tone
    digitalWrite(ledPin, LOW); // Turn off the LED
  }

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100); // Delay to stabilize sensor readings
}
