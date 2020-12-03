#include "Generator.h"

Generator::Generator()
{
    Frequency = 100000;
    Duty = 0;

    ledcAttachPin(13,1);
    ledcSetup(1,Frequency,8);
    ledcWrite(1,Duty);

    pid = new PID(0.01, MAX_CURRENT, MIN_CURRENT, 10, 0, 0);
}

Generator::~Generator() 
{

}

bool Generator::setCurrent(float c)
{
    if( c<MIN_CURRENT || c>MAX_CURRENT )
    {
        return false;
    }

    Current = c;

    return true;
}

void Generator::calibrateCurrent(void)
{
    Duty = (pid->calculate(Current, readCurrent())/MAX_CURRENT)*100;
    setDuty(Duty);
}

bool Generator::setDuty(float d)
{
    
    ledcWrite(1,d*255);

    return true;
}

const float Generator::readCurrent()
{
    float adc = (float) analogRead(2);
    //Serial.print(adc);
    return (float)adc*(3.3f/4096.0f)/(0.022 * 120);
}

const float Generator::readSpeed()
{
       float reading = analogRead(12);
    //Serial.print("\tADCd:");
    //Serial.print(reading);
    reading = reading*0.018;
    //Serial.print("\tADCa:");
    //Serial.print(reading);//*0.0142857);//0.011550671*1.2);
    reading = reading*333.3333;    
    return (float)reading;//analogRead(26)*(15767/4095)*1.3;
}

const float Generator::readVout()
{
    return (float)analogRead(15)*88/6825;
}

const float Generator::readTemperature()
{
    return (float)analogRead(13)*20/819;
}