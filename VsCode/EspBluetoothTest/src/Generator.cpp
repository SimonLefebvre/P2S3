#include "Generator.h"

Generator::Generator()
{
    Frequency = 100000;
    Duty = 0;

    ledcAttachPin(14,1);
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
    Duty = (pid->calculate(Speed, readCurrent())/MAX_CURRENT)*100;
    setDuty(Duty);
}

bool Generator::setDuty(float d)
{
    
    ledcWrite(1,d*255);

    return true;
}

const float Generator::readCurrent()
{
    return (float)analogRead(2)/3276;
}

const float Generator::readSpeed()
{
    return (float)analogRead(12)*15767/4095;
}

const float Generator::readVout()
{
    return (float)analogRead(15)*88/6825;
}

const float Generator::readTemperature()
{
    return (float)analogRead(13)*20/819;
}