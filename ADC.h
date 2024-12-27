#include <xc.h>
#include "config.h"

//Initializes ADC such that
//the result is right justified
//A/D conversion clock is Fosc/8
//A/D acquisition time is 8*TAD
void initADC(void);

//Selects AN6 as analog channel
//enables ADC
//returns converted value
unsigned short getAN6(void);

//Selects AN7 as analog channel
//enables ADC
//returns converted value
unsigned short getAN7(void);