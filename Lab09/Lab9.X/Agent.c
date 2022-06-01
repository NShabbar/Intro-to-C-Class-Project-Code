/* 
 * File:   AgentTest.c
 * Author: Tristen Miller (trkmille@ucsc.edu)
 *
 * Created on May 23, 2022, 11:00 AM
 */
#include <stdio.h>
#include "Agent.h"
#include "BOARD.h"
#include "Message.h"
#include "Field.h"
#include "FieldOled.h"
#include "Negotiation.h"
#include "Oled.h"
#include "BattleBoats.h"

#define SIXTEEN_BITS 0xFFFF

enum {
    Win,
    Loss
};
static uint8_t bufferClear = TRUE;
static uint8_t winner;
static unsigned int turnCounter;
static AgentState agentState;
static NegotiationData A;
static NegotiationData Asharp;
static Message message;
static Field myField;
static Field oppField;
static NegotiationData B;
static uint8_t cheatingFlag;

void AgentInit(void)
{
    agentState = AGENT_STATE_START;
    turnCounter = 0;
    A = 0;
    Asharp = 0;
    message.type = MESSAGE_NONE;
    cheatingFlag = FALSE;

}

Message AgentRun(BB_Event event)
{
    char disp[OLED_DRIVER_BUFFER_SIZE];
    GuessData result;
    if (event.type == BB_EVENT_RESET_BUTTON) {
        AgentInit();

    }
    if (event.type == BB_EVENT_MESSAGE_SENT) {
        bufferClear = TRUE;
    }
    if (bufferClear == TRUE) {
        switch (agentState) {
        case AGENT_STATE_START:
            OledClear(OLED_COLOR_BLACK);
            OledDrawString("START\nWait for a challenge\nOr press BTN4 to send a challenge");
            OledUpdate();
            if (event.type == BB_EVENT_START_BUTTON) {
                A = rand() & SIXTEEN_BITS; //Get a 16 bit number for A
                Asharp = NegotiationHash(A);
                message.type = MESSAGE_CHA;
                message.param0 = Asharp;
                FieldInit(&myField, &oppField);
                FieldAIPlaceAllBoats(&myField);
                agentState = AGENT_STATE_CHALLENGING;
                bufferClear = FALSE;
                sprintf(disp, "Challenging\n%d=A\n%d=hash_A", A, Asharp);
                OledClear(OLED_COLOR_BLACK);
                OledDrawString(disp);
                OledUpdate();
                return message;
            } else if (event.type == BB_EVENT_EAST_BUTTON) {
                cheatingFlag = TRUE;
                A = rand() & SIXTEEN_BITS; //Get a 16 bit number for A, going to be replaced later
                Asharp = NegotiationHash(A);
                message.type = MESSAGE_CHA;
                message.param0 = Asharp;
                FieldInit(&myField, &oppField);
                FieldAIPlaceAllBoats(&myField);
                agentState = AGENT_STATE_CHALLENGING;
                bufferClear = FALSE;
                sprintf(disp, "Cheating\n\?\?\?=A\n%d=hash_A", Asharp);
                OledClear(OLED_COLOR_BLACK);
                OledDrawString(disp);
                OledUpdate();

            } else if (event.type == BB_EVENT_CHA_RECEIVED) {

                B = rand() & SIXTEEN_BITS;
                message.type = MESSAGE_ACC;
                message.param0 = B;
                Asharp = event.param0;
                sprintf(disp, "Accepting\n%d=hash_a\n%d=B", Asharp, B);
                OledClear(OLED_COLOR_BLACK);
                OledDrawString(disp);
                OledUpdate();
                FieldInit(&myField, &oppField);
                FieldAIPlaceAllBoats(&myField);
                agentState = AGENT_STATE_ACCEPTING;
                bufferClear = FALSE;
                return message;
            }
            break;
        case AGENT_STATE_CHALLENGING:
            if (event.type == BB_EVENT_ACC_RECEIVED) {
                B = event.param0;
                if(cheatingFlag==TRUE){
                    A=NegotiateGenerateAGivenB(B);
                    cheatingFlag=FALSE;
                }
                message.type = MESSAGE_REV;
                message.param0 = A;
                
                NegotiationOutcome outcome = NegotiateCoinFlip(A, B);
                if (outcome == HEADS) {
                    FieldOledDrawScreen(&myField, &oppField, FIELD_OLED_TURN_MINE, turnCounter);
                    agentState = AGENT_STATE_WAITING_TO_SEND;
                } else if (outcome == TAILS) {
                    FieldOledDrawScreen(&myField, &oppField, FIELD_OLED_TURN_THEIRS, turnCounter);
                    agentState = AGENT_STATE_DEFENDING;
                }
                bufferClear = FALSE;
                return message;


            }
            break;
        case AGENT_STATE_ACCEPTING:


            if (event.type == BB_EVENT_REV_RECEIVED) {
                if (NegotiationVerify(event.param0, Asharp)) {
                    NegotiationOutcome outcome = NegotiateCoinFlip(Asharp, B);
                    if (outcome == HEADS) {
                        message.type = MESSAGE_NONE;
                        agentState = AGENT_STATE_DEFENDING;
                        FieldOledDrawScreen(&myField, &oppField, FIELD_OLED_TURN_THEIRS, turnCounter);

                    } else if (outcome == TAILS) {
                        agentState = AGENT_STATE_ATTACKING;
                        message.type = MESSAGE_SHO;
                        GuessData shot = FieldAIDecideGuess(&oppField);
                        message.param0 = shot.row;
                        message.param1 = shot.col;
                        FieldOledDrawScreen(&myField, &oppField, FIELD_OLED_TURN_MINE, turnCounter);
                    }
                } else {
                    message.type = BB_EVENT_ERROR;
                }
                bufferClear = FALSE;
                return message;
            }

            break;
        case AGENT_STATE_ATTACKING:
            if (event.type == BB_EVENT_RES_RECEIVED) {
                GuessData result;
                result.row = event.param0;
                result.col = event.param1;
                result.result = event.param2;
                FieldUpdateKnowledge(&oppField, &result);
                FieldOledDrawScreen(&myField, &oppField, FIELD_OLED_TURN_MINE, turnCounter);
                if (FieldGetBoatStates(&oppField) == 0) {
                    agentState = AGENT_STATE_END_SCREEN;
                    winner = Win;
                } else {
                    agentState = AGENT_STATE_DEFENDING;
                }
                message.type = MESSAGE_NONE;
                // bufferClear = FALSE;
                return message;

            }
            break;
        case AGENT_STATE_DEFENDING:
            if (event.type == BB_EVENT_SHO_RECEIVED) {

                result.row = event.param0;
                result.col = event.param1;

                FieldRegisterEnemyAttack(&myField, &result);
                FieldOledDrawScreen(&myField, &oppField, FIELD_OLED_TURN_THEIRS, turnCounter);
                if (FieldGetBoatStates(&myField) == 0) {
                    agentState = AGENT_STATE_END_SCREEN;
                    winner = Loss;
                } else {
                    agentState = AGENT_STATE_WAITING_TO_SEND;
                }
                message.type = MESSAGE_RES;
                message.param0 = result.row;
                message.param1 = result.col;
                message.param2 = result.result;
                bufferClear = FALSE;

                return message;

            }
            break;
        case AGENT_STATE_WAITING_TO_SEND:

            turnCounter++;
            GuessData guess = FieldAIDecideGuess(&oppField);
            message.type = MESSAGE_SHO;
            message.param0 = guess.row;
            message.param1 = guess.col;
            agentState = AGENT_STATE_ATTACKING;
            bufferClear = FALSE;
            return message;


            break;
        case AGENT_STATE_END_SCREEN:
            switch (winner) {
            case Win:
                OledDrawString("VICTORY!");
                break;
            case Loss:
                OledDrawString("Better luck next time");


                break;
            }
            OledClear(OLED_COLOR_BLACK);
            OledUpdate();
            message.type = MESSAGE_NONE;
            return message;

        case AGENT_STATE_SETUP_BOATS:
            //in case we decide to do the EC; also to remove a compile warning
            message.type = MESSAGE_ERROR;
            return message;
            break;

        }

    }
    message.type = MESSAGE_NONE;
    return message;
}

AgentState AgentGetState(void)
{
    return agentState;
}

void AgentSetState(AgentState newState)
{
    agentState = newState;
}
