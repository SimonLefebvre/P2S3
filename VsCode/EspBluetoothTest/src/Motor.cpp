#include "Motor.h"

Motor::Motor()
{
    Frequency = 100000;
    Duty = 0;

    ledcAttachPin(16,0);
    ledcSetup(0,Frequency,8);
    ledcWrite(0,Duty);

    pid = new PID(0.01, MAX_SPEED, MIN_SPEED, 10, 0, 0);
}

Motor::~Motor() 
{

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
    if( MIN_DUTY<0 || MAX_DUTY>100 )
    {
        return false;
    }

    Duty = d/100;
    ledcWrite(0,Duty);

    return true;
}

const float Motor::readSpeed()
{
    return (float)analogRead(26)*15767/4095;
}

const float Motor::readVout()
{
    return (float)analogRead(36)*44/6824;
}

const float Motor::readTemperature()
{
    return (float)analogRead(25)*20/819;
}