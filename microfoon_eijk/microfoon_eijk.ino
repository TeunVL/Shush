int pinA = A0;
int pinD = 7;
int var = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  var = analogRead(pinA);
  Serial.println(var);
  if(digitalRead(pinD))
  {
    Serial.println("TRUE");
  }
}
