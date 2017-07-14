unsigned int const leftEnable = 5;
unsigned int const leftForward = 3;
unsigned int const leftBackward = 4;
unsigned int const rightEnable = 8;
unsigned int const rightForward = 6;
unsigned int const leftBackward = 7;

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
  delay(10000);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, LOW);
  delay(1000);
  digitalWrite(leftBackward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(leftEnable, LOW);
  digitalWrite(rightEnable, LOW);
  while (1) {}
}
