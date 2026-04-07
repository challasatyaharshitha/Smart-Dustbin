#include <Servo.h>

Servo myServo;

const int trigPin = 5;
const int echoPin = 6;
const int buttonPin = 7;

long duration;
int distance;

bool lidOpen = false;
bool lastButtonState = LOW;

//  Function to get stable distance (average of 3 readings)
int getDistance() {
  int sum = 0;
  for (int i = 0; i < 3; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long dur = pulseIn(echoPin, HIGH);
    int dist = dur * 0.034 / 2;

    sum += dist;
    delay(10);
  }

  int avgDistance = sum / 3;

  // Limit abnormal values
  avgDistance = constrain(avgDistance, 0, 100);

  return avgDistance;
}

void setup() {
  myServo.attach(9);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);

  myServo.write(0); // Lid closed initially
  Serial.begin(9600);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // Manual Override (Toggle Control)
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    lidOpen = !lidOpen;

    if (lidOpen) {
      myServo.write(90); // Open lid
      Serial.println("Manual Override: Lid Opened");
    } else {
      myServo.write(0);  // Close lid
      Serial.println("Manual Override: Lid Closed");
    }
    delay(300); // Debounce
  }

  lastButtonState = currentButtonState;

  // Automatic Mode (only when manual override is OFF)
  if (!lidOpen) {
    distance = getDistance();

    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance <= 30 && distance > 0) {
      myServo.write(90);
      Serial.println("Auto: Lid Opened");

      delay(3000);

      myServo.write(0);
      Serial.println("Auto: Lid Closed");
    }
  }

  delay(100);
}
