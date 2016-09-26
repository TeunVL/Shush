int piezo = 4;
int button = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(piezo, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(button))
  {
    digitalWrite(piezo, HIGH);
  }
  else
  {
    digitalWrite(piezo, LOW);
  }
}
