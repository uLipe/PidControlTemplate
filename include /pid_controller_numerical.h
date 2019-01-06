#ifndef __PID_CONTROLLER_NUMERICAL_H
#define __PID_CONTROLLER_NUMERICAL_H

#include <pid_controller_interface.h>
#include <trapezoidal_Integrator.h>
#include <backward_differentiator.h>

typedef struct {
    TrapezoidalIntegrator integrator;
    BackDifferentiator differ;
    float kp;
    float ki;
    float kd;
    PidControllerInterface interface;
}PidNumerical;

/**
 * @brief initiliaze Pid controller based on numerical approach
 * @param self numerical pid controller object
 * @param settings pid controllers initial settings
 * @return 0 on success, otherwise -1
 */ 
int PidControlllerNumericalInit(PidNumerical *self, PidControllerSettings *settings);

/**
 * @brief gets the controller interface to use its common methods
 * @param self numericla pid controller object
 * @return returns the interface of pid object, NULL on error
 */ 
static inline PidControllerInterface *PidControllerNumericalGetInterface(PidNumerical *self) {
    if(self) {
        return &self->interface;
    } else {
        return NULL;
    }
}

#endif