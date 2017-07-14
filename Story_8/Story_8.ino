//m1 left
//m2 right
unsigned int const leftEnable = 9;
unsigned int const leftForward = 8;
unsigned int const leftBackward = 7;
unsigned int const rightEnable = 10;
unsigned int const rightForward = 12;
unsigned int const leftBackward = 11;
unsigned int const leftMotorCountPin = 2;
unsigned int const rightMotorCountPin = 3;
volatile unsigned int leftMotorCount = 0;
volatile unsigned int rightMotorCount = 0;
unsigned int const power = 171;
unsigned int const x = 67;
unsigned int const turn90 = 86;
unsigned int const forwardrightturn90 = 76;

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

void totalReset()
{
  resetCounters();
  hardStop();
}

void forwardsFigureOf8() {
  for (int i = 0; i < 3; i++) {
    while (leftMotorCount < x and rightMotorCount < x) {
      balanceForward();
    }
    totalReset();
    while (leftMotorCount < forwardrightturn90 or rightMotorCount < forwardrightturn90) {
      balanceRight();
    }
    totalReset();
  }
  while (leftMotorCount < (2.75 * x) and rightMotorCount < (2.75 * x)) {
    balanceForward();
}
  for (int i = 0; i < 3; i++) {
    totalReset();
    while (leftMotorCount < turn90 or rightMotorCount < turn90) {
      balanceLeft();
    }
    totalReset();
    while (leftMotorCount < x and rightMotorCount < x) {
      balanceForward();
    }
  }
}


void loop()
{
  forwardsFigureOf8();
  totalReset();
  while (true) {}

}

void hardStop() {
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
void turnRight() {
  analogWrite(rightForward, 0);
  analogWrite(leftForward, power);
  analogWrite(leftBackward, power);
  analogWrite(leftBackward, 0);
}
void turnLeft() {
  analogWrite(leftForward, 0);
  analogWrite(rightForward, power);
  analogWrite(leftBackward, power);
  analogWrite(leftBackward, 0);
}

