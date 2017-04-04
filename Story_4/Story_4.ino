int m1enable = 5;
int m1forward = 3;
int m1backward = 4;
int m2enable = 8;
int m2forward = 6;
int m2backward = 7;

void setup()
{
  pinMode(m1enable, OUTPUT);
  pinMode(m1forward, OUTPUT);
  pinMode(m1backward, OUTPUT);
  pinMode(m2enable, OUTPUT);
  pinMode(m2forward, OUTPUT);
  pinMode(m2backward, OUTPUT);
}

void loop()
{
  digitalWrite(m1enable, HIGH);
  digitalWrite(m1forward, HIGH);
  digitalWrite(m2enable, HIGH);
  digitalWrite(m2forward, HIGH);
  delay(1000);
  digitalWrite(m1forward, LOW);
  digitalWrite(m2forward, LOW);
  digitalWrite(m1enable, LOW);
  digitalWrite(m2enable, LOW);
  delay(1000);
  digitalWrite(m1backward, HIGH);
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2backward, HIGH);
  digitalWrite(m2enable, HIGH);
  delay(1000);
  digitalWrite(m1backward, LOW);
  digitalWrite(m2backward, LOW);
}
