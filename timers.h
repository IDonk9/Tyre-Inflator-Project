#include <xc.h>
#include "config.h"

// Initializes timer 0 so that it will
// cause an interruption in 100 ms.
void initTMR0(void);

// Initializes timer 2 so that it will
// count to 100 in 800 us (best to
// use it with the CCP for the duty
// cycle).
void initTMR2(void);