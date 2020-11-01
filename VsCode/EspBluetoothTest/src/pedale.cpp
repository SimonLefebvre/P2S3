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
    TensionGenerateur = ADC[4];
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
  display.drawStringMaxWidth(0, 0, 128,"U Moteur 24V" );
  display.drawStringMaxWidth(0, 16, 128,"U Gene 80V" );
  display.drawStringMaxWidth(0, 32, 128,"T Moteur 20C" );
  display.drawStringMaxWidth(0, 48, 128,"T Gene 80C" );
  display.display();
  Serial.println("Display started");
}
Display::Display(int mode, myValues* Values)
{
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);



  switch(mode)
  {
      case 0:
        display.drawStringMaxWidth(0, 0, 128,"U Moteur "+String(Values->TensionMoteur)+"V" );
        display.drawStringMaxWidth(0, 16, 128,"U Gene "+String(Values->TensionGenerateur)+"V" );
        display.drawStringMaxWidth(0, 32, 128,"T Moteur "+String(Values->TempMoteur)+"C" );
        display.drawStringMaxWidth(0, 48, 128,"T Gene "+String(Values->TempGenerateur)+"C" );
break;
      case 1:
        display.drawStringMaxWidth(0, 0, 128,"S Moteur "+String(Values->VitesseMoteur)+"R" );
        display.drawStringMaxWidth(0, 16, 128,"U Moteur "+String(Values->TensionMoteur)+"V" );
        display.drawStringMaxWidth(0, 32, 128,"P Moteur "+String(Values->PWMMoteur)+"%" );
        display.drawStringMaxWidth(0, 48, 128,"F Moteur "+String(Values->FreqMoteur)+"Hz" );
break;
      case 2:
        display.drawStringMaxWidth(0, 0, 128,"S Gene "+String(Values->VitesseGenerateur)+"R" );
        display.drawStringMaxWidth(0, 16, 128,"U Gene "+String(Values->TensionGenerateur)+"V" );
        display.drawStringMaxWidth(0, 32, 128,"P Gene "+String(Values->PWMGenerateur)+"%" );
        display.drawStringMaxWidth(0, 48, 128,"F Gene "+String(Values->FreqGenerateur)+"Hz" );
  }
  
  display.display();
  Serial.println("Display started");
}
void Display::Update(int mode, myValues* Values)
{
    display.resetDisplay();

  switch(mode)
  {
      case 0:
        display.drawStringMaxWidth(0, 0, 128,"U Moteur "+String(Values->TensionMoteur)+"V" );
        display.drawStringMaxWidth(0, 16, 128,"U Gene "+String(Values->TensionGenerateur)+"V" );
        display.drawStringMaxWidth(0, 32, 128,"T Moteur "+String(Values->TempMoteur)+"C" );
        display.drawStringMaxWidth(0, 48, 128,"T Gene "+String(Values->TempGenerateur)+"C" );
break;
      case 1:
        display.drawStringMaxWidth(0, 0, 128,"S Moteur "+String(Values->VitesseMoteur)+"R" );
        display.drawStringMaxWidth(0, 16, 128,"U Moteur "+String(Values->TensionMoteur)+"V" );
        display.drawStringMaxWidth(0, 32, 128,"P Moteur "+String(Values->PWMMoteur)+"%" );
        display.drawStringMaxWidth(0, 48, 128,"F Moteur "+String(Values->FreqMoteur)+"Hz" );
break;
      case 2:
        display.drawStringMaxWidth(0, 0, 128,"S Gene "+String(Values->VitesseGenerateur)+"R" );
        display.drawStringMaxWidth(0, 16, 128,"U Gene "+String(Values->TensionGenerateur)+"V" );
        display.drawStringMaxWidth(0, 32, 128,"P Gene "+String(Values->PWMGenerateur)+"%" );
        display.drawStringMaxWidth(0, 48, 128,"F Gene "+String(Values->FreqGenerateur)+"Hz" );
  }
  
  display.display();
}