// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Oled.h"

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

struct adc_result {
    uint8_t event;
    uint16_t voltage;
};

static struct adc_result adc_res;

// **** Define global, module-level, or external variables here ****
#define WINDOW 5
uint16_t avg;
float percentage;
uint16_t voltage_data;
uint16_t total;

#define MAX 1023
uint16_t maximum = 100;
char string[100];

// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Enable interrupts for the ADC
    IPC6bits.AD1IP = 2;
    IPC6bits.AD1IS = 0;
    IEC1bits.AD1IE = 1;

    // Set B2 to an input so AN2 can be used by the ADC.
    TRISBbits.TRISB2 = 1;

    // Configure and start the ADC
    AD1CHSbits.CH0SA = 2; // add B2 to the mux
    AD1PCFGbits.PCFG2 = 0; // add b2 to the ADC
    AD1CSSLbits.CSSL2 = 1; // and add b2 to the scanner

    AD1CON1 = 0; // start with 0
    AD1CON1bits.SSRC = 0b111; // auto conversion
    AD1CON1bits.ASAM = 1; // auto sample

    AD1CON2 = 0; // start with 0
    AD1CON2bits.SMPI = 7; // one interrupt per 8 samples

    AD1CON3 = 0; // start with 0
    AD1CON3bits.SAMC = 29; // long sample time
    AD1CON3bits.ADCS = 50; // long conversion time

    AD1CON1bits.ADON = 1; // and finally turn it on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to nshabbar's lab6 part3 (bounce_adc).  Compiled on %s %s.\n", __TIME__, __DATE__);

    OledInit();
    while (1) {
        if (adc_res.event == TRUE) {
            float percentage_temp = adc_res.voltage; //converting to float.
            percentage = (percentage_temp / MAX) * 100;
            sprintf(string, "The Potentiometer's Value is:\n Volt: %d \n "
                    "Percent: %3.1f ", adc_res.voltage, percentage);
            OledDrawString(string); //to show on the oled screen
            OledUpdate();
            adc_res.event = FALSE; //makes event false
        }
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the ADC1 peripheral. It will trigger whenever a new ADC reading is available
 * in the ADC buffer SFRs, ADC1BUF0 - ADC1BUF7.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_ADC_VECTOR, ipl2auto) AdcHandler(void) {
    // Clear the interrupt flag.
    IFS1bits.AD1IF = 0;

    total = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4
            + ADC1BUF5 + ADC1BUF6 + ADC1BUF7);
    avg = (total / 8);

    if (avg - adc_res.voltage > WINDOW || adc_res.voltage - avg > WINDOW) {
        adc_res.event = TRUE;
        adc_res.voltage = avg;
    }
}