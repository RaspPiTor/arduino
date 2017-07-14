int leftEnable = 5;
int leftForward = 3;
int leftBackward = 4;
int rightEnable = 8;
int rightForward = 6;
int leftBackward = 7;

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
