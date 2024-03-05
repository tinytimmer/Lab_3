// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
    Also from lab 2 code
 */
void initSwitchPB3(){
  PORTB |= (1 << PORTB3); //set the pull-up resistor to on at pin 50 on board
  DDRB &= ~(1 << DDB3); //this set the switch to be an input (which is what we want)

  //since were introducing timers and interrupters below is the code that handles that
  PCICR |= (1 << PCIE0); //this line enables the pin-change interrupts for this lab
  
  //this line of code enlabes the interrupts on PB3, which is pin 50 on the board (theoretically)
  //PCMSK0 |= (1 << PCINT2 | 1 << PCINT3);
  PCMSK0 |= ( 1 << PCINT3);
}
