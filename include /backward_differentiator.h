#ifndef __BACKWARD_DIFFERENTIATOR_H
#define __BACKWARD_DIFFERENTIATOR_H

typedef struct {
    float xn[2];
}BackDifferentiator;

/**
 * @brief initialize the differentiator blocK 
 * @param self target object to be initialized
 * @return 0 on success otherwise -1 
 */
static inline int BackDifferentiatorInit(BackDifferentiator *self) {
    if(!self)
        return -1;

    self->xn[0] = 0.0f;
    self->xn[1] = 0.0f;

    return 0;
}

/**
 * @brief update the derivative caculation based on input value
 * @param self the differentiator block
 * @param new_value new incoming value
 * @return current derivative value, 0 on error
 */
static inline float Differentiate(BackDifferentiator *self, float new_value) {
    if(!self)
        return 0.0f;

    self->xn[0] = new_value;
    float delta = self->xn[1] - self->xn[0];
    self->xn[1] = self->xn[0];
    return (delta);
}

#endif