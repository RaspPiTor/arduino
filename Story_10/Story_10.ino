//m1 left
//m2 right
#include <NewPing.h>

#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


int const leftEnable = 9;
int const leftForward = 8;
int const leftBackward = 7;
int const rightEnable = 10;
int const rightForward = 12;
int const rightBackward = 11;
int const leftMotorCountPin = 2;
int const rightMotorCountPin = 3;
volatile int leftMotorCount = 0;
volatile int rightMotorCount = 0;
const int power = 171;
const int x = 67;
const int turn90 = 86.25;
const int forwardRightTurn90 = 76.5;

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
  pinMode(rightBackward, OUTPUT);
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
    analogWrite(rightBackward, power);
    analogWrite(leftBackward, 0);
  }
  else if (rightMotorCount > leftMotorCount) {
    analogWrite(rightBackward, 0);
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
    analogWrite(rightBackward, 0);
  }
  else if (leftMotorCount > rightMotorCount) {
    analogWrite(leftForward, 0);
    analogWrite(rightBackward, power);
  }
  else {
    turnRight();
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
    turnLeft();
  }
}

void resetCounters() {
  leftMotorCount = 0;
  rightMotorCount = 0;
}

void loop()
{
  int distance = 100;
  while (distance > 10 or distance == 0) {
    forward();
    delay(25);
    hardStop();
    delay(25);
    distance = sonar.ping_cm();
    Serial.println(distance);
  }
  hardStop();
  delay(500);
  resetCounters();
  while (leftMotorCount < turn90 or rightMotorCount < turn90) {
    balanceLeft();
  }
  hardStop();
  while (true) {}

}

void hardStop() {
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
  analogWrite(leftForward, 0);
  analogWrite(rightForward, 0);
  analogWrite(leftBackward, 0);
  analogWrite(rightBackward, 0);
}

void forward() {
  analogWrite(rightForward, power);
  analogWrite(leftForward, power);
  analogWrite(rightBackward, 0);
  analogWrite(leftBackward, 0);
}
void turnRight() {
  analogWrite(rightForward, 0);
  analogWrite(leftForward, power);
  analogWrite(rightBackward, power);
  analogWrite(leftBackward, 0);
}
void turnLeft() {
  analogWrite(leftForward, 0);
  analogWrite(rightForward, power);
  analogWrite(leftBackward, power);
  analogWrite(rightBackward, 0);
}
void backward() {
  analogWrite(leftForward, 0);
  analogWrite(rightForward, 0);
  analogWrite(leftBackward, power);
  analogWrite(rightBackward, power);
}

