# CCP Documentation

## **Function: enablePWM**

**Precondition:**
- None

**Postcondition:**
- The PWM (Pulse Width Modulation) module is enabled for operation.

**Synopsis:**
```c
#include <CCP.h>

void enablePWM(void);
```

**Description:**
- This function configures and enables the PWM module by setting the relevant bits in the CCP3CON register.
- The function sets the bits CCP3M0, CCP3M1, CCP3M2, and CCP3M3 in CCP3CON to enable PWM mode. Specifically, the bits are set as follows:
    - CCP3M0 = 0
    - CCP3M1 = 0
    - CCP3M2 = 1
    - CCP3M3 = 1

**Return value:**
- This function does not return a value.