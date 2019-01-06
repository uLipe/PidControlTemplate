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

/**
 * @brief Initilizes the integrator block 
 * @param self integrator to be initialized
 * @param settings structure contaninng self settings
 * @return 0 on success, otherwise -1
 */
static inline int TrapezoidalIntegratorInit(TrapezoidalIntegrator *self, 
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

/**
 * @brief perform integration based on new value
 * @param self integrator block
 * @param new_value net containing the data to integrate
 * @return current integrated value, 0 on enrror
 */
static inline float Integrate(TrapezoidalIntegrator *self, float new_value) {
    if(!self)
        return 0.0f;

    //The integration process uses the trapezoidal rule
    //a second order integration method.    
    self->xn[0] = new_value;
    self->yn[0] = self->yn[1] + 
                  self->xn[0] +
                  self->xn[1];
    
    //perform saturation ensuring the integrator
    //will not explode
    if(self->yn[0] > self->saturation_value)
        self->yn[0] = self->saturation_value;
    else if (self->yn[0] < -self->saturation_value)
        self->yn[0] = -self->saturation_value;

    //Trapezoidal rule takes a IIR filter form, sp
    //the history needs to be updated each call
    self->yn[1] = self->yn[0];
    self->xn[1] = self->xn[0];
    return self->yn[0];
}

#endif