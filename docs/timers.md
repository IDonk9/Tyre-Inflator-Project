# Timers Documentation

## **Function: initTMR0**

**Precondition:**
- None

**Postcondition:**
- Timer0 is initialized and begins counting with interrupts enabled.

**Synopsis:**
```c
#include "timers.h"

void initTMR0(void);
```

**Description:**
- Configures Timer0 for 16-bit mode with a clock source of Fosc/4.
- Sets increment on a rising edge and enables a prescaler with a ratio of 1:4.
- Initializes the timer to start counting from 15536 (100 ms) and enables counting and interrupts.

**Return value:**
- This function does not return a value.

## **Function: initTMR2**

**Precondition:**
- None

**Postcondition:**
- Timer2 is initialized and starts counting with the configured prescaler and postscaler.

**Synopsis:**
```c
#include "timers.h"

void initTMR2(void);
```

**Description:**
- Initializes Timer2 to work with PWM by:
    - Configuring Timer2 with a 1:16 prescaler for input clock division and a 1:16 postscaler for output clock division.
    - Setting a PWM period of 800 µs by initializing PR2 to 100 and TMR2 to 0.
    - Disabling Timer2 interrupts and starts the timer.

**Return value:**
- This function does not return a value.