//m1 left
//m2 right
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
const int power = 171;
const int x = 70;

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
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
}

void m1change() {
  m1counter++;
}

void m2change() {
  m2counter++;
}

void balance() {
  if (m1counter > m2counter) {
    analogWrite(m2forward, power);
    analogWrite(m1forward, 0);
  }
  else if (m2counter > m1counter) {
    analogWrite(m2forward, 0);
    analogWrite(m1forward, power);
  }
  else {
    forward();
  }
}

void loop()
{
  for (int i = 0; i < 3; i++) {
    m1counter = 0;
    m2counter = 0;
    forward();
    while (m1counter < x and m2counter < x) {
      balance();
      delay(1);
    }
    hardstop();
    delay(505);
    turnright();
    delay(895);
    hardstop();
    delay(505);
  }
  m1counter = 0;
  m2counter = 0;
  forward();
  while (m1counter < (2.75 * x) and m2counter < (2.75 * x)) {
    balance();
    delay(1);
}
  for (int i = 0; i < 3; i++) {
    //delay(505);
    turnleft();
    delay(805);
    hardstop();
    delay(505);
    m1counter = 0;
    m2counter = 0;
    forward();
    while (m1counter < x and m2counter < x) {
      balance();
      delay(1);
    }
    hardstop();
    
  }
  turnleft();
  delay(155);
  hardstop();
  forward();
  delay(100);
  hardstop();
  while (1) {}
}

  }
  turnleft();
  delay(155);
  hardstop();
  forward();
  delay(100);
  hardstop();
  while (1) {}
}



void hardstop() {
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
  analogWrite(m1forward, 0);
  analogWrite(m2forward, 0);
  analogWrite(m1backward, 0);
  analogWrite(m2backward, 0);
}


void forward() {
  analogWrite(m2forward, power);
  analogWrite(m1forward, power);
  analogWrite(m2backward, 0);
  analogWrite(m1backward, 0);
}
void turnright() {
  analogWrite(m2forward, 0);
  analogWrite(m1forward, power);
  analogWrite(m2backward, power);
  analogWrite(m1backward, 0);
}
void turnleft() {
  analogWrite(m1forward, 0);
  analogWrite(m2forward, power);
  analogWrite(m1backward, power);
  analogWrite(m2backward, 0);
}

