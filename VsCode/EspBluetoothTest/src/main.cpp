#include <MyEspInclude.h>




void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  myValues Values;
  Display Display(0,&Values);
 
  //ledcAttachPin(16,0);//ledcAttachPin(gpio, channel)
  //ledcSetup(0,100000,8);//ledcSetup(channel, frequency, resolution)
  //ledcWrite(0,0.5*255);//ledcWrite(channel, dutycycle)
  //Serial.println("PWM started");

//****BLE***

  //myBLE myBLE;

  //myBLE.Update(&Values);
  //Serial.println("BLE started");

  


  //Serial.println(analogRead(39));
char pin = 13;
pinMode(pin, ANALOG);
bool t1 = adcAttachPin(pin);
Serial.print("test 1:");
Serial.println(t1);
int8_t channel = digitalPinToAnalogChannel(pin);
int8_t pad = digitalPinToTouchChannel(pin);
Serial.print("channel:");
Serial.print(channel);
Serial.print("\t, pad:");
Serial.println(pad);
}

void loop() 
{

  Serial.print("\rADC39: ");
  Serial.print(analogRead(39));
  Serial.print("\t");
  
  Serial.print("ADC36: ");
  Serial.print(analogRead(36));
  Serial.print("\t");

  Serial.print("ADC0: ");
  Serial.print(analogRead(0));
  Serial.print("\t");
  Serial.print("ADC2: ");
  Serial.print(analogRead(2));
  Serial.print("\t");
  Serial.print("ADC4: ");
  Serial.print(analogRead(4));
  Serial.print("\t");
  Serial.print("ADC12: ");
  Serial.print(analogRead(12));
  Serial.print("\t");
  Serial.print("ADC13: ");
  Serial.print(analogRead(13));
  Serial.print("\t");
  Serial.print("ADC14: ");
  Serial.print(analogRead(14));
  Serial.print("\t");
  Serial.print("ADC15: ");
  Serial.print(analogRead(15));
  Serial.print("\t");
  Serial.print("ADC25: ");
  Serial.print(analogRead(25));
  Serial.print("\t");
  Serial.print("ADC26: ");
  Serial.print(analogRead(26));
  Serial.print("\t");
  delay(2);


}