const int led1 = 9;  //  pin 13
const int led2 = 10;  //  pin 10
const int led3 = A1;  //  pin A1

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  blinksDuration(1000); // 1 second delay
  blinksDuration(500);  // 0.5 second delay
  blinksDuration(250);  // 0.25 second delay
}

void blinksDuration(int delayTime) {
  int blinkCount = 0;
  
  while (blinkCount < 10) {
    if (blinkCount < 10) {
      digitalWrite(led1, HIGH);
      delay(delayTime);
      digitalWrite(led1, LOW);
      delay(delayTime);
      blinkCount++;
    }
    
    if (blinkCount < 10) {
      digitalWrite(led2, HIGH);
      delay(delayTime);
      digitalWrite(led2, LOW);
      delay(delayTime);
      blinkCount++;
    }
    
    if (blinkCount < 10) {
      digitalWrite(led3, HIGH);
      delay(delayTime);
      digitalWrite(led3, LOW);
      delay(delayTime);
      blinkCount++;
    }
  }
}
