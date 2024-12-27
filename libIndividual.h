#include <xc.h>
#include "config.h"
#include "GLCD.h"

#define TARGET_COUNT 2

typedef unsigned char byte;

typedef enum {
   FallingEdge = 0,
   RisingEdge = 1
} edge_t;

typedef struct {
   byte startingPage;
   byte startingColumn;
   char name[4];
   char function;
   edge_t typeOfEdge;
   byte bouncingCount;
   byte previousState;
   volatile byte* port;
   byte mask;
} Button;

typedef struct {
   byte page;
   byte centerColumn;
   byte value;
   byte previousValue;
   const char* prefix;
   byte prefixLength;
   char unit[4];
} Value;

typedef struct {
   byte startingColumn;
   byte percentage;
} Bar;

void writeText(byte page, byte y, const char* s);

void printVerticalLine(byte column, byte from, byte to);

void eraseVerticalLine(byte column, byte from, byte to);

void printHorizontalLine(byte row, byte from, byte to);

void eraseHorizontalLine(byte row, byte from, byte to);

void printProgressShape(byte startingColumn);

void printButtonShape(byte startingPage, byte startingColumn, const char* name, char function);

void printButtonToggle(byte startingPage, byte startingColumn);

void printButtonUntoggle(byte startingPage, byte startingColumn);

// New
void printButton(Button* button);

// New
byte updateButtonState(Button* button);

// New
void printValue(Value* value);

// New
void updateValue(Value* value);

// New (adapted)
void printBar(Bar* bar);

// New (adapted)
void printBarIncrement(Bar* bar);

// New (adapted)
void printBarDecrement(Bar* bar);

// New.
void eraseBarProgress(Bar* bar);