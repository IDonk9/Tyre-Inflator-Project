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

## **Function: disablePWM**

**Precondition:**
- None

**Postcondition:**
- The PWM (Pulse Width Modulation) module is disabled.

**Synopsis:**
```c
#include <CCP.h>

void disablePWM(void);
```

**Description:**
- This function disables the PWM module by clearing the relevant bits in the CCP3CON register.
- The function clears the bits CCP3M0, CCP3M1, CCP3M2, and CCP3M3 in CCP3CON to stop PWM operation. Specifically, the bits are cleared as follows:
    - CCP3M0 = 0
    - CCP3M1 = 0
    - CCP3M2 = 0
    - CCP3M3 = 0

**Return value:**
- This function does not return a value.

## **Function: initPWM**

**Precondition:**
- None

**Postcondition:**
- The PWM module is initialized with a 0% duty cycle and is disabled initially.

**Synopsis:**
```c
#include <CCP.h>

void initPWM(void);
```

**Description:**
- This function initializes the PWM module by configuring several registers.
- First, it selects Timer2 (TMR2) as the source for the PWM signal by clearing the CCPTMRS0bits.C3TSEL0 and CCPTMRS0bits.C3TSEL1 bits.
- The duty cycle is initially set to 0%, by setting CCP3CONbits.DC3B0 and CCP3CONbits.DC3B1 to 0 (no "decimal bits").
- The function then disables the PWM module by calling disablePWM() to ensure the PWM is not active immediately.

**Return value:**
- This function does not return a value.

## **Function: setDutyCycleFromPSI**

**Precondition:**
- The PWM module must be initialized before calling this function.

**Postcondition:**
- The PWM duty cycle is updated based on the provided PSI value.

**Synopsis:**
```c
#include <CCP.h>

void setDutyCycleFromPSI(byte psi);
```

**Description:**
- This function sets the PWM duty cycle based on the PSI (Pressure Sensor Input) value.
- The function checks the PSI value and sets the CCPR3 register to a corresponding duty cycle value:
    - If psi is less than or equal to 30, the duty cycle is set to 40.
    - If psi is less than or equal to 60, the duty cycle is set to 80.
    - If psi is greater than 60, the duty cycle is set to 95.
- The CCPR3 register is used to control the duty cycle, as the PWM signal is based on Timer2, which counts up to 100.

**Return value:**
- This function does not return a value.