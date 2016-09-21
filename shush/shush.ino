//Initialization
#define micSens A0

int led = 13;
int sensorValue = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(micSens);
  Serial.println(sensorValue);
  delay(100);
}
