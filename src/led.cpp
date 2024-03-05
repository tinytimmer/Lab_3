// Description: This file implements turnOnLED and initLED to control
// the LEDs.
//----------------------------------------------------------------------//


#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

/* Initialize PD0, PD1, PD2, and PD3 to outputs

Pins for these on the board are the following:
    PD0 = pin 21
    PD1 = pin 20
    PD2 = pin 19
    PD3 = pin 18
*/
void initLED(){
//this set the LEDs as outputs, loosely based on lab 2 code
  DDRD |= (1 << DDD0);
  DDRD |= (1 << DDD1);
  DDRD |= (1 << DDD2);
  DDRD |= (1 << DDD3);
}

/* This must be one line of code.
* In this function you will be giving a number "num" which will be represented
* in binary by four LEDs. You must effectively assign the lowest four bits of
* "num" to the appropriate bits of PORTD.
*/
void turnOnLEDWithChar(unsigned char num){
  PORTD = (PORTD & 0xF0) | (num & 0x0F);
}
