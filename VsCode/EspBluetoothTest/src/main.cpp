#include <MyEspInclude.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

 
  //ledcAttachPin(16,0);//ledcAttachPin(gpio, channel)
  //ledcSetup(0,100000,8);//ledcSetup(channel, frequency, resolution)
  //ledcWrite(0,0.5*255);//ledcWrite(channel, dutycycle)
  //Serial.println("PWM started");


}

void loop() 
{
  myValues Values;
  Display Display;
  int Displaycpt=0;
  int DisplayChangeDelay=0;
while(1)
{



  for(int i =0;i<10;i++)
  {

    //ADC
    //2   Speed moteur
    //12  Flyback Voltage
    //13  Speed Generateur
    //15  Temp Generateur
    //25  Temp moteur
    //36  Current
    //39  Buck Voltage
    Values.VitesseMoteur = analogRead(2);
    Values.TensionGenerateur = analogRead(12);
    Values.VitesseGenerateur = analogRead(13);
    Values.TempGenerateur = analogRead(15);
    Values.TempMoteur = analogRead(25);
    Values.Current = analogRead(36);
    Values.TensionMoteur = analogRead(39);
    delay(2);
  }
  DisplayChangeDelay ++;
  Display.Update(Displaycpt,&Values);
  if(DisplayChangeDelay >100)
  {
    DisplayChangeDelay =0;
    Displaycpt ++;
    if(Displaycpt >2)Displaycpt=0;
  }

}





}