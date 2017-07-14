int leftEnable = 9;
int leftForward = 8;
int leftBackward = 7;
int rightEnable = 10;
int rightForward = 12;
int leftBackward = 11;

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
