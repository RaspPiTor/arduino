//m1 left
//m2 right
#include <NewPing.h>

#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     17  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


int const leftEnable = 9;
int const leftForward = 8;
int const leftBackward = 7;
int const rightEnable = 10;
int const rightForward = 12;
int const leftBackward = 11;
int const leftMotorCountPin = 2;
int const rightMotorCountPin = 3;
volatile int leftMotorCount = 0;
volatile int rightMotorCount = 0;
const int power = 171;
const int x = 67;
const int turn90 = 86.25;
const int forwardrightturn90 = 76.5;

void setup()
{
  Serial.begin(115200);
  pinMode(leftMotorCountPin, INPUT);
  pinMode(rightMotorCountPin, INPUT);
  attachInterrupt(0, leftMotorCountChange, RISING);
  attachInterrupt(1, rightMotorCountChange, RISING);
  pinMode(leftEnable, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
}

void leftMotorCountChange() {
  leftMotorCount++;
}

void rightMotorCountChange() {
  rightMotorCount++;
}

void balanceBackward() {
  if (leftMotorCount > rightMotorCount) {
    analogWrite(leftBackward, power);
    analogWrite(leftBackward, 0);
  }
  else if (rightMotorCount > leftMotorCount) {
    analogWrite(leftBackward, 0);
    analogWrite(leftBackward, power);
  }
  else {
    backward();
  }
}

void balanceForward() {
  if (leftMotorCount > rightMotorCount) {
    analogWrite(rightForward, power);
    analogWrite(leftForward, 0);
  }
  else if (rightMotorCount > leftMotorCount) {
    analogWrite(rightForward, 0);
    analogWrite(leftForward, power);
  }
  else {
    forward();
  }
}

void balanceRight() {
  if (rightMotorCount > leftMotorCount) {
    analogWrite(leftForward, power);
    analogWrite(leftBackward, 0);
  }
  else if (leftMotorCount > rightMotorCount) {
    analogWrite(leftForward, 0);
    analogWrite(leftBackward, power);
  }
  else {
    turnright();
  }
}

void balanceLeft() {
  if (rightMotorCount > leftMotorCount) {
    analogWrite(leftBackward, power);
    analogWrite(rightForward, 0);
  }
  else if (leftMotorCount > rightMotorCount) {
    analogWrite(leftBackward, 0);
    analogWrite(rightForward, power);
  }
  else {
    turnleft();
  }
}

void resetCounters() {
  leftMotorCount = 0;
  rightMotorCount = 0;
}

void loop()
{
  int distance = 0;
  while (distance < 18 or distance == 0) {
    forward();
    delay(25);
    hardstop();
    delay(25);
    distance = sonar.ping_cm();
    Serial.println(distance);
  }
  hardstop();
  delay(500);
  resetCounters();
  while (leftMotorCount < x or rightMotorCount < x) {
    balanceBackward();
  }
  hardstop();
  while (true) {}

}

void hardstop() {
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
  analogWrite(leftForward, 0);
  analogWrite(rightForward, 0);
  analogWrite(leftBackward, 0);
  analogWrite(leftBackward, 0);
}

void forward() {
  analogWrite(rightForward, power);
  analogWrite(leftForward, power);
  analogWrite(leftBackward, 0);
  analogWrite(leftBackward, 0);
}
void turnright() {
  analogWrite(rightForward, 0);
  analogWrite(leftForward, power);
  analogWrite(leftBackward, power);
  analogWrite(leftBackward, 0);
}
void turnleft() {
  analogWrite(leftForward, 0);
  analogWrite(rightForward, power);
  analogWrite(leftBackward, power);
  analogWrite(leftBackward, 0);
}
void backward() {
  analogWrite(leftForward, 0);
  analogWrite(rightForward, 0);
  analogWrite(leftBackward, power);
  analogWrite(leftBackward, power);
}

