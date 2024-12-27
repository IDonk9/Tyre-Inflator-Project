#include <xc.h>
#include "config.h"

typedef unsigned char byte;

// Initializes the EUSART module so that it
// can make asyncronuos transmission using
// USART1 at ~155.2 kBd using busy wait and
// reception using USART1 by interruption.
void initEUSART(void);

// Using USART1, it will transmit all the
// characters that the null-terminated
// string contains (except for  the null
// termination) at ~155.2 kBd in asyncronous
// mode. Note that it does a busy wait for
// the character that was being sent before
// the function call, but it will not do the
// busy wait for the last character of this
// string. Initialization prior to this
// function call is required.
void transmitAsyncEUSART(const char* message);

// Returns 1 if there are errors in the
// receive FIFO of USART1, 0 otherwise.
byte receptionError(void);

// Clears the receive FIFO of USART1,
// thought for error recovery.
void clearFIFO(void);

// Recovers from errors in the reception
// form USART1 by clearing the FIFO and
// the error flags.
void receptionErrorRecovery(void);