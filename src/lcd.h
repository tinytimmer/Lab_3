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
//void setCGRAM(unsigned char x);

void fourBitCommandWithDelay(unsigned char data, unsigned int delay); 
void eightBitCommandWithDelay(unsigned char command, unsigned int delay); 

void moveCursor(unsigned char x, unsigned char y);


#endif
