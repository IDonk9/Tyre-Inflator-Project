#include "ADC.h"

void initADC(void)
{
   ADON = 1;
   ADCON1 = 0x00;
   ADCON2 = 0xA1;
}

unsigned short getAN6(void)
{
   // Selects AN6.
   ADCON0 = 0x1B;
   while (GO);
   unsigned short high = ADRESH;
   return (high << 8) | ADRESL;
}

unsigned short getAN7(void)
{
   // Selects AN7.
   ADCON0 = 0x1F;
   while (GO);
   unsigned short high = ADRESH;
   return (high << 8) | ADRESL;
}
