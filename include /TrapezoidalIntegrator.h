#ifndef __TRAPEZOIDAL_INTEGRATOR_H
#define __TRAPEZOIDAL_INTEGRATOR_H

typedef struct {
    float xn[2];
    float yn[2];
    float saturation_value;
}TrapezoidalIntegrator;

typedef struct {
    float saturation_value;
} IntegratorSettings;

static inline int TrapezoidalIntegratorInit(TrapezoildalIntegrator *self, 
                                            IntegratorSettings *settings) {
    if(!self) 
        return -1;
    
    if(!settings)
        return -1;
    
    self->xn[0] = 0.0f;
    self->xn[1] = 0.0f;
    self->yn[0] = 0.0f;
    self->yn[1] = 0.0f;    
    self->saturation_value = settings->saturation_value;
    return 0;
}


static inline float Integrate(TrapezoildalIntegrator *self, float new_value) {
    if(!self)
        return 0.0f;
    
    self->xn[0] = new_value;
    self->yn[0] = self->yn[1] + 
                  self->xn[0] +
                  self->xn[1];
    
    if(self->yn[0] > self->saturation_value)
        self->yn[0] = self->saturation_value;
    else if (self->yn[0] < -self->saturation_value)
        self->yn[0] = -self->saturation_value;

    self->yn[1] = self->yn[0];
    self->xn[1] = self->xn[0];

    return self->yn[0];
}

#endif