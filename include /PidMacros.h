#ifndef __PID_MACROS_H
#define __PID_MACROS_H

#define PID_CONTAINER_OF(ptr, type, field)  \
((type *)(((char *)(ptr)) - offsetof(type, field))) \

#endif