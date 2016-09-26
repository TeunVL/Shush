// Library's
#include <SoftwareSerial.h>


// Initilization
SoftwareSerial Genotronex(10,11);
// Bluetooth on pin 11 and 10.

String bluetoothData = ""; //Data from Genotronex

int sensorPinA = A0; // select the input pin for Analog Mic
int sensorPinD = 7; // select the input pin for Digital Mic
int buttonPin = 2; // select the pin for the LED
int sensorValueA = 0; // variable to store the Analog value coming from the sensor
int sensorValueD = 0; // variable to store the Digital value coming from the sensor

/* ~~FUNCTIONS~~ */
void moveFlagUp(int servoPin)
{
  /* CODE */
}

void sendMessage()
{
  Genotronex.println("!ALERT!");
  delay(150);
}

void microphone()
{
  sensorValueA = analogRead (sensorPinA);
  sensorValueD = digitalRead (sensorPinD);
  Serial.println ("print analog: " + String(sensorValueA));
  if (sensorValueD == 1)
  {
    Serial.println("TRUE!");
    digitalWrite(0, HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(0, LOW);
  }
  delay(100);
}

void bluetooth()
{
  if(Genotronex.available())
  {
    Serial.println(bluetoothData);
  }
  
  if(digitalRead(buttonPin))
  {
    sendMessage();
  }
}

// Setup
void setup () 
{
  Serial.begin (9600); //Begin serial connection with PC
  pinMode(buttonPin, INPUT); //Make DPin "LEDpin" an output

  Genotronex.begin(9600);
  Genotronex.println("Device Connected");
}

//Main loop
void loop () 
{
  bluetooth();
}
