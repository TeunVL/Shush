// Library's
#include <SoftwareSerial.h>
#include <Servo.h>

// Initilization
/*LED lights*/
int LedG = 3;
int LedO = 4;
int LedR = 5;

/*Set stat & perc*/
int perc = 0;
int stage = 0;

/*Servo*/
Servo serv;
bool servoWrite = false;

/*Bluetooth Stuff*/
SoftwareSerial Genotronex(10,11);
// Bluetooth on pin 11 and 10.
String bluetoothData = ""; //Data from Genotronex

bool messageAlreadySend = false;

/*Microphone sensor*/
int sensorPinD = 7; // select the input pin for Digital Mic
int sensorValueD = 0; // variable to store the Digital value coming from the sensor

/*drukSensor Stuff*/
int drukSensor = A1;
int dValue = 0;
int prevButton = false;

/*Time Window*/
bool noise = false;
unsigned long beginWindow = 0;
unsigned long endWindow = 0;
//int sizeWindow = 30000;
int refreshRate = 100;

bool noiseCounter[300];
int arrayCounter = 0;

// Setup
void setup () 
{
  Serial.begin (9600); //Begin serial connection with PC
  pinMode(LedG,OUTPUT);
  pinMode(LedO,OUTPUT);
  pinMode(LedR,OUTPUT);
  serv.attach(9);
  serv.write(10);
  Genotronex.begin(9600);
  Genotronex.println("Device Connected");
}

//Main loop
void loop () 
{
  dValue = analogRead(drukSensor);
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
    perc = getPercentage();
    Serial.println(perc);
  }
  stage = getState(perc);
  interact(stage, messageAlreadySend, servoWrite);
  
  if(Genotronex.available())
  {
    bluetoothData=Genotronex.readString();
    delay(10);
    Serial.println(bluetoothData);
  }
  
  if(dValue >= 100 && prevButton==false)
  {
    sendMessage();
    prevButton = true;
  }
  else{
    prevButton = false;
  }
}

/* ~~FUNCTIONS~~ */
void interact(int z, bool messageSend, bool servoWritten)
{
  switch(z)
  {
    case 0:
      digitalWrite(LedG, HIGH);
      digitalWrite(LedO, LOW);
      digitalWrite(LedR, LOW);
      break;
    case 1:
      digitalWrite(LedG, LOW);
      digitalWrite(LedO, HIGH);
      digitalWrite(LedR, LOW);
      moveFlagDown();
      break;
    case 2:
      digitalWrite(LedG, LOW);
      digitalWrite(LedO, LOW);
      digitalWrite(LedR, HIGH);
      break;
     case 3:
      digitalWrite(LedG, LOW);
      digitalWrite(LedO, LOW);
      digitalWrite(LedR, HIGH);
      moveFlagUp();
      messageAlreadySend = false;
      break;
     case 4:
      digitalWrite(LedG, LOW);
      digitalWrite(LedO, LOW);
      digitalWrite(LedR, HIGH);
      if(!messageSend)
      {
        sendMessage();
        messageAlreadySend = true;
      }
      break;
  }
}

int getState(int z)
{
  if(z < 30)
  {
    return 0;
  }
  else if(z >= 30 && z < 50)
  {
    return 1;
  }
  else if(z >= 50 && z < 100)
  {
    return 2;
  }
  else if(z >= 100 && z < 150)
  {
    return 3;
  }
  else if(z >= 150)
  {
    return 4;
  }
}

void moveFlagUp()
{
  
  serv.write(100);
}

void moveFlagDown()
{
  serv.write(10);
}

void sendMessage()
{
  Genotronex.println("!ALERT!");
}

void microphone()
{
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
