#include "pid_controller_numerical.h"

static float update (PidControllerInterface *self, float reference, float measured) {
    if(!self)
        return 0.0f;
        
    PidNumerical *pid = PID_CONTAINER_OF(self, PidNumerical, interface);
    float error = reference - measured;
    float command = (pid->kp * error) +
                    (pid->ki * Integrate(&pid->integrator, error)) +
                    (pid->kd * Differentiate(&pid->differ, error));

    return (command);
}

static void tune (PidControllerInterface *self, float kp, float ki, float kd) {
    if(!self)
        return;
    PidNumerical *pid = PID_CONTAINER_OF(self, PidNumerical, interface);
    
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

static void reset (PidControllerInterface *self) {
    //Nothing to implement yet.
    return;
}

int PidControlllerNumericalInit(PidNumerical *self, PidControllerSettings *settings) {
     if(!self)
        return -1;
    if(!settings)
        return -1;

    self->interface.update = update;
    self->interface.tune = tune;
    self->interface.reset = reset;
    self->kp = settings->kp;
    self->ki = settings->ki;
    self->kd = settings->kd;
    TrapezoidalIntegratorInit(&self->integrator, &(IntegratorSettings){settings->windup_limit});
    BackDifferentiatorInit(&self->differ);    
    return 0;
}