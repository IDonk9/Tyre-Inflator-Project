#include "libIndividual.h"

void writeText(byte page, byte y, const char* s)
{
   byte i = 0;
   while (*s != '\n' && *s != '\0') {
      GIE = 0;
      putchGLCD(page, y + i, *(s++));
      GIE = 1;
      ++i;
   }
}

// Trying to write entire bytes for efficiency.
void printVerticalLine(byte column, byte from, byte to)
{
   while (from <= to && (from & 7)) {
      GIE = 0;
      SetDot(from++, column);
      GIE = 1;
   }
   while (from + 7 <= to) {
      GIE = 0;
      writeByte(from >> 3, column, 0xff);
      GIE = 1;
      from += 8;
   }
   while (from <= to) {
      GIE = 0;
      SetDot(from++, column);
      GIE = 1;
   }
}

void eraseVerticalLine(byte column, byte from, byte to)
{
   while (from <= to && (from & 7)) {
      GIE = 0;
      ClearDot(from++, column);
      GIE = 1;
   }
   while (from + 7 <= to) {
      GIE = 0;
      writeByte(from >> 3, column, 0x00);
      GIE = 1;
      from += 8;
   }
   while (from <= to) {
      GIE = 0;
      ClearDot(from++, column);
      GIE = 1;
   }
}

// Not much that can be done for efficiency.
void printHorizontalLine(byte row, byte from, byte to)
{
   while (from <= to) {
      GIE = 0;
      SetDot(row, from++);
      GIE = 1;
   }
}

void eraseHorizontalLine(byte row, byte from, byte to)
{
   while (from <= to) {
      GIE = 0;
      ClearDot(row, from++);
      GIE = 1;
   }
}

// Column as if it was for chars.
// It fits in a 3x3.
// Initially not toggled.
void printButtonShape(byte startingPage, byte startingColumn, const char* name, char function)
{
   printHorizontalLine(
      (startingPage << 3) + 6,
      5*startingColumn,
      5*(startingColumn + 3) - 1
   );
   
   printHorizontalLine(
      startingPage << 3,
      5*startingColumn + 3,
      5*(startingColumn + 3) - 4
   );
   
   printVerticalLine(
      5*startingColumn + 3,
      startingPage << 3,
      (startingPage << 3) + 6
   );
   
   printVerticalLine(
      5*(startingColumn + 3) - 4,
      startingPage << 3,
      (startingPage << 3) + 6
   );
   
   GIE = 0;
   writeText(startingPage + 1, startingColumn, name);
   GIE = 1;
   
   GIE = 0;
   putchGLCD(startingPage + 2, startingColumn + 1, function);
   GIE = 1;
}

// Button must be untoggled.
void printButtonToggle(byte startingPage, byte startingColumn)
{
   eraseHorizontalLine(
      startingPage << 3,
      5*startingColumn + 3,
      5*(startingColumn + 3) - 4
   );
   
   eraseVerticalLine(
      5*startingColumn + 3,
      startingPage << 3,
      (startingPage << 3) + 3
   );
   
   eraseVerticalLine(
      5*(startingColumn + 3) - 4,
      startingPage << 3,
      (startingPage << 3) + 3
   );
   
   printHorizontalLine(
      (startingPage << 3) + 3,
      5*startingColumn + 3,
      5*(startingColumn + 3) - 4
   );
}

// Button must be toggled.
void printButtonUntoggle(byte startingPage, byte startingColumn)
{
   eraseHorizontalLine(
      (startingPage << 3) + 3,
      5*startingColumn + 3,
      5*(startingColumn + 3) - 4
   );
   
   printHorizontalLine(
      startingPage << 3,
      5*startingColumn + 3,
      5*(startingColumn + 3) - 4
   );
   
   printVerticalLine(
      5*startingColumn + 3,
      startingPage << 3,
      (startingPage << 3) + 3
   );
   
   printVerticalLine(
      5*(startingColumn + 3) - 4,
      startingPage << 3,
      (startingPage << 3) + 3
   );
}

void printButton(Button* button)
{
   printButtonShape(button->startingPage, button->startingColumn, &button->name, button->function);
}

byte updateButtonState(Button* button)
{
   byte currentState = *button->port & button->mask;
   byte previousState = button->previousState;
   byte edge = 0;
   if (button->typeOfEdge == RisingEdge) {
      if (previousState != currentState) {
	 if (button->bouncingCount == TARGET_COUNT && !previousState && currentState) {
	    edge = 1;
	    button->bouncingCount = 0;
	    printButtonToggle(button->startingPage, button->startingColumn);
	 } else {
	    printButtonUntoggle(button->startingPage, button->startingColumn);
	 }
      }
   } else {
      // button->typeOfEdge == FallingEdge
      if (previousState != currentState) {
	 if (button->bouncingCount == TARGET_COUNT && previousState && !currentState) {
	    edge = 1;
	    button->bouncingCount = 0;
	    printButtonToggle(button->startingPage, button->startingColumn);
	 } else {
	    printButtonUntoggle(button->startingPage, button->startingColumn);
	 }
      }
   }
   button->previousState = currentState;
   return edge;
}

