//m1 left
//m2 right
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

void leftMotorCountChange()
{
  leftMotorCount++;
}

void rightMotorCountChange()
{
  rightMotorCount++;
}

void balance()
{
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

void loop()
{
  for (int i = 0; i < 4; i++) {
    leftMotorCount = 0;
    rightMotorCount = 0;
    forward();
    while (leftMotorCount < 250 and rightMotorCount < 250) {
      balance();
      delay(10);
    }
    hardstop();
    delay(500);
    turnright();
    delay(445);
    hardstop();
    delay(500);
  }
  hardstop();
  while (1) {}
}
void hardstop()
{
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
  analogWrite(leftForward, 0);
  analogWrite(rightForward, 0);
  analogWrite(leftBackward, 0);
  analogWrite(leftBackward, 0);
}


void forward()
{
  analogWrite(rightForward, power);
  analogWrite(leftForward, power);
  analogWrite(leftBackward, 0);
  analogWrite(leftBackward, 0);
}
void turnright()
{
  analogWrite(rightForward, 0);
  analogWrite(leftForward, power);
  analogWrite(leftBackward, power);
  analogWrite(leftBackward, 0);
}

