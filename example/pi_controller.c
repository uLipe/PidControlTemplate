/**
 *  Simple PI Controller example 
 */ 
#include <pid_controller_numerical.h>
#include <pid_controller_2p2z.h>
#include <pid_controller_interface.h>
#include <unistd.h>
#include <signal.h>

//PI controller sampled at 1us
#define SAMPLE_RATE_US 1000
#define P_GAIN         10.0f
#define I_GAIN         (0.1f * (1.0f / (float) SAMPLE_RATE_US))

static PidNumerical pi;
static PidControllerSettings settings;
static int should_run = 1;

static void SignalHandler(int signo) {
    (void)signo;
    should_run = 0;
}

static float StateEstimator(void) {
   //Add your 
   return 0.0f;
}

static void Act(float command) {
    (void)command;
    //TODO: add your actuation code here
}

int main (int argc, char *argv[]) {
    //On PI controllers there is no derivative gain.
    settings.kd = 0.0f;
    settings.kp = P_GAIN;
    settings.ki = I_GAIN;
    settings.windup_limit = 1000.0f;

    signal(SIGINT, SignalHandler);

    //FIRST: Initialize PID object with desired settings:
    PidControlllerNumericalInit(&pi, &settings);

    //SECOND: Get controller interface to use its common methods.
    //        From now we will use only the interface  
    PidControllerInterface *itf = PidControllerNumericalGetInterface(&pi); 

    float dummy_reference = 1.0f;

    //Simulate a closed loop control:
    while(should_run) {
        //THIRD MEasure sensors and compute controller:
        float command = itf->update(itf, dummy_reference, StateEstimator ());

        //OPTIONAL: reset or tune PID in runtime:
        // itf->tune(itf, new_kp, new_ki, new_kd);
        // itf->reset(itf);

        //FOURTH: Update + scale command to your actuator:
        Act(command);
        usleep(SAMPLE_RATE_US);
    }

    return 0;
}