void printValue(Value* value)
{
   byte totalLength = value->prefixLength + (value->value < 10 ? 1 : 2) + 4;
   byte startingColumn = value->centerColumn - (totalLength >> 1);
   writeText(value->page, startingColumn, value->prefix);
   if (value->value > 9) {
      GIE = 0;
      putchGLCD(value->page, startingColumn + totalLength - 6, '0' + value->value/10);
      putchGLCD(value->page, startingColumn + totalLength - 5, '0' + value->value%10);
      putchGLCD(value->page, startingColumn + totalLength - 4, ' ');
      writeText(value->page, startingColumn + totalLength - 3, value->unit);
      GIE = 1;
   } else {
      GIE = 0;
      putchGLCD(value->page, startingColumn + totalLength - 5, '0' + value->value);
      putchGLCD(value->page, startingColumn + totalLength - 4, ' ');
      writeText(value->page, startingColumn + totalLength - 3, value->unit);
      GIE = 1;
   }
   value->previousValue = value->value;
}

void updateValue(Value* value)
{
   if (value->value == value->previousValue) return;
   if ((value->value < 10) == (value->previousValue < 10)) {
      // Manual update to modify only one or two characters.
      byte totalLength = value->prefixLength + (value->value < 10 ? 1 : 2) + 4;
      byte startingColumn = value->centerColumn - (totalLength >> 1);
      if (value->value > 9) {
	 GIE = 0;
	 putchGLCD(value->page, startingColumn + totalLength - 6, '0' + value->value/10);
	 putchGLCD(value->page, startingColumn + totalLength - 5, '0' + value->value%10);
	 GIE = 1;
      } else {
	 GIE = 0;
	 putchGLCD(value->page, startingColumn + totalLength - 5, '0' + value->value);
	 GIE = 1;
      }
      value->previousValue = value->value;
   } else {
      if (value->value < value->previousValue) {
	 // If the size decresed, the first character
	 // will not be overwritten.
	 byte totalLength = value->prefixLength + (value->previousValue < 10 ? 1 : 2) + 4;
	 byte startingColumn = value->centerColumn - (totalLength >> 1);
	 GIE = 0;
	 clearGLCD(value->page, value->page, 5*startingColumn, 5*startingColumn + 4);
	 GIE = 1;
      }
      printValue(value);
   }
}

void printBar(Bar* bar)
{
   // Leaving padding between top and bottom (5 px).
   // Leaving padding between the shape and the progess bar
   // (1 px), except for the right part (3 px) because of the
   // horizontal lines.
   printVerticalLine(bar->startingColumn, 5, 58);
   printVerticalLine(bar->startingColumn + 10, 5, 58);
   printHorizontalLine(5, bar->startingColumn + 1, bar->startingColumn + 9);
   printHorizontalLine(58, bar->startingColumn + 1, bar->startingColumn + 9);
   
   // Long lines.
   for (byte i = 56; i >= 7; i -= 6) {
      GIE = 0;
      SetDot(i, bar->startingColumn + 9);
      SetDot(i, bar->startingColumn + 8);
      GIE = 1;
   }
   
   // Short lines.
   for (byte i = 53; i >= 9; i -= 6) {
      GIE = 0;
      SetDot(i, bar->startingColumn + 9);
      GIE = 1;
   }
}

// Assumes that a correct state in the GLCD.
// Prints one line every 2 increments on the
// time that percentage is odd.
// The state of percentage will be updated in
// the function call.
void printBarIncrement(Bar* bar)
{
   ++bar->percentage;
   if (bar->percentage & 1) {
      printHorizontalLine(
	 56 - (bar->percentage >> 1),
	 bar->startingColumn + 2,
	 bar->startingColumn + 6
      );
   }
}

void printBarDecrement(Bar* bar)
{
   --bar->percentage;
   if ((bar->percentage & 1) == 0) {
      eraseHorizontalLine(
	 56 - (bar->percentage >> 1),
	 bar->startingColumn + 2,
	 bar->startingColumn + 6
      );
   }
}

void eraseBarProgress(Bar* bar)
{
   for (byte i = 0; i < 5; ++i) {
      eraseVerticalLine(bar->startingColumn + 2 + i, 7, 56);
   }
   bar->percentage = 0;
}