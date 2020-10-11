#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial BT;
void setup() {
  // put your setup code here, to run once:
  BT.begin("Myesp32");
  Serial.begin(9600);
  Serial.println("Bt started");
}

void loop() {
  // put your main code here, to run repeatedly:
  static bool test = false;
  if(BT.available())
  {
    Serial.println("Data is available");
    Serial.println(BT.read());
  }

  

  if(test ==false && BT.hasClient())
  {
    Serial.println("New Client has been connected");
    test = true;
  }
}