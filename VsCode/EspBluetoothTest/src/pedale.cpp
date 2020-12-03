#include <MyEspInclude.h>


SSD1306 display(0x3c,5,4);

myValues::myValues(void)
{
    ModeEcran = 0;
    Status = 0;
    TempMoteur = 0;         //ADC
    TempGenerateur = 0;     //ADC
    VitesseMoteur = 0;      //ADC
    VitesseGenerateur = 0;  //ADC
    TensionMoteur = 0;      //ADC
    TensionGenerateur = 0;  //ADC
    FreqMoteur = 0;
    FreqGenerateur = 0;
    PWMMoteur = 0;
    PWMGenerateur = 0;    
    Current = 0;            //ADC
}

void myValues::update(void)
{
  this->VitesseMoteur = (26)*15767/4095;
  this->TensionMoteur = analogRead(36)*44/6824;
  this->TempMoteur = analogRead(25)*20/819;

  this->Current = analogRead(2)/3276;
  this->VitesseGenerateur = analogRead(12)*15767/4095;
  this->TensionGenerateur = analogRead(15)*88/6825;
  this->TempGenerateur = analogRead(13)*20/819;


}

Display::Display(void)
{
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //display.setLogBuffer(5, 30);
        display.resetDisplay();
        display.drawStringMaxWidth(0, 0, 128, "U Mote");
        display.drawStringMaxWidth(0, 16, 128,"U Gene" );
        display.drawStringMaxWidth(0, 32, 128,"T Mote" );
        display.drawStringMaxWidth(0, 48, 128,"T Gene" );

        display.drawStringMaxWidth(93, 0, 128, "V");
        display.drawStringMaxWidth(93, 16, 128,"V" );
        display.drawStringMaxWidth(93, 32, 128,"C" );
        display.drawStringMaxWidth(93, 48, 128,"C" );
  display.display();
  currentmode = 0;
}

void Display::Update(int mode, myValues* Values)
{
    

  switch(mode)
  {
      case 0:

      if(currentmode != mode)
      {
        display.resetDisplay();
        display.drawStringMaxWidth(0, 0, 128, "U Mote");
        display.drawStringMaxWidth(0, 16, 128,"U Gene" );
        display.drawStringMaxWidth(0, 32, 128,"T Mote" );
        display.drawStringMaxWidth(0, 48, 128,"T Gene" );

        display.drawStringMaxWidth(93, 0, 128, "V");
        display.drawStringMaxWidth(93, 16, 128,"V" );
        display.drawStringMaxWidth(93, 32, 128,"C" );
        display.drawStringMaxWidth(93, 48, 128,"C" );
      }
      
      else
      {
        for(int y=0;y<63;y++)
        {
          for(int x = 55;x<90;x++)
          {
            display.clearPixel(x,y);
          }
        }
      }
        display.drawStringMaxWidth(55, 0, 128,String(Values->TensionMoteur) );
        display.drawStringMaxWidth(55, 16, 128,String(Values->TensionGenerateur));
        display.drawStringMaxWidth(55, 32, 128,String(Values->TempMoteur));
        display.drawStringMaxWidth(55, 48, 128,String(Values->TempGenerateur));
break;
      case 1:
      if(currentmode != mode)
      {
        display.resetDisplay();
        display.drawStringMaxWidth(0, 0, 128,"S Mote" );
        display.drawStringMaxWidth(0, 16, 128,"U Mote" );
        display.drawStringMaxWidth(0, 32, 128,"P Mote" );
        display.drawStringMaxWidth(0, 48, 128,"F Mote" );

        display.drawStringMaxWidth(93, 0, 128, "RPM");
        display.drawStringMaxWidth(93, 16, 128,"V" );
        display.drawStringMaxWidth(93, 32, 128,"%" );
        display.drawStringMaxWidth(93, 48, 128,"HZ" );
      }
      else
      {
        for(int y=0;y<63;y++)
        {
          for(int x = 55;x<90;x++)
          {
            display.clearPixel(x,y);
          }
        }
      }
        display.drawStringMaxWidth(55, 0, 128,String(Values->VitesseMoteur));
        display.drawStringMaxWidth(55, 16, 128,String(Values->TensionMoteur));
        display.drawStringMaxWidth(55, 32, 128,String(Values->PWMMoteur));
        display.drawStringMaxWidth(55, 48, 128,String(Values->FreqMoteur) );
      
break;
      case 2:
      if(currentmode != mode)
      {
        display.resetDisplay();
        display.drawStringMaxWidth(0, 0, 128,"S Gene");
        display.drawStringMaxWidth(0, 16, 128,"U Gene" );
        display.drawStringMaxWidth(0, 32, 128,"P Gene" );
        display.drawStringMaxWidth(0, 48, 128,"F Gene" );

        display.drawStringMaxWidth(93, 0, 128, "RPM");
        display.drawStringMaxWidth(93, 16, 128,"V" );
        display.drawStringMaxWidth(93, 32, 128,"%" );
        display.drawStringMaxWidth(93, 48, 128,"HZ" );
      }
      else
      {
        for(int y=0;y<63;y++)
        {
          for(int x = 55;x<90;x++)
          {
            display.clearPixel(x,y);
          }
        }
      }
        display.drawStringMaxWidth(55, 0, 128,String(Values->VitesseGenerateur));
        display.drawStringMaxWidth(55, 16, 128,String(Values->TensionGenerateur));
        display.drawStringMaxWidth(55, 32, 128,String(Values->PWMGenerateur));
        display.drawStringMaxWidth(55, 48, 128,String(Values->FreqGenerateur));
        break;
  }
  currentmode = mode;
  display.display();
}


MyTime::MyTime(void)
{
  Time = millis();
  PidTime = 0;
  DisplayTime = 0;
}

void MyTime::update(void)
{
  Time = millis();
}


myPID::myPID(void)
{


}


float myPID::updateMotor(float kp, float ki, float kd, int MAXSPEED, int SpeedLive, int SpeedSet, int Delay, float PWMLive)
{
  float PwmPutPut =PWMLive;
  int speedDif = SpeedLive - SpeedSet;
  PwmPutPut -= (float)speedDif/(float)MAXSPEED * (1+kp);


  float PWShouldBe = (float)SpeedSet/(float)MAXSPEED;
  PwmPutPut -= (PWShouldBe-PwmPutPut)*(ki);

/*
    Serial.print("\tki:");
  Serial.print((PWShouldBe-PwmPutPut)*(1+ki));
*/
  if(PwmPutPut > 1)
  {
    PwmPutPut=1;
    //Serial.print("putput >1");
  }
  else if(PwmPutPut < 0)
  {
    PwmPutPut=0;
    //Serial.print("putput <0");
  }

return PwmPutPut;
}



float myPID::updateGenerator(float kp, float ki, float kd, float MaxCurrent, int CurrentLive, int CurrentSet, int Delay, float PWMLive)
{
  float PwmPutPut = PWMLive;
  int VoltDif = CurrentLive - CurrentSet;
  PwmPutPut += (float)VoltDif/(float)MaxCurrent * (kp);


  float PWShouldBe = (float)CurrentSet/(float)MaxCurrent;
  PwmPutPut += (PWShouldBe-PwmPutPut)*(ki);

/*
    Serial.print("\tki:");
  Serial.print((PWShouldBe-PwmPutPut)*(1+ki));
*/
  if(PwmPutPut > 1)
  {
    PwmPutPut=1;
    //Serial.print("putput >1");
  }
  else if(PwmPutPut < 0.5)
  {
    PwmPutPut=0.5;
    //Serial.print("putput <0");
  }
    return PwmPutPut;
}