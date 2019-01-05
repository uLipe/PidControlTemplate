#ifndef __PID_CONTROLLER_2P2Z_H
#define __PID_CONTROLLER_2P2Z_H

#include <PidControllerInterface.h>

typedef struct {
    float bn[3];
    float xn[3];
    float yn[2];
    float windup_limit;
    PidControllerInterface interface;
}Pid2p2z;

int PidControlller2p2zInit(Pid2p2z *self, PidControllerSettings *settings);
PidControllerInterface *PidController2p2zGetInterface(Pid2p2z *self);

#endif