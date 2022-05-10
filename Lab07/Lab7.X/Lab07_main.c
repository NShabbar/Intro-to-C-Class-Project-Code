// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Ascii.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

//My User Library
#include "Adc.h"
#include "Buttons.h"
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"


// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)
#define WINDOW 5
#define addTEMP 300
#define DEFAULT_TEMP 350
#define LONGPRESS 3
#define LEDSOFF 0x00
#define LEDSON 0xFF
#define EIGHT 8


// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

//Making an OvenMode for broil, bake, toast.

typedef enum {
    BAKE, TOAST, BROIL
} OvenMode;

typedef struct {
    OvenState state;
    //add more members to this struct
    OvenMode Mode;
    uint16_t CookINIT;
    uint16_t Temperature;
    uint16_t CookTimeRem;
} OvenData;

// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****


// **** Put any helper functions here ****
static OvenData Oven;
static uint16_t TempChng = 0;
static uint16_t count = 0;
static uint16_t stor;
static uint8_t ADC_change = 0;
static uint32_t adc_val;
static uint16_t MaxTemp = 555;
static uint8_t Ticker = 0;
static uint16_t ButtonEvent;
static uint16_t TimePassed;

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData) {
    //update OLED here
    char stringMain[100];
    switch (ovenData.Mode) {
        case BAKE:
            if (ovenData.state == COOKING) {
                sprintf(stringMain, "|%s%s%s%s|   Mode: Bake\n"
                        "|    |   Time: %d:%02d\n"
                        "|----|   Temp: 500%sF\n"
                        "|%s%s%s%s|", OVEN_TOP_ON,
                        OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON,
                        (ovenData.CookTimeRem / WINDOW) / 60,
                        (ovenData.CookTimeRem / WINDOW) % 60,
                        DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF,
                        OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
            } else if (ovenData.state == SETUP) {
                if (!TempChng) {
                    sprintf(stringMain, "|%s%s%s%s|   Mode: Bake\n"
                            "|    |   Time: %d:%02d\n"
                            "|----| > Temp: 500%sF\n|%s%s%s%s|", OVEN_TOP_OFF,
                            OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF,
                            (ovenData.CookTimeRem / WINDOW) / 60,
                            (ovenData.CookTimeRem / WINDOW) % 60,
                            DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF,
                            OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
                } else {
                    sprintf(stringMain, "|%s%s%s%s|   Mode: Bake\n"
                            "|    |   Time: %d:%02d\n"
                            "|----|   Temp: 500%sF\n"
                            "|%s%s%s%s|", OVEN_TOP_OFF,
                            OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF,
                            (ovenData.CookTimeRem / WINDOW) / 60,
                            (ovenData.CookTimeRem / WINDOW) % 60,
                            DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF,
                            OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
                }
            }
            break;
        case TOAST:
            if (ovenData.state == COOKING) {
                sprintf(stringMain, "|%s%s%s%s|   Mode: Toast\n"
                        "|    |   Time: %d:%02d\n"
                        "|----|   Temp: 500%sF\n"
                        "|%s%s%s%s|", OVEN_TOP_ON,
                        OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON,
                        (ovenData.CookTimeRem / WINDOW) / 60,
                        (ovenData.CookTimeRem / WINDOW) % 60,
                        DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF,
                        OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
            } else {
                sprintf(stringMain, "|%s%s%s%s|   Mode: Toast\n"
                        "|    |   Time: %d:%02d\n"
                        "|----|   Temp: %sF\n|%s%s%s%s|", OVEN_TOP_OFF,
                        OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF,
                        (ovenData.CookTimeRem / WINDOW) / 60,
                        (ovenData.CookTimeRem / WINDOW) % 60,
                        DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF,
                        OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
            }
            break;
        case BROIL:
            if (ovenData.state == COOKING) {
                sprintf(stringMain, "|%s%s%s%s|   Mode: Broil\n"
                        "|    |   Time: %d:%02d\n"
                        "|----|   Temp: 500%sF\n"
                        "|%s%s%s%s|", OVEN_TOP_ON,
                        OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON,
                        (ovenData.CookTimeRem / WINDOW) / 60,
                        (ovenData.CookTimeRem / WINDOW) % 60,
                        DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF,
                        OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
            } else {
                sprintf(stringMain, "|%s%s%s%s|   Mode: Broil\n"
                        "|    |   Time: %d:%02d\n"
                        "|----|   Temp: 500%sF\n"
                        "|%s%s%s%s|", OVEN_TOP_OFF,
                        OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF,
                        (ovenData.CookTimeRem / WINDOW) / 60,
                        (ovenData.CookTimeRem / WINDOW) % 60,
                        DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF,
                        OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
            }
            break;
    }
    OledClear(OLED_COLOR_BLACK);
    OledDrawString(stringMain);
    OledUpdate();
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void) {
    //write your SM logic here.
    switch (Oven.state) {
        case SETUP:
            if (ADC_change) {
                adc_val - (AdcRead() >> 2) + 1;
                if (TempChng) {
                    Oven.Temperature = adc_val + addTEMP;
                    if (Oven.Temperature > MaxTemp) {
                        Oven.Temperature = MaxTemp;
                    } else {
                        Oven.CookINIT = adc_val * WINDOW;
                        Oven.CookTimeRem = Oven.CookINIT;
                    }
                    updateOvenOLED(Oven);
                }
            }
            if (ButtonEvent & BUTTON_EVENT_3DOWN) {
                stor = count;
                Oven.state = SELECTOR_CHANGE_PENDING;
            }
            if (ButtonEvent & BUTTON_EVENT_4DOWN) {
                stor = count;
                updateOvenOLED(Oven);
                Oven.state = COOKING;
                LEDS_SET(LEDSON);
            }
            break;
        case SELECTOR_CHANGE_PENDING:
            if (ButtonEvent & BUTTON_EVENT_3UP) {
                TimePassed = count - stor;
                if (TimePassed < LONGPRESS) {
                    if (Oven.Mode == 2) {
                        Oven.Mode = 0;
                    } else {
                        Oven.Mode++;
                    }
                } else if (Oven.Mode == BAKE && TimePassed >= LONGPRESS) {
                    if (TempChng == 1) {
                        TempChng = 0;
                    } else {
                        TempChng = 1;
                    }
                }
                Oven.state = SETUP;
            }
            updateOvenOLED(Oven);
            break;
        case COOKING:
            if (Ticker) {
                Oven.CookTimeRem--;
                updateOvenOLED(Oven);
                uint32_t NumLED = (Oven.CookTimeRem / (Oven.CookINIT / EIGHT))
                        + 1;
                LEDS_SET(LEDSON << (EIGHT - NumLED));
                if (Oven.CookTimeRem == 0) {
                    Oven.CookTimeRem = Oven.CookINIT;
                    LEDS_SET(LEDSOFF);
                    Oven.state = SETUP;
                }
            }
        case RESET_PENDING:
            if (Ticker) {
                Oven.CookTimeRem -= 1;
                if (Oven.CookTimeRem > 0) {
                    updateOvenOLED(Oven);
                } else {
                    Oven.CookTimeRem = Oven.CookINIT;
                    LEDS_SET(LEDSOFF);
                }
            }
            if (ButtonEvent & BUTTON_EVENT_4UP) {
                Oven.state = COOKING;
            } else {
                TimePassed = count - stor;
                if (TimePassed >= LONGPRESS) {
                    Oven.state = SETUP;
                    updateOvenOLED(Oven);
                    LEDS_SET(LEDSOFF);
                }
            }
            break;
    }
}

int main() {
    BOARD_Init();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    T2CON = 0;
    T2CONbits.TCKPS = 0b100;
    PR2 = BOARD_GetPBClock() / 16 / 100;
    T2CONbits.ON = 1;

    IFS0bits.T2IF = 0;
    IPC2bits.T2IP = 4;
    IPC2bits.T2IS = 0;
    IEC0bits.T2IE = 1;

    T3CON = 0;
    T3CONbits.TCKPS = 0b111;
    PR3 = BOARD_GetPBClock() / 256 / 5;
    T3CONbits.ON = 1;

    IFS0bits.T3IF = 0;
    IPC3bits.T3IP = 4;
    IPC3bits.T3IS = 0;
    IEC0bits.T3IE = 1;

    printf("Welcome to nshabbar's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    ButtonsInit();
    AdcInit();
    OledInit();
    LEDS_INIT();
    Oven.state = SETUP;
    Oven.Mode = BAKE;
    Oven.Temperature = DEFAULT_TEMP;
    Oven.CookINIT = 1;
    updateOvenOLED(Oven);

    while (1) {
        // Add main loop code here:
        if (ButtonEvent || Ticker || ADC_change) {
            // check for events
            // on event, run runOvenSM()
            runOvenSM();
            // clear event flags
            ButtonEvent = BUTTON_EVENT_NONE;
            Ticker = FALSE;
            ADC_change = 0;
        }
    };
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //add event-checking code here
    count += 1;
    Ticker = TRUE;
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //add event-checking code here
    ADC_change = AdcChanged();
    ButtonEvent = ButtonsCheckEvents();
}