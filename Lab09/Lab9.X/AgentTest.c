/* 
 * File:   AgentTest.c
 * Author: Nadia Shabbar
 *
 * Created on May 23, 2022, 6:04 PM
 */

#include <stdio.h>
#include "Agent.h"
#include "BOARD.h"
#include "Message.h"
#include "Field.h"
#include "FieldOled.h"
#include "Negotiation.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Uart1.h"
#include "Buttons.h"
#include "CircularBuffer.h"
#include "Ascii.h"

int main() {
    AgentInit();
    BB_Event input;
    input.type = BB_EVENT_START_BUTTON;
    printf("Testing the AgentRun Function.\n");
    Message test_1 = AgentRun(input);
    if (test_1.type != MESSAGE_CHA) {
        printf("Test 1 failed.\n");
    } else {
        printf("Test 1 passed.\n");
    }
    input.type = BB_EVENT_CHA_RECEIVED;
    Message test_2 = AgentRun(input);
    if (test_2.type != MESSAGE_ACC) {
        printf("Test 2 failed.\n");
    } else if (test_2.type != MESSAGE_NONE) {
        printf("Test 2 failed.\n");
    } else {
        printf("Test 2 passed.\n");
    }
    input.type = BB_EVENT_ACC_RECEIVED;
    Message test_3 = AgentRun(input);
    if (test_3.type != MESSAGE_REV) {
        printf("Test 3 failed.\n");
    } else {
        printf("Test 3 passed.\n");
    }
    input.type = BB_EVENT_REV_RECEIVED;
    Message test_4 = AgentRun(input);
    if (test_4.type != MESSAGE_NONE) {
        printf("Test 4 failed.\n");
    } else if (test_4.type != MESSAGE_SHO) {
        printf("Test 4 failed.\n");
    } else {
        printf("Test 4 passed.\n");
    }
    input.type = BB_EVENT_RES_RECEIVED;
    Message test_5 = AgentRun(input);
    if (test_5.type != MESSAGE_NONE) {
        printf("Test 5 failed.\n");
    } else {
        printf("Test 5 passed.\n");
    }
    input.type = BB_EVENT_SHO_RECEIVED;
    Message test_6 = AgentRun(input);
    if (test_6.type != MESSAGE_RES) {
        printf("Test 6 failed.\n");
    } else {
        printf("Test 6 passed.\n");
    }
}

