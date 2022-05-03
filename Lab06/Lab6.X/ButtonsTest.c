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
#include "Oled.h"

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
uint8_t Button;

// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
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
    printf("Welcome to nshabbar's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);
    

    printf("Please press some buttons!\n");
    uint8_t status = BUTTON_EVENT_NONE;
    ButtonsInit();
    char Butt1[20] = "----";
    char Butt2[20] = "----";
    char Butt3[20] = "----";
    char Butt4[20] = "----";

    while (1) {
        if (Button == status) {
            printf("Event: 4:%s 3:%s 2:%s 1:%s\n", Butt4, Butt3, Butt2, Butt1);
        } else if (Button & BUTTON_EVENT_1DOWN) {
            strcpy(Butt1,"DOWN");
            printf("Event: 4:%s 3:%s 2:%s 1:%s\n", Butt4, Butt3, Butt2, Butt1);
        } else if (Button & BUTTON_EVENT_2DOWN) {
            strcpy(Butt2,"DOWN");
            printf("Event: 4:%s 3:%s 2:%s 1:%s\n", Butt4, Butt3, Butt2, Butt1);
        } else if (Button & BUTTON_EVENT_3DOWN) {
            strcpy(Butt3,"DOWN");
            printf("Event: 4:%s 3:%s 2:%s 1:%s\n", Butt4, Butt3, Butt2, Butt1);
        } else if (Button & BUTTON_EVENT_4DOWN) {
            strcpy(Butt4,"DOWN");
            printf("Event: 4:%s 3:%s 2:%s 1:%s\n", Butt4, Butt3, Butt2, Butt1);
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

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}