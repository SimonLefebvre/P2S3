#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <Arduino.h>
#include "pid.h"

#define MAX_SPEED 3500
#define MIN_SPEED 0
#define MAX_DUTY 100
#define MIN_DUTY 0

class Motor
{
    public:

        Motor();
        ~Motor();

        // s - Speed from MIN_SPEED to MAX_SPEED
        bool setSpeed(float s);

        // d - Duty from MIN_DUTY to MAX_DUTY
        bool setDuty(float d);
        
        void calibrateSpeed(void);

        const float readSpeed();
        const float readVout();
        const float readTemperature();

    private:

        int Frequency;
        float Duty;
        float Speed;
        float Vout;

        PID *pid;
};

#endif
