// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****
#define LED1 0x01
#define LED2 0x02
#define LED3 0x04

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static struct Timer TimerA;
static struct Timer TimerB;
static struct Timer TimerC;

#define Timer_A 76
#define Timer_B 114
#define Timer_C 190

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
    printf("Welcome to nshabbar's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);

    TimerA.timeRemaining = Timer_A;
    TimerB.timeRemaining = Timer_B;
    TimerC.timeRemaining = Timer_C;

    LEDS_INIT();

    while (1) {
        //poll timer A
        //react to timer A events
        //clear timer A event flag
        char set = LEDS_GET();
        if (TimerA.event == TRUE) {
            printf("A");
            set ^= LED1; //needs to XOR to bounce
            TimerA.event = FALSE;
            TimerA.timeRemaining = Timer_A; //this equals time
        }
        if (TimerB.event == TRUE) {
            printf("B");
            set ^= LED2; //needs to XOR to bounce
            TimerB.event = FALSE;
            TimerB.timeRemaining = Timer_B; //this equals time
        }
        if (TimerC.event == TRUE) {
            printf("C");
            set ^= LED3; //needs to XOR to bounce
            TimerC.event = FALSE;
            TimerC.timeRemaining = Timer_C; //this equals time
        }
        LEDS_SET(set);
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
    TimerA.timeRemaining = TimerA.timeRemaining - 1;
    if (TimerA.timeRemaining == 0) {
        TimerA.event = TRUE;
    }
    TimerB.timeRemaining = TimerB.timeRemaining - 1;
    if (TimerB.timeRemaining == 0) {
        TimerB.event = TRUE;
    }
    TimerC.timeRemaining = TimerC.timeRemaining - 1;
    if (TimerC.timeRemaining == 0) {
        TimerC.event = TRUE;
    }
    //update timerA
    //if timerA has counted down,
    //generate timerA event
    //reset timerA


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}