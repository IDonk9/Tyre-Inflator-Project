#include <xc.h>
#include "config.h"

typedef unsigned char byte;

// Enables PWM.
void enablePWM(void);

// Disables PWM.
void disablePWM(void);

// Initializes the CCP3 module
// taking timer 2 and puts it
// in the PWM mode, but disabled.
void initPWM(void);

// Takes the requied psi and sets
// the duty cycle as of the specification.
void setDutyCycleFromPSI(byte psi);