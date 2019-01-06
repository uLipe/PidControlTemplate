#ifndef __PID_MACROS_H
#define __PID_MACROS_H

#include <stddef.h> //offsetof

/**
 * This macro is used to extract common interface from 
 * specific object that implements it
 */
#define PID_CONTAINER_OF(ptr, type, field)  ((type *)(((char *)(ptr)) - offsetof(type, field))) 

#endif