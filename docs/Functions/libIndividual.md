# libIndividual Documentation

## **Function: writeText**

**Precondition:**
- GLCD must be initialized.

**Postcondition:**
- Writes a null-terminated string (`s`) to the specified page and y-coordinate on the GLCD.

**Synopsis:**
```c
#include "libIndividual.h"

void writeText(byte page, byte y, const char* s);
```

**Description:**
- Writes each character from the string s to the GLCD at the specified page and y position, stopping at a newline (\n) or null terminator (\0).
- Temporarily disables global interrupts (GIE) during the putchGLCD function call for safe operation.

**Return value:**
- This function does not return a value.

## **Function: printVerticalLine**

**Precondition:**
- GLCD must be initialized.

**Postcondition:**
- A vertical line is drawn on the GLCD in the specified column between `from` and `to` rows.

**Synopsis:**
```c
#include "libIndividual.h"

void printVerticalLine(byte column, byte from, byte to);
```

**Description:**
- Draws a vertical line in the specified column from row from to row to.
- Sets individual dots for rows not aligned to byte boundaries.
- Temporarily disables global interrupts (GIE) during each GLCD operation.

**Return value:**
- This function does not return a value.

## **Function: eraseVerticalLine**

**Precondition:**
- GLCD must be initialized.

**Postcondition:**
- A vertical line is erased on the GLCD in the specified column between `from` and `to` rows.

**Synopsis:**
```c
#include "libIndividual.h"

void eraseVerticalLine(byte column, byte from, byte to);
```

**Description:**
- Erases a vertical line in the specified column from row from to row to.
- Clears individual dots for rows not aligned to byte boundaries.
- Temporarily disables global interrupts (GIE) during each GLCD operation.

**Return value:**
- This function does not return a value.

## **Function: printHorizontalLine**

**Precondition:**
- GLCD must be initialized.

**Postcondition:**
- A horizontal line is drawn on the GLCD at the specified row from column `from` to column `to`.

**Synopsis:**
```c
#include "libIndividual.h"

void printHorizontalLine(byte row, byte from, byte to);
```

**Description:**
- Draws a horizontal line in the specified row by setting individual dots from column from to column to.
- Temporarily disables global interrupts (GIE) during each GLCD operation.

**Return value:**
- This function does not return a value.

## **Function: eraseHorizontalLine**

**Precondition:**
- GLCD must be initialized.

**Postcondition:**
- A horizontal line is erased on the GLCD at the specified row from column `from` to column `to`.

**Synopsis:**
```c
#include "libIndividual.h"

void eraseHorizontalLine(byte row, byte from, byte to);
```

**Description:**
- Erases a horizontal line in the specified row by clearing individual dots from column from to column to.
- Temporarily disables global interrupts (GIE) during each GLCD operation.

**Return value:**
- This function does not return a value.

## **Function: printButtonShape**

**Precondition:**
- GLCD must be initialized.

**Postcondition:**
- A 3x3 button shape is drawn on the GLCD starting from the specified page and column.

**Synopsis:**
```c
#include "libIndividual.h"

void printButtonShape(byte startingPage, byte startingColumn, const char* name, char function);
```

**Description:**
- Draws a rectangular button shape at the specified startingPage and startingColumn using horizontal and vertical lines:
- The top and bottom edges are defined by horizontal lines.
- The left and right edges are defined by vertical lines.
- Displays the button's label (name) and function character (function) inside the rectangle.

**Return value:**
- This function does not return a value.

## **Function: printButtonToggle**

**Precondition:**
- GLCD must be initialized, and the button must be in an untoggled state.

**Postcondition:**
- Toggles the button state visually by modifying its graphical representation.

**Synopsis:**
```c
#include "libIndividual.h"
void printButtonToggle(byte startingPage, byte startingColumn);
```

**Description:**
- Adjusts the button's appearance at the specified startingPage and startingColumn:
- Erases the top edge and upper parts of the left and right edges.
- Draws a new horizontal line closer to the button's center to give the toggled appearance.

**Return value:**
- This function does not return a value.

## **Function: printButtonUntoggle**

**Precondition:**
- GLCD must be initialized, and the button must be in a toggled state.

**Postcondition:**
- Returns the button to its untoggled state visually by restoring its original graphical representation.

**Synopsis:**
```c
#include "libIndividual.h"

void printButtonUntoggle(byte startingPage, byte startingColumn);
```

**Description:**
- Restores the button's untoggled appearance at the specified startingPage and startingColumn:
- Erases the inner horizontal line from the toggled state.
- Redraws the top edge and upper parts of the left and right edges to reestablish the untoggled look.

**Return value:**
- This function does not return a value.

## **Function: printButton**

**Precondition:**
- GLCD must be initialized and button must be valid.

**Postcondition:**
- The button is drawn on the GLCD using the details from the `Button` structure.

**Synopsis:**
```c
#include "libIndividual.h"

void printButton(Button* button);
```

