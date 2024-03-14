// Author: 
// Net ID: 
// Date: 
// Assignment: Lab 3
//----------------------------------------------------------------------//
#include "lcd.h"
#include "timer.h"
#include <util/delay.h>

/*
 * Initializes all pins related to the LCD to be outputs
 */
void initLCDPins(){
  // set LCD pins to output
  DDRA |= (1 << DDA0);
  DDRA |= (1 << DDA1);
  DDRA |= (1 << DDA2);
  DDRA |= (1 << DDA3);

  // next initialized RS and E
  DDRB |= (1 << DDB4) | (1 << DDB6); 
  
  //finally initialized R/W
  DDRH |= (1 << DDH4); 
}

//PB6 = pin 12 on board -> RS pin
//PB4 = pin 10 on board -> enable pin

/* //decided to put in this function to make it easier to change the enable pin
void assertEnable(){
  PORTB |= (1 << PORTB4); //enable pin is high
  delayUs(1);
  PORTB &= ~(1 << PORTB4); //enable pin is low
  delayUs(1);
} */

/* 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *      a. data is an unsigned char which has 8 bits. Therefore, you
 *         need assign the bottom 4 bits of "data" to the appropriate bits in
 *         PORTA`
 *  2. This is a "command" signal, meaning RS should be Low, NOTE TO SELF: why is low, whuolsnt we switch?
 *  3. Assert high on enable pin, delay, and asset low on enable pin
 *  4. delay the provided number in MICROseconds.
 */
void fourBitCommandWithDelay(unsigned char data, unsigned int delay){
  PORTA = (PORTA & 0xF0) | (data & 0x0F); //asserts bits here
  PORTB &= ~(1 << PORTB6);
  PORTB |= (1 << PORTB4); 
  delayUs(1);
  PORTB &= !(1 << PORTB);
  delayUs(delay);
}


/* Similar to fourBitCommandWithDelay except that now all eight bits of command are
 * sent.
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *       a. unlike fourBitCommandWithDelay, you need to send the TOP four bits of
 *          "command" first. These should be assigned to appropriate bits in PORTA
 * 2. This is a command signal, meaning RS should be low
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of command to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay the provided number in MICROseconds.
 */
void eightBitCommandWithDelay(unsigned char command, unsigned int delay){
  PORTA = ((PORTA & 0xF0) | ((command >> 4) & 0x0F));// asserts the bits to top here
  PORTB &= ~(1 << PORTB6); 
  PORTB |= (1 << PORTB6);
  delayUs(1);

  PORTB &= ~(1 << PORTB4);
  PORTA = ((PORTA & 0xF0) | (command & 0x0F)); //assert bits to the bottom here
  PORTB |= (1 << PORTB4);
  delayUs(1); 

  PORTB &= ~(1 << PORTB4);
  delayUs(delay);
}

/*
Similar to eightBitCommandWithDelay except that now RS should be high
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 * 2. This is a "data" signal, meaning RS should be high
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of character to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay is always 46 MICROseconds for a character write
 *
 * why did this repeat if this is a different function?
*/ 
void writeCharacter(unsigned char character){
  PORTA = ((PORTA & 0xF0) | ((character >> 4)  & 0x0F));
  PORTB |= (1 << PORTB6); 
  PORTB |= (1 << PORTB4);
  delayUs(1);
  PORTB &= ~(1 << PORTB4);
  
  PORTA = ((PORTA & 0xF0) | (character & 0x0F));
  PORTB |= (1 << PORTB4);
  delayUs(1);
  PORTB &= ~(1 << PORTB4);
  
  delayUs(53);
}





/*
 * Writes a provided string such as "Hello!" to the LCD screen. You should
 * remember that a c string always ends with the '\0' character and
 * that this should just call writeCharacter multiple times.
 * 
 * got this from lecture slides
 */
void writeString(const char *string){
    int i=0;
    while(string[i]!='\0')
    /* loop will go on till the NULL character
    in the string */
    { writeCharacter(string[i]);
    // sending data on LCD byte by byte
    i++;
    }

  /* unsigned int i = 0;
    while(i < strlen(string)){
      writeCharacter(string[i]);
      i++;
    } */
}



/*
 * This moves the LCD cursor to a specific place on the screen.
 * This can be done using the eightBitCommandWithDelay with correct arguments
 * 
 * got this from lecture slides
 */
void moveCursor(unsigned char x, unsigned char y){
	//to or 0x80 (setting D7 to 1), or'd with x << 6
  //(sets DB6 to either a 0 or 1) (row 0 or row 1), or'd with y
  eightBitCommandWithDelay(((0x80) | (x << 6) | (y)), 53);
}

/* //got this from lecture slides
 void setCGRAM(unsigned char x){
  //This function use an 8 bit command to set the CGRAM Address
  eightBitCommandWithDelay(x, 53);
} */
 


/* This is the procedure outline on the LCD datasheet page 4 out of 9.
 * This should be the last function you write as it largely depends on all other
 * functions working.
 */
void initLCDProcedure(){
  // Delay 15 milliseconds
  delayUs(15000);

  // Write 0b0011 to DB[7:4] and delay 4100 microseconds
  fourBitCommandWithDelay(0b0011, 4100);

  // Write 0b0011 to DB[7:4] and delay 100 microseconds
  fourBitCommandWithDelay(0b0011, 100);

  // The data sheet does not make this clear, but at this point you are issuing
  // commands in two sets of four bits. You must delay after each command
  // (which is the second set of four bits) an amount specified on page 3 of
  // the data sheet.
  // write 0b0011 to DB[7:4] and 100us delay
  //   thats good to know cuz I surely didnt get that info from the 
  fourBitCommandWithDelay(0b0011, 100);

  // write 0b0010 to DB[7:4] and 100us delay.
  fourBitCommandWithDelay(0b0010, 100);

  // Function set in the command table with 53us delay
  eightBitCommandWithDelay(0b00101000, 53);

  // Display off in the command table with 53us delay
  eightBitCommandWithDelay(0b00001000, 53);

  // Clear display in the command table. Remember the delay is longer!!!
  eightBitCommandWithDelay(0b00000001, 3000);

  // Entry Mode Set in the command table.
  eightBitCommandWithDelay(0b00000110, 53);

  // Display ON/OFF Control in the command table. (Yes, this is not specified),
  // in the data sheet, but you have to do it to get this to work. Yay datasheets!)
  eightBitCommandWithDelay(0b00001100, 53);
}



/* Initializes Tri-state for LCD pins and calls initialization procedure.
* This function is made so that it's possible to test initLCDPins separately
* from initLCDProcedure which will likely be necessary.
*/
void initLCD(){
  initLCDPins();
  initLCDProcedure();
}