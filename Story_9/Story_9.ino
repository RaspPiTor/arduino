//m1 left
//m2 right
unsigned int const leftEnable = 9;
unsigned int const leftForward = 8;
unsigned int const leftBackward = 7;
unsigned int const rightEnable = 10;
unsigned int const rightForward = 12;
unsigned int const rightBackward = 11;
unsigned int const leftMotorCountPin = 2;
unsigned int const rightMotorCountPin = 3;
volatile unsigned int leftMotorCount = 0;
volatile unsigned int rightMotorCount = 0;
unsigned int const power = 171;
unsigned int const x = 67;
unsigned int const turn90 = 86;
unsigned int const forwardRightTurn90 = 76;

void setup()
{
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

void totalreset() {
  resetCounters();
  hardStop();
}

void forwardsFigureOf8() {
  for (int i = 0; i < 3; i++) {
    while (leftMotorCount < x and rightMotorCount < x) {
      balanceForward();
    }
    totalreset();
    while (leftMotorCount < forwardrightturn90 or rightMotorCount < forwardrightturn90) {
      balanceRight();
    }
    totalreset();
  }
  while (leftMotorCount < (2.75 * x) and rightMotorCount < (2.75 * x)) {
    balanceForward();
}
  for (int i = 0; i < 3; i++) {
    totalreset();
    while (leftMotorCount < turn90 or rightMotorCount < turn90) {
      balanceLeft();
    }
    totalreset();
    while (leftMotorCount < x and rightMotorCount < x) {
      balanceForward();
    }
  }
}

void backwardsFigureOf8() {
  for (int i = 0; i < 3; i++) {
    while (leftMotorCount < x and rightMotorCount < x) {
      balanceBackward();
    }
    totalreset();
    while (leftMotorCount < turn90 or rightMotorCount < turn90) {
      balanceLeft();
    }
    totalreset();
  }
  while (leftMotorCount < (2 * x) and rightMotorCount < (2 * x)) {
    balanceBackward();
}
  for (int i = 0; i < 3; i++) {
    totalreset();
    while (leftMotorCount < turn90 or rightMotorCount < turn90) {
      balanceRight();
    }
    totalreset();
    while (leftMotorCount < x and rightMotorCount < x) {
      balanceBackward();
    }
  }
}

void loop()
{
  forwardsFigureOf8();
  totalreset();
  delay(1000);
  backwardsFigureOf8();
  totalreset();
  while (true) {}
  
}

void hardStop() {
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
  analogWrite(leftForward, 0);
  analogWrite(rightForward, 0);
  analogWrite(leftBackward, 0);
  analogWrite(rightBackward, 0);
  delay(500);
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

