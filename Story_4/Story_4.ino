unsigned int const leftEnable = 9;
unsigned int const leftForward = 8;
unsigned int const leftBackward = 7;
unsigned int const rightEnable = 10;
unsigned int const rightForward = 12;
unsigned int const leftBackward = 11;

void setup()
{
  pinMode(leftEnable, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
}

void loop()
{
  digitalWrite(leftEnable, HIGH);
  digitalWrite(leftForward, HIGH);
  digitalWrite(rightEnable, HIGH);
  digitalWrite(rightForward, HIGH);
  delay(1000);
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftEnable, LOW);
  digitalWrite(rightEnable, LOW);
  delay(1000);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(leftEnable, HIGH);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightEnable, HIGH);
  delay(1000);
  digitalWrite(leftBackward, LOW);
  digitalWrite(leftBackward, LOW);
}
