// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>
#include "Leds_Lab06.h"

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
static uint8_t Button;
static uint8_t prog = FALSE;
#define LED1 0x01 //binary eq: 0000 0001
#define LED2 0x02 //binary eq: 0000 0010
#define LED3 0x04 //binary eq: 0000 0100
#define LED4 0x08 //binary eq: 0000 1000
#define LED5 0x10 //binary eq: 0001 0000
#define LED6 0x20 //binary eq: 0010 0000
#define LED7 0x40 //binary eq: 0100 0000
#define LED8 0x80 //binary eq: 1000 0000
uint8_t LED_NUM1 = 1;
uint8_t LED_NUM2 = 2;
uint8_t LED_NUM3 = 3;
uint8_t LED_NUM4 = 4;
uint8_t LED_NUM5 = 5;
uint8_t LED_NUM6 = 6;
uint8_t LED_NUM7 = 7;
uint16_t LED_NUM8 = 8;
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
    printf("Welcome to nshabbar's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    uint8_t switchesState = SWITCH_STATES();
    LEDS_INIT();
    LEDS_SET(LED_NUM1);LEDS_SET(LED_NUM2);LEDS_SET(LED_NUM3);LEDS_SET(LED_NUM4);
    LEDS_SET(LED_NUM5);LEDS_SET(LED_NUM6);LEDS_SET(LED_NUM7);LEDS_SET(LED_NUM8);

    while (1) {
        if (prog == TRUE) {
            if ((switchesState & SWITCH_STATE_SW1) == 1 &&
                    (Button & BUTTON_EVENT_1UP)) {
                LED_NUM1 = LED1;
                LEDS_SET(LED_NUM1);
            }
            else if ((switchesState & SWITCH_STATE_SW1) == 0 &&
                    (Button & BUTTON_EVENT_1DOWN)){
                LED_NUM2 = LED2;
                LEDS_SET(LED_NUM2);
            }
            if ((switchesState & SWITCH_STATE_SW1) == 1 &&
                    (Button & BUTTON_EVENT_2UP)) {
                LED_NUM3 = LED3;
                LEDS_SET(LED_NUM3);
            }
            else if ((switchesState & SWITCH_STATE_SW1) == 0 &&
                    (Button & BUTTON_EVENT_2DOWN)){
                LED_NUM4 = LED4;
                LEDS_SET(LED_NUM4);
            }
            if ((switchesState & SWITCH_STATE_SW1) == 1 &&
                    (Button & BUTTON_EVENT_3UP)) {
                LED_NUM5 = LED5;
                LEDS_SET(LED_NUM5);
            }
            else if ((switchesState & SWITCH_STATE_SW1) == 0 &&
                    (Button & BUTTON_EVENT_3DOWN)){
                LED_NUM6 = LED6;
                LEDS_SET(LED_NUM6);
            }
            if ((switchesState & SWITCH_STATE_SW1) == 1 &&
                    (Button & BUTTON_EVENT_4UP)) {
                LED_NUM7 = LED7;
                LEDS_SET(LED_NUM7);
            }
            else if ((switchesState & SWITCH_STATE_SW1) == 0 &&
                    (Button & BUTTON_EVENT_4DOWN)){
                LED_NUM8 = LED8;
                LEDS_SET(LED_NUM8);
            }
        prog = FALSE;
    }
}
/***************************************************************************************************
 * Your code goes in between this comment and the preceding one with asterisks
 **************************************************************************************************/

while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    Button = ButtonsCheckEvents();
    if (Button != BUTTON_EVENT_NONE) {
        prog = TRUE;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}