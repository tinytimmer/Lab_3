// Author:         
// Net ID:         
// Date:           
// Assignment:     Lab 3
//----------------------------------------------------------------------//

#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

void initLCD();
void initLCDPins();
void initLCDProcedure();
void writeCharacter(unsigned char character);
void writeString(const char *string);


void fourBitCommandWithDelay(unsigned char data, unsigned int delay); //this one is writeDataWithDelay()
void eightBitCommandWithDelay(unsigned char command, unsigned int delay); //this one is writeCommanWithUsDelay()

void moveCursor(unsigned char x, unsigned char y);


#endif
