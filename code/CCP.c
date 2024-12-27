#include "CCP.h"

void enablePWM(void)
{
   // Activate PWM.
   CCP3CONbits.CCP3M0 = 0;
   CCP3CONbits.CCP3M1 = 0;
   CCP3CONbits.CCP3M2 = 1;
   CCP3CONbits.CCP3M3 = 1;
}

void disablePWM(void)
{
   // Stop PWM.
   CCP3CONbits.CCP3M0 = 0;
   CCP3CONbits.CCP3M1 = 0;
   CCP3CONbits.CCP3M2 = 0;
   CCP3CONbits.CCP3M3 = 0;
}

void initPWM(void)
{
   // Select TMR2.
   CCPTMRS0bits.C3TSEL0 = 0;
   CCPTMRS0bits.C3TSEL1 = 0;
   
   // Start with 0% duty cycle.
   CCPR3 = 0;
   // Using no "decimal bits".
   CCP3CONbits.DC3B0 = 0;
   CCP3CONbits.DC3B1 = 0;
   
   // Disable PWM for now.
   disablePWM();
}

void setDutyCycleFromPSI(byte psi)
{
   // As of the specification.
   // Note that the value that we put
   // into CCP3 is the percentage itself
   // since TMR2 counts up to 100.
   if (psi <= 30) {
      CCPR3 = 40;
   } else if (psi <= 60) {
      CCPR3 = 80;
   } else {
      CCPR3 = 95;
   }
}