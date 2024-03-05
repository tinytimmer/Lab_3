// Author: 
// Net ID: 
// Date: 
// Assignment: Lab 3
//----------------------------------------------------------------------//

#include "timer.h"
//You many use any timer you wish for the microsecond delay and the millisecond delay


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
	
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){

}

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode
    Below is from lab 2, lines 26-68
 */
void initTimer0(){
    //set up timer0 for ctc mode
    TCCR0A &= ~(1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
    unsigned int count = 0;

    OCR0A = 249;
    //int prescalar = 64;

    // TURN ON CLOCK , SET FREQ PRSCALER TO 64
    TCCR0B  |= (1 << CS00) | (1 << CS01);
    TCCR0B  &= ~ (1 << CS02);

    //from example code
    
    // go into the millisecond loop and loop until count = delay
    // after this while loop the delay time = delay * 1ms
    while (count < delay){
    // CLEAR THE OCF0A FLAG ()
    // CLEAR THE OCF0A flag by writing a 1 bit
    TIFR0 |= (1 << OCF0A);

    TCNT0 = 0;
    // CLEAR THE COUNTER TO RESTART COUNTING UP TO 249
    // WHILE THE FLAG OCF0A IS NOT RAISED DO NOTHING
    while ( !(TIFR0 & ( 1 << OCF0A)));
    
    count++;
    }

    //turning off the clock
    TCCR0B  &= ~ ((1 << CS00) | (1 << CS01) | ( 1 << CS02));
   
}