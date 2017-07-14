//m1 left
//m2 right
unsigned int const m1enable = 9;
unsigned int const m1forward = 8;
unsigned int const m1backward = 7;
unsigned int const m2enable = 10;
unsigned int const m2forward = 12;
unsigned int const m2backward = 11;
unsigned int const m1pin = 2;
unsigned int const m2pin = 3;
volatile unsigned int m1counter = 0;
volatile unsigned int m2counter = 0;
unsigned int const power = 171;
unsigned int const x = 67;
unsigned int const turn90 = 86;
unsigned int const forwardrightturn90 = 76;

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

void balancebackward() {
  if (m1counter > m2counter) {
    analogWrite(m2backward, power);
    analogWrite(m1backward, 0);
  }
  else if (m2counter > m1counter) {
    analogWrite(m2backward, 0);
    analogWrite(m1backward, power);
  }
  else {
    backward();
  }
}

void balanceforward() {
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

void balanceright() {
  if (m2counter > m1counter) {
    analogWrite(m1forward, power);
    analogWrite(m2backward, 0);
  }
  else if (m1counter > m2counter) {
    analogWrite(m1forward, 0);
    analogWrite(m2backward, power);
  }
  else {
    turnright();
  }
}

void balanceleft() {
  if (m2counter > m1counter) {
    analogWrite(m1backward, power);
    analogWrite(m2forward, 0);
  }
  else if (m1counter > m2counter) {
    analogWrite(m1backward, 0);
    analogWrite(m2forward, power);
  }
  else {
    turnleft();
  }
}

void resetcounters() {
  m1counter = 0;
  m2counter = 0;
}

void totalreset() {
  resetcounters();
  hardstop();
}

void forwardsfigureof8() {
  for (int i = 0; i < 3; i++) {
    while (m1counter < x and m2counter < x) {
      balanceforward();
    }
    totalreset();
    while (m1counter < forwardrightturn90 or m2counter < forwardrightturn90) {
      balanceright();
    }
    totalreset();
  }
  while (m1counter < (2.75 * x) and m2counter < (2.75 * x)) {
    balanceforward();
}
  for (int i = 0; i < 3; i++) {
    totalreset();
    while (m1counter < turn90 or m2counter < turn90) {
      balanceleft();
    }
    totalreset();
    while (m1counter < x and m2counter < x) {
      balanceforward();
    }
  }
}

void backwardsfigureof8() {
  for (int i = 0; i < 3; i++) {
    while (m1counter < x and m2counter < x) {
      balancebackward();
    }
    totalreset();
    while (m1counter < turn90 or m2counter < turn90) {
      balanceleft();
    }
    totalreset();
  }
  while (m1counter < (2 * x) and m2counter < (2 * x)) {
    balancebackward();
}
  for (int i = 0; i < 3; i++) {
    totalreset();
    while (m1counter < turn90 or m2counter < turn90) {
      balanceright();
    }
    totalreset();
    while (m1counter < x and m2counter < x) {
      balancebackward();
    }
  }
}

void loop()
{
  forwardsfigureof8();
  totalreset();
  delay(1000);
  backwardsfigureof8();
  totalreset();
  while (true) {}
  
}

void hardstop() {
  digitalWrite(m1enable, HIGH);
  digitalWrite(m2enable, HIGH);
  analogWrite(m1forward, 0);
  analogWrite(m2forward, 0);
  analogWrite(m1backward, 0);
  analogWrite(m2backward, 0);
  delay(500);
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
void backward() {
  analogWrite(m1forward, 0);
  analogWrite(m2forward, 0);
  analogWrite(m1backward, power);
  analogWrite(m2backward, power);
}

