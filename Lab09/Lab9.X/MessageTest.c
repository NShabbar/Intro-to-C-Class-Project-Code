/* 
 * File:   MessageTest.c
 * Author: Tristen Miller (trkmille@ucsc.edu)
 *
 * Created on May 23, 2022, 11:00 AM
 */
#include<string.h>
#include <stdio.h>
#include "Message.h"
#include "BOARD.h"
#include "BattleBoats.h"
#include "Field.h"

int main()
{
    //Test CalculateChecksum:
    {
        uint8_t calcTests = 0;
        uint8_t totalCalcTests = 0;
        if (Message_CalculateChecksum("This is a message") == 0x16) {//Found from http://www.hhhh.org/wiml/proj/nmeaxor.html
            calcTests++;
        }
        totalCalcTests++;
        if (Message_CalculateChecksum("REALLY LONG AND LARGE MESSAGE CHECKSUM GOES HERE PLEASE AND THANKS") == 0x1F) {
            calcTests++;
        }
        totalCalcTests++;
        printf("Message_CalculateChecksum passed:(%d/%d)\n", calcTests, totalCalcTests);
    }
    //Test Message_ParseMessage():
    {
        uint8_t parseTests = 0;
        uint8_t totalParseTests = 0;
        BB_Event event;
        if (!Message_ParseMessage("ACC, this is a message", "7B", &event)) {
            parseTests++;
        } else {
            printf("Message_ParseMessage Failed to catch invalid message format\n");
        }

        totalParseTests++;
        if (Message_ParseMessage("SHO,5,6", "54", &event)) {
            if (event.type == BB_EVENT_SHO_RECEIVED && event.param0 == 5 && event.param1 == 6) {
                parseTests++;
            } else {
                printf("test2 failed\n");
            }
        } else {
            printf("test2 failed\n");
        }
        totalParseTests++;
        if (Message_ParseMessage("CHA,100", "57", &event)) {
            if (event.type == BB_EVENT_CHA_RECEIVED && event.param0 == 100) {
                parseTests++;
            } else {
                printf("test3 failed\n");
            }
        } else {
            printf("test3 failed\n");
        }

        totalParseTests++;
        if (Message_ParseMessage("REV,122", "5c", &event)) {
            if (event.type == BB_EVENT_REV_RECEIVED && event.param0 == 122) {
                parseTests++;
            } else {
                printf("test4 failed\n");
            }
        } else {
            printf("test4 failed\n");
        }
        totalParseTests++;
        if (Message_ParseMessage("RES,5,7,1", "69", &event)) {
            if (event.type == BB_EVENT_RES_RECEIVED && event.param0 == 5 && event.param1 == 7 && event.param2 == RESULT_HIT) {
                parseTests++;
            } else {
                printf("test5 failed\n");
            }
        } else {
            printf("test5 failed\n");
        }
        totalParseTests++;

        if (Message_ParseMessage("RES,1,0,3", "5A", &event)) {
            if (event.type == BB_EVENT_RES_RECEIVED && event.param0 == 1 && event.param1 == 0 && event.param2 == 3) {
                parseTests++;
            }else{
                printf("test6 Failed\n");
            }
        }else{
            printf("test6 failed\n");
        }
        totalParseTests++;
        if (!Message_ParseMessage("RES,1,0,3", "5B", &event)) {
            parseTests++;
        } else {
            printf("Message_ParseMessage did not catch non-matching Checksum\n");
        }
        totalParseTests++;
        if (!Message_ParseMessage("RES,1,0,3", "5AA", &event)) {
            parseTests++;
        } else {
            printf("Message_ParseMessage did not catch invalid Checksum\n");
        }
        totalParseTests++;
        printf("Message_ParseMessage passed: (%d/%d)\n", parseTests, totalParseTests);

    }
    //testing Message_Encode()
    {
        uint8_t encodeTests = 0;
        uint8_t totalEncodeTests = 0;
        char output[MESSAGE_MAX_LEN];
        Message message;
        message.type = MESSAGE_CHA;
        message.param0 = 5;
        Message_Encode(output, message);
        char expected[] = "$CHA,5*53\n";
        if (strcmp(output, expected) == 0) {
            encodeTests++;
        }
        totalEncodeTests++;

        message.type = MESSAGE_RES;
        message.param0 = 5;
        message.param1 = 8;
        message.param2 = RESULT_HIT;

        Message_Encode(output, message);
        char expected1[] = "$RES,5,8,1*54\n";
        if (strcmp(output, expected1) == 0) {
            encodeTests++;
        }
        totalEncodeTests++;

        message.type = MESSAGE_REV;
        message.param0 = 21344; //This also makes sure that it doesn't do anything with extra params
        char exptected2[] = "$REV,21344*5D\n";
        Message_Encode(output, message);
        if (strcmp(output, exptected2) == 0) {
            encodeTests++;
        }
        totalEncodeTests++;

        message.type = MESSAGE_SHO;
        message.param0 = 2;
        message.param1 = 1;
        char expected3[] = "$SHO,2,1*57\n";
        Message_Encode(output, message);
        if (strcmp(output, expected3) == 0) {
            encodeTests++;
        }
        totalEncodeTests++;

        message.type = MESSAGE_RES;
        message.param0 = 2;
        message.param1 = 1;
        message.param2 = RESULT_HIT;
        char expected4[] = "$RES,2,1,1*5A\n";
        int test = Message_Encode(output, message);
        if (strcmp(output, expected4) == 0) {
            encodeTests++;
        }
        totalEncodeTests++;
        if (test == 14) {
            encodeTests++;
        }
        totalEncodeTests++;
        printf("Message_Encode passed:(%d/%d)\n", encodeTests, totalEncodeTests);
    }
    //Testing Message_Decode
    {
        uint8_t decodeTests = 0;
        uint8_t totalDecodeTests = 0;
        BB_Event event;
        char test[] = "$RES,2,1,1*5A";
        for (int i = 0; i <= strlen(test); i++) {
            Message_Decode(test[i], &event);
        }
        if (event.type == BB_EVENT_RES_RECEIVED) {
            decodeTests++;
        } else {
            printf("Did not decode to message type BB_EVENT_RES_RECEIVED\n");
        }
        totalDecodeTests++;
        char test2[] = "$REV,3212*6F";
        for (int i = 0; i != strlen(test2); i++) {
            Message_Decode(test2[i], &event);
        }
        if (event.type == BB_EVENT_REV_RECEIVED) {
            decodeTests++;
        } else {
            printf("Did not decode to message type BB_EVENT_REV_RECEIVED\n");
        }
        totalDecodeTests++;
        printf("Message_Decode passed:(%d/%d)\n", decodeTests, totalDecodeTests);
    }

}