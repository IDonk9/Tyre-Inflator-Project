# CCP Documentation

## **Function: enablePWM**

**Precondition:**
- None

**Postcondition:**
- The PWM (Pulse Width Modulation) module is enabled for operation.

**Synopsis:**
```c
#include "CCP.h"

void enablePWM(void);
```

**Description:**
- This function enables the PWM module by setting the appropriate control bits for PWM mode.

**Return value:**
- This function does not return a value.

## **Function: disablePWM**

**Precondition:**
- None

**Postcondition:**
- The PWM (Pulse Width Modulation) module is disabled.

**Synopsis:**
```c
#include "CCP.h"

void disablePWM(void);
```

**Description:**
- This function disables the PWM module by clearing the control bits for PWM mode.

**Return value:**
- This function does not return a value.

## **Function: initPWM**

**Precondition:**
- None

**Postcondition:**
- The PWM module is initialized with a 0% duty cycle and is disabled initially.

**Synopsis:**
```c
#include "CCP.h"

void initPWM(void);
```

**Description:**
- This function initializes the PWM module, sets the duty cycle to 0%, and disables the PWM.

**Return value:**
- This function does not return a value.

## **Function: setDutyCycleFromPSI**

**Precondition:**
- The PWM module must be initialized before calling this function.

**Postcondition:**
- The PWM duty cycle is updated based on the provided PSI value.

**Synopsis:**
```c
#include "CCP.h"

void setDutyCycleFromPSI(byte psi);
```

**Description:**
- This function sets the PWM duty cycle based on the PSI value, adjusting the duty cycle to predefined values for different ranges of PSI.
    - If psi is less than or equal to 30, the duty cycle is set to 40.
    - If psi is less than or equal to 60, the duty cycle is set to 80.
    - If psi is greater than 60, the duty cycle is set to 95.

**Return value:**
- This function does not return a value.