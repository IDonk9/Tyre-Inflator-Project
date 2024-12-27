# ADC Module Documentation

## **Function: initADC**

**Precondition:**
- None

**Postcondition:**
- The ADC module is initialized and ready to perform analog-to-digital conversions.

**Synopsis:**
```c
#include "ADC.h"

void initADC(void);
```

**Description:**
- This function configures the ADC module for conversions. It sets the result to be right-justified, the conversion clock to Fosc/8, and the acquisition time to 8*TAD.

**Return value:**
- This function does not return a value.

## **Function: getAN6**

**Precondition:**
- The ADC module should be initialized before calling this function.

**Postcondition:**
- The function returns the 10-bit result of the A/D conversion of analog channel AN6.

**Synopsis:**
```c
#include "ADC.h"

unsigned short getAN6(void);
```
**Description:**
- This function performs an A/D conversion on analog channel AN6 and returns the 10-bit result by combining the high and low bytes of the conversion result.

**Return value:**
- Returns a 10-bit unsigned integer (the result of the A/D conversion on AN6).

## **Function: getAN7**

**Precondition:**
- The ADC module should be initialized before calling this function.

**Postcondition:**
- The function returns the 10-bit result of the A/D conversion of analog channel AN7.

**Synopsis:**
```c
#include "ADC.h"

unsigned short getAN7(void);
```
**Description:**
- This function performs an A/D conversion on analog channel AN7 and returns the 10-bit result by combining the high and low bytes of the conversion result.

**Return value:**
- Returns a 10-bit unsigned integer (the result of the A/D conversion on AN7).
