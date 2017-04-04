int m1enable = 9;
int m1forward = 7;
int m1backward = 8;
int m2enable = 12;
int m2forward = 10;
int m2backward = 11;

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
