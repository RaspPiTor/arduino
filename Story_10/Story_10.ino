//m1 left
//m2 right
#include <NewPing.h>

#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


int const m1enable = 9;
int const m1forward = 8;
int const m1backward = 7;
int const m2enable = 10;
int const m2forward = 12;
int const m2backward = 11;
int const m1pin = 2;
int const m2pin = 3;
volatile int m1counter = 0;
volatile int m2counter = 0;
const int power = 171;
const int x = 67;
const int turn90 = 86.25;
const int forwardrightturn90 = 76.5;

void setup()
{
  Serial.begin(115200);
  pinMode(m1pin, INPUT);
  pinMode(m2pin, INPUT);
  attachInterrupt(0, m1change, RISING);
  attachInterrupt(1, m2change, RISING);
  pinMode(m1enable, OUTPUT);
  pinMode(m1forward, OUTPUT);
  pinMode(m1backward, OUTPUT);
  pinMode(m2enable, OUTPUT);
  pinMode(m2forward, OUTPUT);
  pinMode(m2backward, OUTPUT);
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
}

void m1change() {
  m1counter++;
}

void m2change() {
  m2counter++;
}

void balancebackward() {
  if (m1counter > m2counter) {
    analogWrite(m2backward, power);
    analogWrite(m1backward, 0);
  }
  else if (m2counter > m1counter) {
    analogWrite(m2backward, 0);
    analogWrite(m1backward, power);
  }
  else {
    backward();
  }
}

void balanceforward() {
  if (m1counter > m2counter) {
    analogWrite(m2forward, power);
    analogWrite(m1forward, 0);
  }
  else if (m2counter > m1counter) {
    analogWrite(m2forward, 0);
    analogWrite(m1forward, power);
  }
  else {
    forward();
  }
}

void balanceright() {
  if (m2counter > m1counter) {
    analogWrite(m1forward, power);
    analogWrite(m2backward, 0);
  }
  else if (m1counter > m2counter) {
    analogWrite(m1forward, 0);
    analogWrite(m2backward, power);
  }
  else {
    turnright();
  }
}

void balanceleft() {
  if (m2counter > m1counter) {
    analogWrite(m1backward, power);
    analogWrite(m2forward, 0);
  }
  else if (m1counter > m2counter) {
    analogWrite(m1backward, 0);
    analogWrite(m2forward, power);
  }
  else {
    turnleft();
  }
}

void resetcounters() {
  m1counter = 0;
  m2counter = 0;
}

void loop()
{
  int distance = 100;
  while (distance > 10 or distance == 0) {
    forward();
    delay(25);
    hardstop();
    delay(25);
    distance = sonar.ping_cm();
    Serial.println(distance);
  }
  hardstop();
  delay(500);
  resetcounters();
  while (m1counter < turn90 or m2counter < turn90) {
    balanceleft();
  }
  hardstop();
  while (true) {}
  
}

void hardstop() {
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
  analogWrite(m1forward, 0);
  analogWrite(m2forward, 0);
  analogWrite(m1backward, 0);
  analogWrite(m2backward, 0);
}

void forward() {
  analogWrite(m2forward, power);
  analogWrite(m1forward, power);
  analogWrite(m2backward, 0);
  analogWrite(m1backward, 0);
}
void turnright() {
  analogWrite(m2forward, 0);
  analogWrite(m1forward, power);
  analogWrite(m2backward, power);
  analogWrite(m1backward, 0);
}
void turnleft() {
  analogWrite(m1forward, 0);
  analogWrite(m2forward, power);
  analogWrite(m1backward, power);
  analogWrite(m2backward, 0);
}
void backward() {
  analogWrite(m1forward, 0);
  analogWrite(m2forward, 0);
  analogWrite(m1backward, power);
  analogWrite(m2backward, power);
}

