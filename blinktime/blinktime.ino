const int led1 = 13;  // 13
const int led2 = 12;  // 12
const int led3 = 11;  //  11

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  blinktime(1000); // 1 second delay, 10 times
  blinktime(500);  // 0.5 second delay, 10 times
  blinktime(250);  // 0.25 second delay, 10 times
}

void blinktime(int delayTime) {
  for (int count = 1; count <= 10; count++) {
    digitalWrite(led1, HIGH);
    delay(delayTime);
    digitalWrite(led1, LOW);
    delay(delayTime);

    digitalWrite(led2, HIGH);
    delay(delayTime);
    digitalWrite(led2, LOW);
    delay(delayTime);

    digitalWrite(led3, HIGH);
    delay(delayTime);
    digitalWrite(led3, LOW);
    delay(delayTime);
  }
}
