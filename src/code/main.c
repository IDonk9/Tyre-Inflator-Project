/* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <string.h>
#include <math.h>
#include "ascii.h"
#include "ADC.h"
#include "config.h"
#include "CCP.h"
#include "EUSART.h"
#include "GLCD.h"
#include "splash.h"
#include "timers.h"
#include "libIndividual.h"
#define _XTAL_FREQ 8000000

#define DELAY 2000

void showSplash(void)
{
   const unsigned char* ptr = bitmap;
   
   for (byte page = 0; page < 8; ++page) {
      for (byte column = 0; column < 128; ++column) {
	 GIE = 0;
	 writeByte(page, column, *(ptr++));
	 GIE = 1;
      }
   }
   
   __delay_ms(DELAY);
   
   GIE = 0;
   clearGLCD(0, 7, 0, 127);
   GIE = 1;
}

void showIntro(void)
{
   static const char* text[] = {
      "L7 Projecte",
      "Ferran Mesas Borras",
      "Javier Zhangpan"
   };
   
   static const byte length[] = {
      sizeof("L7 Projecte"),
      sizeof("Ferran Mesas Borras"),
      sizeof("Javier Zhangpan")
   };
   
   static const byte start[] = {
      (26 - sizeof("L7 Projecte")) >> 1,
      (26 - sizeof("Ferran Mesas Borras")) >> 1,
      (26 - sizeof("Javier Zhangpan")) >> 1
   };
   
   // Manual vertical alignment.
   for (byte i = 0; i < 3; ++i) {
      writeText(2 + i, start[i], text[i]);
   }
   
   __delay_ms(DELAY);
   
   for (byte i = 0; i < 3; ++i) {
      GIE = 0;
      clearGLCD(2 + i, 2 + i, 5*start[i], 5*(start[i] + length[i]));
      GIE = 1;
   }
}

// Change it to modulate the period in which
// the flanks are ignored because of bouncing.
// Every unit here is 100 ms, this might cause
// the animation to look slower, if you decrease
// it, the animation will be faster, but at the
// expense of detecting some "false" flanks.
#define TARGET_COUNT 2

// Initializing the structs for the buttons.
// I had to initialize it in the same declaration
// because this version of C does not support
// compound literals as C99 would.
Button buttons[4] = {
   // 	startingPage, 	startingColumn, name, 		function, 	typeOfEdge, 	bouncingCount, 	previousState, 	port, 		mask
   { 	2, 		2, 		"RC0", 		'+', 		RisingEdge, 	0, 		0, 		&PORTC, 	0x01 },
   { 	2, 		7, 		"RC1", 		'-', 		RisingEdge,	0,	 	0, 		&PORTC, 	0x02 },
   { 	2, 		12, 		"RC2", 		'>', 		RisingEdge, 	0, 		0, 		&PORTC, 	0x04 },
   { 	2, 		17, 		"RC3", 		'!', 		RisingEdge, 	0, 		0, 		&PORTC, 	0x08 }
};

//		startingColumn, percentage
Bar bar = { 	110, 		0 	   };

unsigned short ticsSinceStart = 0;
unsigned short ticsToFinish = 0;
// "lines" is a percentage count for the bar.
byte lines = 0;
byte measure = 0;
byte animate = 0;
char currentCommand = '\0';

void interrupt high_priority RSI(void)
{
   if (TMR0IE && TMR0IF) {
      // Initialize timer.
      TMR0H = (unsigned short)15536 >> 8; TMR0L = 15536;
      TMR0IF = 0;
      // Set the measure bit.
      measure = 1;
      animate = 1;
      // Increment count if needed.
      for (byte i = 0; i < 4; ++i) {
	 if (buttons[i].bouncingCount < TARGET_COUNT) {
	    ++buttons[i].bouncingCount;
	 }
      }
      if (ticsSinceStart < ticsToFinish) ++ticsSinceStart;
      if (ticsToFinish > 0) {
	 byte newLines = (100*ticsSinceStart)/ticsToFinish;
	 // Usually, it will only be one line,
	 // but, if time is very short, then
	 // we may need to print several at once.
	 while (lines < newLines) {
	    printBarIncrement(&bar);
	    ++lines;
	 }
      }
   }
   if (TMR2IE && TMR2IF) {
      TMR2IF = 0;
   }
   if (RC1IE && RC1IF) {
      if (receptionError()) {
	 // If there is an error, cannot
	 // retrieve data this time.
	 receptionErrorRecovery();
      } else {
	 currentCommand = RCREG1;
      }
      RC1IF = 0;
   }
}

float getTemperature(void)
{
   float voltage = 5.0f*(float)getAN6()/1023.0f;
   return 4050.0f/log(-(4751.0f-(4751.0f*5.0f)/(voltage))/0.0059257f) - 273.15f;
}

float getPressure(void)
{
   return 90.0f*(float)getAN7()/1023.0f;
}

void transmitIntroToTerminal(void)
{
   static const char* message[] = {
      "Projecte 7\r\n",
      "Ferran Mesas Borras\r\n",
      "Javier Zhangpan\r\n"
   };
   
   for (byte i = 0; i < 3; ++i) {
      transmitAsyncEUSART(message[i]);
   }
}

void printButtons(void)
{
   for (byte i = 0; i < 4; ++i) {
      printButton(&buttons[i]);
   }
}

void printFlatTyreAlert(void)
{
   static const char* alert = "Is your tyre flat?";
   static const byte start = ((26 - sizeof("Is your tyre flat?")) >> 1) - 1;
   writeText(5, start, alert);
}

void eraseFlatTyreAlert(void)
{
   static const byte length = sizeof("Is your tyre flat?");
   static const byte start = ((26 - sizeof("Is your tyre flat?")) >> 1) - 1;
   GIE = 0;
   clearGLCD(5, 5, 5*start, 5*(start + length));
   GIE = 1;
}

// Returns 1 if animation finised, 0 otherwise.
byte successAnimationFrame(void)
{
   static const char* text = "Finished";
   static const byte start = 5*(((26 - sizeof("Progress")) >> 1) - 1);
   static const byte length = 5*(sizeof("Progress") - 1) - 1;
   static byte offset = 0;
   GIE = 0;
   writeByte(6, start + offset, font5x7[5*(text[offset/5] - ' ') + offset%5]);
   writeByte(6, start + offset + 1, 0xff);
   GIE = 1;
   if (++offset == length) {
      offset = 0;
      return 1;
   } else {
      return 0;
   }
}

void config(void)
{
   ANSELA = 0x00;
   ANSELB = 0x00;
   ANSELC = 0x00;
   ANSELD = 0x00;
   ANSELE = 0xfe;
   
   TRISA = 0x00;
   TRISB = 0x00;
   TRISC = 0xbf;
   TRISD = 0x00;
   TRISE = 0xfe;
   
   PORTA = 0x00;
   PORTB = 0x00;
   PORTD = 0x00;
   PORTE = 0x00;
}

typedef enum {
   Select = 0,
   Progress = 1,
   Finished = 2,
   Null = 3, 	// To enforce initialization.
   Success = 4 	// Never call changeState on it.
} state_t;

void changeState(state_t state)
{
   static const char* states[] = {
      "Select",
      "Progress",
      "Finished",
      ""
   };
   
   static const byte length[] = {
      sizeof("Select"),
      sizeof("Progress"),
      sizeof("Finished"),
      sizeof("")
   };
   
   static const byte start[] = {
      ((26 - sizeof("Select")) >> 1) - 1,
      ((26 - sizeof("Progress")) >> 1) - 1,
      ((26 - sizeof("Finished")) >> 1) - 1,
      ((26 - sizeof("")) >> 1) - 1
   };
   
   static const byte leds[] = { 0x01, 0x02, 0x04, 0x00 };
   
   static state_t previous = Null;
   
   GIE = 0;
   clearGLCD(6, 6, 5*start[previous], 5*(start[previous] + length[previous]));
   GIE = 1;
   writeText(6, start[state], states[state]);
   
   PORTA = leds[state];
   
   previous = state;
}

void main(void)
{
   config();
   initADC();
   initTMR2();
   initPWM();
   initEUSART();
   initTMR0();

   GLCDinit();
   clearGLCD(0, 7, 0, 127);
   setStartLine(0);
   
   showSplash();
   transmitIntroToTerminal();
   showIntro();
   
   printBar(&bar);
   
   printButtons();
   
   //			  page,		centerColumn,	value,		previousValue,	prefix,			prefixLength,			unit
   Value selectedPSI = 	{ 7, 		10, 		0, 		0, 		"Selected PSI: ", 	sizeof("Selected PSI: ") - 1, 	"PSI" };
   Value pressure = 	{ 0, 		5, 		0,		0, 		"", 			sizeof("") - 1,			"PSI" };
   Value temperature = 	{ 0, 		17, 		0, 		0, 		"", 			sizeof("") - 1, 		"DEG" };
   
   pressure.value = (byte)getPressure();
   temperature.value = (byte)getTemperature();
   
   printValue(&selectedPSI);
   printValue(&pressure);
   printValue(&temperature);
   
   state_t state = Select;
   changeState(state);
   
   byte flatTyreAlert = 0;
   byte reducedPressure = 0;
   
   while (1) {
      // Measure every 100 ms.
      if (measure) {
	 pressure.value = (byte)getPressure();
	 temperature.value = (byte)getTemperature();
	 reducedPressure = pressure.value < pressure.previousValue;
	 updateValue(&pressure);
	 updateValue(&temperature);
	 measure = 0;
      }
      // Update the state of the buttons and
      // store the edges.
      byte edges[4];
      for (byte i = 0; i < 4; ++i) {
	 edges[i] = updateButtonState(&buttons[i]);
      }
      (void)0xdeadbeef;
      switch (state) {
	 case Select: {
	    if (edges[0] || currentCommand == 'd') {
	       if (selectedPSI.value < 90) {
		  ++selectedPSI.value;
		  updateValue(&selectedPSI);
	       }
	    }
	    if (edges[1] || currentCommand == 'a') {
	       if (selectedPSI.value > 0) {
		  --selectedPSI.value;
		  updateValue(&selectedPSI);
	       }
	    }
	    if (edges[2] || currentCommand == 's') {
	       // Compute ticsToFinish.
	       lines = 0;
	       ticsSinceStart = 0;
	       ticsToFinish = 10*(((selectedPSI.value - pressure.value) >> 1) - (temperature.value - 25));
	       // If negative or zero, fill the bar and finish.
	       if ((signed short)ticsToFinish <= 0) {
		  ticsToFinish = 0;
		  for (byte i = 1; i <= 100; ++i) {
		     printBarIncrement(&bar);
		  }
		  changeState(state = Finished);
		  break;
	       }
	       changeState(state = Progress);
	       setDutyCycleFromPSI(selectedPSI.value);
	       enablePWM();
	    }
	    currentCommand = '\0';
	    break;
	 }
	 case Progress: {
	    // Check for flat tyre (if the pressure has been reduced in 100 ms).
	    if (ticsSinceStart > 0 && reducedPressure && !flatTyreAlert) {
	       flatTyreAlert = 1;
	       printFlatTyreAlert();
	    }
	    if (edges[3] || currentCommand == 'w' || ticsSinceStart == ticsToFinish) {
	       if (ticsSinceStart == ticsToFinish && !flatTyreAlert) {
		  // Successful.
		  state = Success;
	       } else {
		  // Not successful.
		  changeState(state = Finished);
	       }
	       disablePWM();
	       lines = 0;
	       ticsSinceStart = 0;
	       ticsToFinish = 0;
	    }
	    currentCommand = '\0';
	    break;
	 }
	 case Success: {
	    if (animate) {
	       animate = 0;
	       if (successAnimationFrame()) {
		  changeState(state = Finished);
	       }
	    }
	    break;
	 }
	 case Finished: {
	    if (edges[2] || currentCommand == 's') {
	       eraseBarProgress(&bar);
	       if (flatTyreAlert) {
		  flatTyreAlert = 0;
		  eraseFlatTyreAlert();
	       }
	       changeState(state = Select);
	    }
	    currentCommand = '\0';
	    break;
	 }
      }
   }
}
