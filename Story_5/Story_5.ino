int m1enable = 9;
int m1forward = 8;
int m1backward = 7;
int m2enable = 10;
int m2forward = 12;
int m2backward = 11;
int m1pin = 2;
int m2pin = 3;
volatile int m1counter = 0;
volatile int m2counter = 0;

void setup()
{
  pinMode(m1pin, INPUT);
  pinMode(m2pin, INPUT);
  attachInterrupt(0, m1change, CHANGE);
  attachInterrupt(1, m2change, CHANGE);
  pinMode(m1enable, OUTPUT);
  pinMode(m1forward, OUTPUT);
  pinMode(m1backward, OUTPUT);
  pinMode(m2enable, OUTPUT);
  pinMode(m2forward, OUTPUT);
  pinMode(m2backward, OUTPUT);
}

void m1change() {
  m1counter++;
  balance();
}

void m2change() {
  m2counter++;
  balance();
}

void balance() {
  if (m1counter > m2counter) {
    digitalWrite(m2forward, HIGH);
    digitalWrite(m1forward, LOW);
  }
  else if (m2counter > m1counter) {
    digitalWrite(m2forward, LOW);
    digitalWrite(m1forward, HIGH);
  }
  else {
    digitalWrite(m2forward, HIGH);
    digitalWrite(m1forward, HIGH);
  }
}

void loop()
{
  digitalWrite(m1forward, HIGH);
  digitalWrite(m2forward, HIGH);
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
  digitalWrite(m1backward, HIGH);
  digitalWrite(m2backward, HIGH);
  delay(10000);
  hardstop();
  while (1) {delay(10);hardstop();}
}
void hardstop() {
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
  digitalWrite(m1backward, LOW);
  digitalWrite(m2backward, LOW);
  digitalWrite(m1forward, LOW);
  digitalWrite(m2forward, LOW);
}
