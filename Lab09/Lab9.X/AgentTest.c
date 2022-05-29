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

int main() {
    AgentInit();

    printf("Testing the AgentRun Function.\n");
    test_1 = AgentRun(BB_EVENT_START_BUTTON);
    if (test_1 != MESSAGE_CHA) {
        printf("Test 1 failed.\n");
    } else {
        printf("Test 1 passed.\n");
    }
    test_2 = AgentRun(BB_EVENT_CHA_RECEIVED);
    if (test_2 != MESSAGE_ACC) {
        printf("Test 2 failed.\n");
    } else if (test_2 != MESSAGE_NONE) {
        printf("Test 2 failed.\n");
    } else {
        printf("Test 2 passed.\n");
    }
    test_3 = AgentRun(BB_EVENT_ACC_RECEIVED);
    if (test_3 != MESSAGE_REV) {
        printf("Test 3 failed.\n");
    } else {
        printf("Test 3 passed.\n");
    }
    test_4 = AgentRun(BB_EVENT_REV_RECEIVED);
    if (test_4 != MESSAGE_NONE) {
        prinft("Test 4 failed.\n");
    } else if (test_4 != MESSAGE_SHO) {
        printf("Test 4 failed.\n");
    } else {
        printf("Test 4 passed.\n");
    }
    test_5 = AgentRun(BB_EVENT_RES_RECEIVED);
    if (test_5 != MESSAGE_NONE) {
        printf("Test 5 failed.\n");
    } else {
        printf("Test 5 passed.\n");
    }
    test_6 = AgentRun(BB_EVENT_SHO_RECEIVED);
    if (test_6 != MESSAGE_RES) {
        printf("Test 6 failed.\n");
    } else {
        printf("Test 6 passed.\n");
    }


    return (EXIT_SUCCESS);
}

