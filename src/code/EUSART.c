#include "EUSART.h"

void initEUSART(void)
{
   // Baudcon.
   // Select the whole 16 bits.
   BAUDCON1bits.BRG16 = 1;
   // Precalculated baud rate.
   // Taking into account the rest
   // of the configuration, the
   // comunication will be done
   // at ~155.2 kBd.
   SPBRG1 = 16;
   // Transmit.
   // Enables transmission.
   TXSTA1bits.TXEN = 1;
   // Asyncronous mode.
   TXSTA1bits.SYNC = 0;
   // Use high baud rate.
   TXSTA1bits.BRGH = 1;
   // Receive.
   // Configure pins as serial.
   RCSTA1bits.SPEN = 1;
   // Clear flag and enable interruption
   // for reception.
   RC1IF = 0;
   RC1IE = 1;
   PEIE = 1;
   GIE = 1;
   // Enable reception.
   RCSTA1bits.CREN = 1;
   // Raise flag so that no busy wait
   // is done since there are no pending
   // transmissions.
   PIR1bits.TXIF = 1;
}

void transmitAsyncEUSART(const char* message)
{
   // Will transmit all characters except
   // for the null termination.
   while (*message) {
      // Busy wait for the character that
      // was being sent before the function
      // call (if none, PIR1bits.TXIF should
      // be 1 by precondition).
      while (!PIR1bits.TXIF);
      // Clear the flag becasue there is a
      // transmission about to start that
      // should be awaited.
      PIR1bits.TXIF = 0;
      // Start transmission and advance.
      TXREG1 = *(message++);
   }
}

byte receptionError(void)
{
   return RCSTA1bits.FERR || RCSTA1bits.OERR;
}

void clearFIFO(void)
{
   char trash;
   for (byte i = 0; i < 3; ++i) {
      trash = RCREG1;
   }
}

void receptionErrorRecovery(void)
{
   // Clear FIFO, since there will be
   // invalid data (with both, framing
   // error and overrun error, but
   // specially with the framing error).
   clearFIFO();
   // If there was a framing error, the
   // flag has been cleared.
   // If there is an overrun error, the
   // flag has to be manually cleared
   // in an indirect manner.
   if (RCSTA1bits.OERR) {
      RCSTA1bits.CREN = 0;
      RCSTA1bits.CREN = 1;
   }
}