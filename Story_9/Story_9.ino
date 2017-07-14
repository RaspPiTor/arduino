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

void balancebackward() {
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

void balanceforward() {
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

void balanceright() {
  if (rightMotorCount > leftMotorCount) {
    analogWrite(leftForward, power);
    analogWrite(rightBackward, 0);
  }
  else if (leftMotorCount > rightMotorCount) {
    analogWrite(leftForward, 0);
    analogWrite(rightBackward, power);
  }
  else {
    turnright();
  }
}

void balanceleft() {
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

void resetcounters() {
  leftMotorCount = 0;
  rightMotorCount = 0;
}

void totalreset() {
  resetcounters();
  hardstop();
}

void forwardsfigureof8() {
  for (int i = 0; i < 3; i++) {
    while (leftMotorCount < x and rightMotorCount < x) {
      balanceforward();
    }
    totalreset();
    while (leftMotorCount < forwardrightturn90 or rightMotorCount < forwardrightturn90) {
      balanceright();
    }
    totalreset();
  }
  while (leftMotorCount < (2.75 * x) and rightMotorCount < (2.75 * x)) {
    balanceforward();
}
  for (int i = 0; i < 3; i++) {
    totalreset();
    while (leftMotorCount < turn90 or rightMotorCount < turn90) {
      balanceleft();
    }
    totalreset();
    while (leftMotorCount < x and rightMotorCount < x) {
      balanceforward();
    }
  }
}

void backwardsfigureof8() {
  for (int i = 0; i < 3; i++) {
    while (leftMotorCount < x and rightMotorCount < x) {
      balancebackward();
    }
    totalreset();
    while (leftMotorCount < turn90 or rightMotorCount < turn90) {
      balanceleft();
    }
    totalreset();
  }
  while (leftMotorCount < (2 * x) and rightMotorCount < (2 * x)) {
    balancebackward();
}
  for (int i = 0; i < 3; i++) {
    totalreset();
    while (leftMotorCount < turn90 or rightMotorCount < turn90) {
      balanceright();
    }
    totalreset();
    while (leftMotorCount < x and rightMotorCount < x) {
      balancebackward();
    }
  }
}

void loop()
{
  forwardsfigureof8();
  totalreset();
  delay(1000);
  backwardsfigureof8();
  totalreset();
  while (true) {}
  
}

void hardstop() {
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
void turnright() {
  analogWrite(rightForward, 0);
  analogWrite(leftForward, power);
  analogWrite(rightBackward, power);
  analogWrite(leftBackward, 0);
}
void turnleft() {
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

