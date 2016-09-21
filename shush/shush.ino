// Initilization
int sensorPinA = A0; // select the input pin for Analog Mic
int sensorPinD = 7; // select the input pin for Digital Mic
int LEDpin = 13; // select the pin for the LED
int sensorValueA = 0; // variable to store the Analog value coming from the sensor
int sensorValueD = 0; // variable to store the Digital value coming from the sensor

/* ~~FUNCTIONS~~ */





// Setup
void setup () 
{
  Serial.begin (9600);
  pinMode(LEDpin, OUTPUT);
}

//Main loop
void loop () 
{
  sensorValueA = analogRead (sensorPinA);
  sensorValueD = digitalRead (sensorPinD);
  Serial.println ("print analog: " + String(sensorValueA));
  if (sensorValueD == 1)
  {
    Serial.println("TRUE!");
    digitalWrite(LEDpin, HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(LEDpin, LOW);
  }
  delay(100);
}
