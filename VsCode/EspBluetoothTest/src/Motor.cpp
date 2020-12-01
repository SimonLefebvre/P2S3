#include "Motor.h"

Motor::Motor()
{
    Frequency = 100000;
    Duty = 0;

    ledcAttachPin(16,0);
    ledcSetup(0,Frequency,8);
    ledcWrite(0,Duty);

    pid = new PID(0.1, MAX_SPEED, MIN_SPEED, 10, 0, 0);
}

Motor::~Motor() 
{
    delete pid;
}

bool Motor::setSpeed(float s)
{
    if( s<MIN_SPEED || s>MAX_SPEED )
    {
        return false;
    }

    Speed = s;

    return true;
}

void Motor::calibrateSpeed(void)
{
    Duty = (pid->calculate(Speed, readSpeed())/MAX_SPEED)*100;
    setDuty(Duty);
}

bool Motor::setDuty(float d)
{
 
    ledcWrite(0,d*255);

    return true;
}

const float Motor::readSpeed()
{

    float reading = analogRead(26);
    //Serial.print("\tADCd:");
    //Serial.print(reading);
    reading = reading*0.018;
    //Serial.print("\tADCa:");
    //Serial.print(reading);//*0.0142857);//0.011550671*1.2);
    reading = reading*333.3333;    
    return (float)reading;//analogRead(26)*(15767/4095)*1.3;
}

const float Motor::readVout()
{
    return (float)analogRead(36)*44/6824;
}

const float Motor::readTemperature()
{
    return (float)analogRead(25)*20/819;
}