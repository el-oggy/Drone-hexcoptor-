void setup() {

  pinMode(PB0, OUTPUT);
  pinMode(PB14, OUTPUT);
  pinMode(PE1, OUTPUT);
}

void loop() {

  digitalWrite(PB0, HIGH);
  delay(1000);
  digitalWrite(PB0, LOW);

  digitalWrite(PB14, HIGH);
  delay(1000);
  digitalWrite(PB14, LOW);

  digitalWrite(PE1, HIGH);
  delay(1000);
  digitalWrite(PE1, LOW);
}