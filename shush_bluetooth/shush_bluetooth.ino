#include <SoftwareSerial.h>// import the serial library

SoftwareSerial Genotronex(10, 11);
int BluetoothData;

void setup() {
  Serial.begin(9600);
  Genotronex.begin(9600);

}

void loop() {
  if (Genotronex.available()){
    BluetoothData=Genotronex.read();
    if(BluetoothData=='1'){
      Serial.println("Hoi");
      Genotronex.println("Hoi");
    }
  }
}
