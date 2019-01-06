#include <pid_controller_2p2z.h>

static float update (PidControllerInterface *self, float reference, float measured) {
    if(!self)
        return 0.0f;
    Pid2p2z *pid = PID_CONTAINER_OF(self, Pid2p2z, interface);

    //Run pid filter core like a IIR z TF:
    pid->xn[0] = reference - measured;
    pid->yn[0] = (pid->bn[0] * pid->xn[0]) +
                 (pid->bn[1] * pid->xn[1]) +  
                 (pid->bn[2] * pid->xn[2]) +
                 (-pid->yn[1]);
    
    //Perform windup limit:
    if(pid->yn[0] > pid->windup_limit)
        pid->yn[0] = pid->windup_limit;
    else if (pid->yn[0] < -pid->windup_limit)
        pid->yn[0] = -pid->windup_limit;

    //Update IIR tf history:
    pid->xn[2] = pid->xn[1];
    pid->xn[1] = pid->xn[0];
    pid->yn[1] = pid->yn[0];

    return (pid->yn[0]);
 }

static void tune (PidControllerInterface *self, float kp, float ki, float kd) {
    if(!self)
        return;
    Pid2p2z *pid = PID_CONTAINER_OF(self, Pid2p2z, interface);

    pid->bn[0] = kp + ki + kd; 
    pid->bn[1] = kp + (2.0f * ki);
    pid->bn[2] = kd;
}

static void reset (PidControllerInterface *self) {
    if(!self)
        return;
    Pid2p2z *pid = PID_CONTAINER_OF(self, Pid2p2z, interface);

    pid->xn[0] = 0.0f; 
    pid->xn[1] = 0.0f;
    pid->xn[2] = 0.0f;
    pid->yn[0] = 0.0f;
    pid->yn[1] = 0.0f;    
}

int PidControlller2p2zInit(Pid2p2z *self, PidControllerSettings *settings) {
    if(!self)
        return -1;
    if(!settings)
        return -1;

    self->interface.update = update;
    self->interface.tune = tune;
    self->interface.reset = reset;
    self->windup_limit = settings->windup_limit;
    self->xn[0] = 0.0f; 
    self->xn[1] = 0.0f;
    self->xn[2] = 0.0f;
    self->yn[0] = 0.0f;
    self->yn[1] = 0.0f;

    //Convert PID gains to Z-trans gains:
    self->bn[0] = settings->kp + settings->ki + settings->kd; 
    self->bn[1] = -settings->kp + (2.0f * settings->ki);
    self->bn[2] = settings->kd;
    
    return 0;
}