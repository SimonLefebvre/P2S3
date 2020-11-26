//
// Created by Xavier on 11/21/2020.
//

#include "pid.h"

PIDController::PIDController() :
        integral(0.0f),
        differential(0.0f),
        prevError(0.0f),
        prevMeasurement(0.0f)
{

}

float PIDController::update(float setpoint, float measurement)
{
    return 0.0f;
}