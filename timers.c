#include "timers.h"

void initTMR0(void)
{
   // Indicates that the interrupt occurs when a 16-bit overflow occurs.
   T0CONbits.T08BIT = 0;
   
   // Indicates that Fosc/4 is taken as the clock.
   T0CONbits.T0CS = 0;
   
   // Indicates that it will be incremented when there is a rising edge.
   T0CONbits.T0SE = 1;
   
   // Indicates that it is prescaled.
   T0CONbits.PSA = 0;
   
   // The following bits indicate that the prescaling is 1:4.
   T0CONbits.T0PS2 = 0;
   T0CONbits.T0PS1 = 0;
   T0CONbits.T0PS0 = 1;
   
   // The following registers are initialized to start counting from 15536.
   TMR0H = (unsigned short)15536 >> 8;
   TMR0L = 15536;
   
   // Indicates that the count should begin.
   T0CONbits.TMR0ON = 1;
   
   // Enable interruptions.
   GIE = 1;
   TMR0IE = 1;
}

// PR2 has a good value to represent
// the duty cycle easily as a percentage.
#define PR2_COUNT 100
void initTMR2(void)
{
   // Select 1:16 PreScaler.
   T2CKPS0 = 0;
   T2CKPS1 = 1;
   
   // Select 1:16 PostScaler.
   T2OUTPS0 = 1;
   T2OUTPS1 = 1;
   T2OUTPS2 = 1;
   T2OUTPS3 = 1;
   
   // For PWM period of 800 us (TMR2 has period 8 microseconds).
   TMR2 = 0;
   PR2 = PR2_COUNT;
   
   // Disable TMR2 interrupts.
   TMR2IE = 0;
   
   // Start counting.
   TMR2ON = 1;
}