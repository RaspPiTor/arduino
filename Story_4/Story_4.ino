unsigned int const leftEnable = 9;
unsigned int const leftForward = 8;
unsigned int const leftBackward = 7;
unsigned int const rightEnable = 10;
unsigned int const rightForward = 12;
unsigned int const rightBackward = 11;
unsigned int const power = 171;

void setup()
{
  pinMode(leftEnable, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);
}

void loop()
{
  forward();
  delay(1000);
  hardStop();
  delay(1000);
  backward();
  delay(1000);
  hardStop();
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
void forward()
{
  analogWrite(rightForward, power);
  analogWrite(leftForward, power);
  analogWrite(rightBackward, 0);
  analogWrite(leftBackward, 0);
}
void backward()
{
  analogWrite(leftForward, 0);
  analogWrite(rightForward, 0);
  analogWrite(leftBackward, power);
  analogWrite(rightBackward, power);
}
