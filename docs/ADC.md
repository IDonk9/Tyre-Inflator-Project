## ADC Module Documentation

### **Function: initADC**

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
