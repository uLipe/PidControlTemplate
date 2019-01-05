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

/**
 * @brief initiliaze Pid controller based on 2p2z approach
 * @param self 2p2z pid controller object
 * @param settings pid controllers initial settings
 * @return 0 on success, otherwise -1
 */ 
int PidControlller2p2zInit(Pid2p2z *self, PidControllerSettings *settings);


/**
 * @brief gets the controller interface to use its common methods
 * @param self 2p2z pid controller object
 * @return returns the interface of pid object, NULL on error
 */ 
static inline PidControllerInterface *PidController2p2zGetInterface(Pid2p2z *self) {
    if(self) {
        return &self->interface;
    } else {
        return NULL;
    }
}
#endif