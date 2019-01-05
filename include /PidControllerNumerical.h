#ifndef __PID_CONTROLLER_NUMERICAL_H
#define __PID_CONTROLLER_NUMERICAL_H

#include <PidControllerInterface.h>
#include <TrapezoidalIntegrator.h>
#include <BackwardDifferentiator.h>

typedef struct {
    TrapezoidalIntegrator integrator;
    BackDifferentiator differ;
    float kp;
    float ki;
    float kd;
    PidControllerInterface interface;
}PidNumerical;

int PidControlllerNumericalInit(PidNumerical *self, PidControllerSettings *settings);
PidControllerInterface *PidControllerNumericalGetInterface(PidNumerical *self);

#endif