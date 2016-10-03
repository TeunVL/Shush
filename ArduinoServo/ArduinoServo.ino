#include "Servo.h"

Servo serv;
int readPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  serv.attach(9);
  serv.write(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(readPin))
  {
    serv.write(100);
  }
  else
  {
    serv.write(10);
  }
}
