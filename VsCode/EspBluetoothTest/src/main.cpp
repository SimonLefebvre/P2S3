#include <MyEspInclude.h>




void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  myValues Values;
  Display Display(0,&Values);
 
  pinMode(0,OUTPUT);
  ledcAttachPin(16,0);//ledcAttachPin(gpio, channel)
  //ledcSetup(0,1000000,10);//ledcSetup(channel, frequency, resolution)
  //ledcWrite(0,0.25*1024);//ledcWrite(channel, dutycycle)
  Serial.println("PWM started");

//****BLE***

  myBLE myBLE;

  myBLE.Update(&Values);
  Serial.println("BLE started");

}

void loop() 
{





}