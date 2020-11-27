#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <Arduino.h>
#include "pid.h"

#define MAX_DUTY 100
#define MIN_DUTY 0
#define MAX_CURRENT 1
#define MIN_CURRENT 0

class Generator
{
    public:

        Generator();
        ~Generator();

        // c - Current from MIN_CURRENT to MAX_CURRENT
        bool setCurrent(float c);
        void calibrateCurrent(void);

        const float readCurrent();
        const float readSpeed();
        const float readVout();
        const float readTemperature();

    private:

        int Frequency;
        float Duty;
        float Speed;
        float Vout;
        float Current;

        PID *pid;

        // d - Duty from MIN_DUTY to MAX_DUTY
        bool setDuty(float d);
};

#endif
