// Library's
#include <SoftwareSerial.h>

// Initilization
SoftwareSerial Genotronex(10,11);
// Bluetooth on pin 11 and 10.

String bluetoothData = ""; //Data from Genotronex

int sensorPinA = A0; // select the input pin for Analog Mic
int sensorPinD = 7; // select the input pin for Digital Mic
bool noise = false;
unsigned long beginWindow = 0;
unsigned long endWindow = 0;
//int sizeWindow = 30000;
int refreshRate = 100;

bool noiseCounter[300];
int arrayCounter = 0;

int buttonPin = 2; // select the pin for the LED
bool prevButton = false;

int sensorValueA = 0; // variable to store the Analog value coming from the sensor
int sensorValueD = 0; // variable to store the Digital value coming from the sensor

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
  beginWindow = millis();
  microphone();

//  if((beginWindow-endWindow) > sizeWindow){
//    endWindow = beginWindow - sizeWindow;
//  }

  if((beginWindow-endWindow)>=refreshRate){
    noiseCounter[arrayCounter]=noise;
    if(arrayCounter>299){
      arrayCounter=0;
    }
    else{
      arrayCounter++;
    }
    endWindow = beginWindow;
    Serial.println(getPercentage());
  }
  
  if(Genotronex.available())
  {
    bluetoothData=Genotronex.readString();
    delay(10);
    Serial.println(bluetoothData);
  }
  
  if(digitalRead(buttonPin)== true && prevButton==false)
  {
    sendMessage();
    prevButton = true;
  }
  else{
    prevButton = false;
  }
}

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
  sensorValueA = analogRead(sensorPinA);
  sensorValueD = digitalRead(sensorPinD);
//  Serial.println(sensorValueA);
  if (sensorValueD == HIGH)
  {
//    Serial.println("TRUE!");
    noise = true;
  }
  else
  {
    noise = false;
  }
}

int getPercentage(){
  int y= 0;
  for(int i = 0; i<300; i++){
    if(noiseCounter[i]==1){
      y++;
    }
  }
  int percentage = y;
  return percentage;
}

