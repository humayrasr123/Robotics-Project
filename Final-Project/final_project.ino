#include <Servo.h>

Servo clawServo;

// Servo pin
const int servoPin = 9;

// Ultrasonic sensor pins
const int trigPin = 10;
const int echoPin = 11;

// LED pin
const int ledPin = 6;

// Claw positions
int openAngle = 60;
int closeAngle = 115;

// Distance limit in cm
int detectDistance = 15;

void setup() {
  clawServo.attach(servoPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  // Start with claw closed
  clawServo.write(closeAngle);
  digitalWrite(ledPin, LOW);
}

void loop() {
  float distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If hand/object is detected close to sensor
  if (distance > 0 && distance <= detectDistance) {
    digitalWrite(ledPin, HIGH);   // LED turns on
    clawServo.write(openAngle);   // claw opens
  } 
  else {
    digitalWrite(ledPin, LOW);    // LED turns off
    clawServo.write(closeAngle);  // claw closes
  }

  delay(200);
}

float getDistance() {
  long duration;
  float distanceCm;

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo
  duration = pulseIn(echoPin, HIGH, 30000);

  // If no reading, return -1
  if (duration == 0) {
    return -1;r
  }

  // Convert time to distance
  distanceCm = duration * 0.0343 / 2;

  return distanceCm;
}