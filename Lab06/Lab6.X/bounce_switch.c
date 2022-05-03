
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>



//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>
#include "Leds_Lab06.h"

// **** Declare any datatypes here ****

#define LED1 0x01
#define LED2 0x02
#define LED3 0x04
#define LED4 0x08
#define LED5 0x10
#define LED6 0x20
#define LED7 0x40
#define LED8 0x80

#define Board_Timer 2

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

typedef enum {
    LEFT = 0,
    RIGHT = 1
} direc;
// **** Define global, module-level, or external variables here ****
static struct Timer Timer1 = {
    .event = FALSE,
    .timeRemaining = Board_Timer
};

uint8_t LED_NOW = 1;
direc dir = LEFT;
// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to nshabbar's lab6 part2 (bounce_switch).  Compiled on %s %s.\n", __TIME__, __DATE__);

    LEDS_INIT();
    LEDS_SET(LED_NOW);

    while (1) {
        //poll timer events and react if any occur
        if (Timer1.event == TRUE) {
            Timer1.event = FALSE;
            Timer1.timeRemaining = Board_Timer * (SWITCH_STATES() + 1);
            if (LED_NOW == LED8) {
                dir = RIGHT;
            } else if (LED_NOW == LED1) {
                dir = LEFT;
            }
            if (dir == LEFT) {
                LED_NOW = LED_NOW << 1;
            } else if (dir == RIGHT) {
                LED_NOW = LED_NOW >> 1;
            }
            LEDS_SET(LED_NOW);
        }
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    Timer1.timeRemaining = Timer1.timeRemaining - 1;
    if (Timer1.timeRemaining == 0) {
        Timer1.event = TRUE;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}