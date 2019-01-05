#ifndef __PID_CONTROLLER_INTERFACE_H
#define __PID_CONTROLLER_INTERFACE_H
#include <PidMacros.h>

/** Generic pid controller interface allowing multiple implementations **/
typedef struct {
    void (*update) (PidControllerInterface *self, float reference, float measured);
    void (*tune) (PidControllerInterface *self, float kp, float ki, float kd);
} PidControllerInterface;

#endif
