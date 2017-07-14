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
const int power = 150;

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

void balanceForward()
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
  balanceForward();
  if (leftMotorCount > 1055 or rightMotorCount > 1055) {
    hardstop();
    while (true) {
    }
  }
}
void hardStop()
{
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
  analogWrite(leftForward, 0);
  analogWrite(rightForward, 0);
  analogWrite(leftBackward, 0);
  analogWrite(rightBackward, 0);
}
