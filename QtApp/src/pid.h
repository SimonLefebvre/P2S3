//
// Created by Xavier on 11/21/2020.
//

#ifndef PID_H
#define PID_H


class PIDController {
public:
    PIDController();

    float update(float setpoint, float measurement);

private:
    float Kp;
    float Ki;
    float Kd;

    float tau;

    float limMin;
    float limMax;

    float dt;

    float integral;
    float prevError;
    float differential;
    float prevMeasurement;

    float output;
};


#endif //PID_H