**Description:**
- Draws the button on the GLCD by calling printButtonShape with the startingPage, startingColumn, name, and function from the Button structure.

**Return value:**
- This function does not return a value.

## **Function: updateButtonState**

**Precondition:**
- GLCD must be initialized and button must be valid

**Postcondition:**
- The button's state is updated, and the visual state of the button on the GLCD is toggled or untoggled based on the edge detection logic.

**Synopsis:**
```c
#include "libIndividual.h"

byte updateButtonState(Button* button);
```

**Description:**
- Checks the state of the button (from port and mask) and compares it to the previous state (previousState).If the button is configured for rising or falling edge detection, it identifies a state change:
    - On a rising edge (when state changes from 0 to 1), it toggles the button if the state remains stable (based on bouncingCount).
    - On a falling edge (when state changes from 1 to 0), it similarly toggles or untoggles based on the bouncing count.
- The visual button state is updated on the GLCD using printButtonToggle or printButtonUntoggle.
- Updates the previousState for future comparisons.

**Return value:**
- Returns 1 if a valid edge was detected, 0 otherwise.

## **Function: printValue**

**Precondition:**
- GLCD must be initialized and value must be valid.

**Postcondition:**
- The value is printed on the GLCD, formatted with a prefix, numeric value, and unit.

**Synopsis:**
```c
void printValue(Value* value);
```

**Description:**
- Displays the value on the GLCD at the specified page and centerColumn, including:
    - A prefix (prefix), followed by the numeric value.
    - If the value is greater than 9, it is displayed with two digits.
    - A space is added after the numeric value, followed by the unit (unit).
    - The value is centrally aligned based on the calculated total length.
- Updates previousValue for comparison in subsequent prints.

**Return value:**
- This function does not return a value.

## **Function: updateValue**

**Precondition:**
- GLCD must be initialized and value must be valid.

**Postcondition:**
- Displayed value on the GLCD has been updated if it has changed, either by modifying only the changed characters or clearing the old value and printing the new one.

**Synopsis:**
```c
#include "libIndividual.h"

void updateValue(Value* value);
```

**Description:**
- Compares the current value with the previousValue to detect changes.
    - If the value remains the same, no update occurs.
    - If the value changes and the new value has the same number of digits (1 or 2), it only updates the relevant digits (either the first or second digit).
    - If the new value has a different number of digits (e.g., a change from 1-digit to 2-digit), the old value is cleared, and the new value is printed in full.
- Updates the previousValue to keep track of the current state.

**Return value:**
- This function does not return a value.

## **Function: printBar**

**Precondition:**
- GLCD must be initialized and bar must be valid.

**Postcondition:**
- Prints a progress bar on the GLCD at the specified location.

**Synopsis:**
```c
#include "libIndividual.h"

void printBar(Bar* bar);
```
**Description:**
- The function prints a progress bar with padding and structure:
    - Vertical lines are drawn at the specified starting column (startingColumn) to form the sides of the bar.
    - Horizontal lines are drawn at the top and bottom for the bar's frame.
    - Long lines are drawn along the sides of the bar for decoration.
    - Short lines are drawn on the top-right and bottom-right corners of the bar.

**Return value:**
- This function does not return a value.

## **Function: printBarIncrement**

**Precondition:**
- GLCD must be initialized and bar must be valid and be in a valid position

**Postcondition:**
- The progress bar's percentage will be updated and a horizontal line will be printed on the GLCD if the percentage is odd.

**Synopsis:**
```c
#include "libIndividual.h"

void printBarIncrement(Bar* bar);
```

**Description:**
- The function increments the percentage of the progress bar.
- If the new percentage is odd, it prints a horizontal line on the GLCD to visually represent progress.

**Return value:**
- This function does not return a value.

## **Function: printBarDecrement**

**Precondition:**
- GLCD must be initialized and bar must be valid and be in a valid position

**Postcondition:**
- The progress bar's percentage will be decremented and a horizontal line will be erased on the GLCD if the percentage is even.

**Synopsis:**
```c
#include "libIndividual.h"

void printBarDecrement(Bar* bar);
```

**Description:**
- The function decrements the percentage of the progress bar.
- If the new percentage is even, it erases a horizontal line on the GLCD to visually represent a decrease in progress.

**Return value:**
- This function does not return a value.

## **Function: eraseBarProgress**

**Precondition:**
- GLCD must be initialized and bar must be valid

**Postcondition:**
- The progress bar will be cleared on the GLCD by erasing the vertical lines representing the progress.
- The `percentage` field in the `Bar` structure will be reset to 0.

**Synopsis:**
```c
#include "libIndividual.h"

void eraseBarProgress(Bar* bar);
```

**Description:**
- The function erases the progress bar by clearing the vertical lines.
- After clearing the bar, the percentage of the progress bar is reset to 0.

**Return value:**
- This function does not return a value.