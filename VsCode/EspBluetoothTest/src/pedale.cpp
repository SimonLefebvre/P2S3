#include <MyEspInclude.h>


SSD1306 display(0x3c,5,4);

myValues::myValues(void)
{
    ModeEcran = 0;
    Status = 0;
    TempMoteur = 0;
    TempGenerateur = 0;
    VitesseMoteur = 0;
    VitesseGenerateur = 0;
    TensionMoteur = 0;
    TensionGenerateur = 0;
    FreqMoteur = 0;
    FreqGenerateur = 0;
    PWMMoteur = 0;
    PWMGenerateur = 0;
    Current = 0;
}
myValues::myValues(int* info, int* ADC, int* PWM)
{
    ModeEcran = info[0];
    Status = info[1];
    TempMoteur = ADC[0];
    TempGenerateur = ADC[1];
    VitesseMoteur = ADC[2];
    VitesseGenerateur = ADC[3];
    TensionMoteur = ADC[4];
    TensionGenerateur = ADC[5];
    Current = ADC[6];
    FreqMoteur = PWM[0];
    FreqGenerateur = PWM[1];
    PWMMoteur = PWM[2];
    PWMGenerateur = PWM[3];
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
  Serial.println("Display started");
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