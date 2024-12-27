# ADC Module Documentation

## **Function: initADC**

**Precondition:**
- None

**Postcondition:**
- The ADC module is initialized and ready to perform analog-to-digital conversions.

**Synopsis:**
```c
#include <ADC.h>

void initADC(void);
```

**Description:**
- A call to initADC configures the ADC module such that:
  - The result is right justified
  - A/D conversion clock is Fosc/8
  - A/D acquisition time is 8*TAD

**Return value:**
- This function does not return a value.

## **Function: getAN6**

**Precondition:**
- The ADC module should be initialized before calling this function.

**Postcondition:**
- The function returns the 10-bit result of the A/D conversion of analog channel AN6.

**Synopsis:**
```c
#include <ADC.h>

unsigned short getAN6(void);
```
**Description:**
- This function performs an analog-to-digital conversion on the analog input channel AN6 and returns the 10-bit result.
  - It first selects AN6 by setting ADCON0 to 0x1B.
  - Then it waits for the A/D conversion to complete by checking the GO flag.
  - After the conversion, the function combines the high (ADRESH) and low (ADRESL) result bytes to form a 10-bit value, which is then returned.

**Return value:**
- Returns a 10-bit unsigned integer (the result of the A/D conversion on AN6).

## **Function: getAN7**

**Precondition:**
- The ADC module should be initialized before calling this function.

**Postcondition:**
- The function returns the 10-bit result of the A/D conversion of analog channel AN7.

**Synopsis:**
```c
#include <ADC.h>

unsigned short getAN7(void);
```
**Description:**
- This function performs an analog-to-digital conversion on the analog input channel AN7 and returns the 10-bit result.
  - It first selects AN7 by setting ADCON0 to 0x1F.
  - Then it waits for the A/D conversion to complete by checking the GO flag.
  - After the conversion, the function combines the high (ADRESH) and low (ADRESL) result bytes to form a 10-bit value, which is then returned.

**Return value:**
- Returns a 10-bit unsigned integer (the result of the A/D conversion on AN7).
