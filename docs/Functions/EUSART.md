# EUSART Documentation

## **Function: initEUSART**

**Precondition:**
- None

**Postcondition:**
- EUSART module is initialized for transmission and reception with interrupt handling.

**Synopsis:**
```c
#include "EUSART.h"

void initEUSART(void);
```

**Description:**
- Initializes the EUSART for asynchronous communication at ~155.2 kBd (baud rate set by SPBRG1 = 16).
- Enables transmission, sets asynchronous mode, and configures high baud rate.
- Configures receive pins, enables interrupts for reception, and continuous receive mode.

**Return value:**
- This function does not return a value.

## **Function: transmitAsyncEUSART**

**Precondition:**
- EUSART must be initialized for transmission.

**Postcondition:**
- The specified message is transmitted asynchronously, character by character.

**Synopsis:**
```c
#include "EUSART.h"

void transmitAsyncEUSART(const char* message);
```

**Description:**
- Transmits each character of the message, waiting for the transmit buffer to be ready before sending the next character.
- The function uses the TXIF flag to ensure the transmit register is ready before writing each character to TXREG1.

**Return value:**
- This function does not return a value.

## **Function: receptionError**

**Precondition:**
- EUSART must be initialized for reception.

**Postcondition:**
- Returns a non-zero value if there is a reception error (framing or overrun).

**Synopsis:**
```c
#include "EUSART.h"

byte receptionError(void);
```

**Description:**
- This function checks the FERR (framing error) and OERR (overrun error) flags in the RCSTA1 register to determine if a reception error has occurred.

**Return value:**
- Returns 1 if there is a reception error, otherwise 0.

## **Function: clearFIFO**

**Precondition:**
- EUSART must be initialized for reception.

**Postcondition:**
- Clears any unread data in the receive FIFO buffer.

**Synopsis:**
```c
#include "EUSART.h"

void clearFIFO(void);
```

**Description:**
- This function discards the first 3 characters from the receive buffer by reading from RCREG1, effectively clearing the FIFO.
- The intended use of this function is for error recovery.

**Return value:**
- This function does not return a value.

## **Function: receptionErrorRecovery**

**Precondition:**
- EUSART must be initialized for reception.

**Postcondition:**
- The function clears any reception errors and recovers from them.

**Synopsis:**
```c
#include "EUSART.h"

void receptionErrorRecovery(void);
```

**Description:**
- Clears the receive FIFO buffer to discard invalid data when a reception error occurs.
- If an overrun error (OERR) is detected, it clears and re-enables the continuous receive mode (CREN) to recover from the error.

**Return value:**
- This function does not return a value.