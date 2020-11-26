#include <MyEspInclude.h>
#include "pid.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

 


}

void loop() 
{
  myValues Values;
  Display Display;
  int Displaycpt=0;
  int DisplayChangeDelay=0;

  Values.FreqGenerateur = 100000;
  Values.FreqMoteur = 100000;
  Values.PWMMoteur = 0.5*255;
  Values.PWMGenerateur = 00.5*255;

  float kp = 10;
  float ki = 0;
  float kd = 0;

   PID pid = PID(0.01, 3500, 0, 10, 0, 0);

  ledcAttachPin(16,0);//ledcAttachPin(gpio, channel)
  ledcSetup(0,Values.FreqMoteur,8);//ledcSetup(channel, frequency, resolution)
  ledcWrite(0,Values.PWMMoteur);//ledcWrite(channel, dutycycle)
  Serial.println("PWM started");

  ledcAttachPin(14,1);//ledcAttachPin(gpio, channel)
  ledcSetup(1,Values.FreqGenerateur,8);//ledcSetup(channel, frequency, resolution)
  ledcWrite(1,Values.PWMGenerateur);//ledcWrite(channel, dutycycle)
  Serial.println("PWM started");

  double val = 1500;

  while(1)
  {
    Values.VitesseMoteur = (float)analogRead(26)*15767/4095;
    Values.PWMMoteur = 255*(pid.calculate(val, Values.VitesseMoteur))/3500;
    ledcWrite(0,Values.PWMMoteur);//ledcWrite(channel, dutycycle)
    delay(10);
    Serial.print("\n)");
    Serial.print(Values.VitesseMoteur);
    Serial.print("\t)");
    Serial.print(Values.PWMMoteur);
    int test = Serial.read();
  if(test != -1)
  {
    switch (test)
    {
    case '1':
    Serial.print("\t Kp up)");
    pid.pimpl._Ki ++;
    break;
    case '2':
    Serial.print("\t Kp down");
    break;
    case '3':
    Serial.print("\t Ki up");
    break;
    case '4':
    Serial.print("\t Ki down");
    break;
    case '5':
    Serial.print("\t Kd up");
    break;
    case '6':
    Serial.print("\t Kd down");
    break;
    }
  }

}
/*
  int test = Serial.read();
  if(test != -1)
  {
    switch (test)
    {
    case '1':
    if(Values.PWMMoteur < 255)Values.PWMMoteur ++;
    ledcWrite(0,Values.PWMMoteur);
    Serial.print("\nPwm ++ Moteur ");
      break;
      case '2':
    if(Values.PWMMoteur > 0)Values.PWMMoteur --;
    ledcWrite(0,Values.PWMMoteur);
    Serial.print("\nPwm -- Moteur ");
      break;
      case '3':
    if(Values.PWMGenerateur < 255)Values.PWMGenerateur ++;
    ledcWrite(1,Values.PWMGenerateur);
    Serial.print("\nPwm ++ Generateur ");
      break;
      case '4':
      if(Values.PWMGenerateur > 0)Values.PWMGenerateur --;
      ledcWrite(1,Values.PWMGenerateur);
    Serial.print("\nPwm -- Generateur ");
      break;
    
    default:
    Serial.print((char)test);
      break;
    }
  }

  
  for(int i =0;i<10;i++)
  {
    Values.VitesseMoteur = (float)analogRead(26)*15767/4095;
    Values.VitesseGenerateur = (float)analogRead(12)*15767/4095;
    Values.TensionMoteur = (float)analogRead(36)*44/6824;
    Values.TensionGenerateur = (float)analogRead(15)*88/6825;
    Values.TempMoteur = (float)analogRead(25)*20/819;
    Values.TempGenerateur = (float)analogRead(13)*20/819;
    Values.Current = (float)analogRead(2)/3276;
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

}*/