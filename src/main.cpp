// Author: Carmen Timmer
// Net ID: cvtimmer
// Date: 02/28/2024
// Assignment:     Lab 3
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//

#include <Arduino.h>
#include <avr/io.h>
#include "led.h"
#include "switch.h"
#include "timer.h"
#include "lcd.h"

// defines from lab 2
#define NORMAL_SPEED 1
#define DOUBLE_SPEED 2


/*
 * Define a set of states that can be used in the state machine using an enum.
   Most of the lines of code are from lab 2, which i think I did ok in
 */
// typedef enum .......
  typedef enum stateType_enum{
    wait_press, button_press, wait_release, button_release
  }  stateType;


  //next well make some volatile variables below
  volatile stateType state = wait_press;
  volatile int counter = 0;
  volatile int multiplier = NORMAL_SPEED;
// Initialize states.  Remember to use volatile 

int main(){

  initTimer1(); //small difference here, changed form Timer0 to Timer1
  initLCD();
  initSwitchPB3();
  initLED();
  initTimer0();
  sei(); // Enable global interrupts.

//this is for lab 3 below

  //also got these from lecture slides
  moveCursor(0, 0); // moves the cursor to 0,0 position
  writeString("Currrent mode is:"); //write top line of LCD
  moveCursor(1, 0); // moves the cursor to 1,0 position
  
  //writeString(0xF2); //display speed of default mode
 writeCharacter(0xF2);
  //moveCursor(1,10);

// writing special character
/*   unsigned char ArrayCh[]={0x00, 0x00, 0x0a, 0x00, 0x1f, 0x11, 0x0e, 0x00};
  writeCharacter(0x00);
  setCGRAM(0X40);
  unsigned int i=0;
  while(i<=7){
    writeCharacter(ArrayCh[i]);
    i++;
  }
  // move cursor
  moveCursor(1,11); */

  //this is for lab 3 above
  


// while loop from lab 2 for the blink LEDs
 // delayMs(100/multiplier);


	while (1) {
    //after 100ms code needs to increment the binary number which is represented by LEDs
    //here is the delay
    delayMs(100/multiplier);
    //counter++;

    //then here is where we turn on the led
    turnOnLEDWithChar(counter);

    //here is the switch statements to go through the different states for the button
    switch (state)
    {
    case wait_press:
      break;

    case button_press:
      //Serial.println("button pressed");
      state = wait_release;
      break;

    case wait_release:
      //Serial.println("wait release");
      break;
    
    case button_release:
      //Serial.println("button release");
      Serial.println(multiplier);
      if (multiplier == NORMAL_SPEED)
      {
        multiplier = DOUBLE_SPEED;
      }

      else if (multiplier == DOUBLE_SPEED)
      {
        multiplier = NORMAL_SPEED;
      }
      
      state = wait_press;
      break;

    }

    //This is the upper limit for the counter
    if (counter == 15)
    {
      counter = 0;
    }
    counter++;
    
	}
  
  return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.

  This is from lab 2
*/
ISR(PCINT0_vect){
  //Serial.println("switch has been HIT");
  if (state == wait_press)
  {
    state = button_press;
  }
  else if (state == wait_release)
  {
    state = button_release;
  }
    
}