int const m1enable = 9;
int const m1forward = 8;
int const m1backward = 7;
int const m2enable = 10;
int const m2forward = 12;
int const m2backward = 11;
int const m1pin = 2;
int const m2pin = 3;
volatile int m1counter = 0;
volatile int m2counter = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(m1pin, INPUT);
  pinMode(m2pin, INPUT);
  attachInterrupt(0, m1change, RISING);
  attachInterrupt(1, m2change, RISING);
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
    analogWrite(m2forward, 170);
    analogWrite(m1forward, 0);
  }
  else if (m2counter > m1counter) {
    analogWrite(m2forward, 0);
    analogWrite(m1forward, 170);
  }
  else {
    analogWrite(m2forward, 170);
    analogWrite(m1forward, 170);
  }
}

void loop()
{
  analogWrite(m1forward, 170);
  analogWrite(m2forward, 170);
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
  delay(10000);
  //while (1) {
    //delay(50);
    //Serial.print(m1counter);
    //Serial.print(":");
    //Serial.println(m2counter);
 // }
  m1counter = m2counter;
  hardstop();
  while (1) {
    delay(10);
    hardstop();
  }+
}
void hardstop() {
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
  analogWrite(m1forward, 0);
  analogWrite(m2forward, 0);
}

