#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "BattleBoats.h"
#include "BOARD.h"
#include "Message.h"

typedef enum {
    start, //This is 0
    pl, //This is 1
    cs, //This is 2
} part;

static part mess_part = start;
static char decode_cs[MESSAGE_CHECKSUM_LEN]; //Checksum
static char decode_pl[MESSAGE_MAX_PAYLOAD_LEN]; //Payload
static int decode_count = 0;
static char encode_pl[MESSAGE_MAX_PAYLOAD_LEN]; //Payload
static uint8_t encode_cs; //Checksum

uint8_t Message_CalculateChecksum(const char* payload) {
    uint8_t checksum = 0;
    for (int i = 0; i != strlen(payload); i++) {
        checksum ^= payload[i];
    }
    return checksum; //Might have to add a null character to the end.
}

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event) {
    char *token;
    int pl_part = 0;

    message_event -> param0 = 0;
    message_event -> param1 = 0;
    message_event -> param2 = 0;
    strcpy(encode_pl, payload);
    token = strtok(encode_pl, ",");

    while (token != NULL) {
            if (strlen(checksum_string) != 2) {
                return STANDARD_ERROR;
            }
            if (strcmp(token, "CHA") == 0  && Message_CalculateChecksum(payload) == atoi(checksum_string)) { //Search for CHA in token.
                pl_part = 1;
                message_event -> type = BB_EVENT_CHA_RECEIVED;
            } else if (strcmp(token, "ACC") == 0  && Message_CalculateChecksum(payload) == atoi(checksum_string)) { //Search for ACC in token.
                pl_part = 1;
                message_event -> type = BB_EVENT_ACC_RECEIVED;
            } else if (strcmp(token, "REV") == 0  && Message_CalculateChecksum(payload) == atoi(checksum_string)) { //Search for REV in token.
                pl_part = 1;
                message_event -> type = BB_EVENT_REV_RECEIVED;
            } else if (strcmp(token, "SHO") == 0  && Message_CalculateChecksum(payload) == atoi(checksum_string)) { //Search for SHO in token.
                pl_part = 1;
                message_event -> type = BB_EVENT_SHO_RECEIVED;
            } else if (strcmp(token, "RES") == 0  && Message_CalculateChecksum(payload) == atoi(checksum_string)) { //Search for RES in token.
                pl_part = 1;
                message_event -> type = BB_EVENT_RES_RECEIVED;
            } else {
                if (pl_part < 1) {
                    message_event->type = BB_EVENT_ERROR;
                    return STANDARD_ERROR;
                } else if (pl_part == 1) {
                    message_event->param0 = atoi(token); //converts string to int.
                    pl_part = 2;
                } else if (pl_part == 2) {
                    message_event->param1 = atoi(token); //converts string to int.
                    pl_part = 3;
                } else if (pl_part == 3) {
                    message_event->param2 = atoi(token); //converts string to int.
                    pl_part = 4;
                } else {
                    message_event->type = BB_EVENT_ERROR;
                    return STANDARD_ERROR;
                }
            }
        token = strtok(NULL, ",");
    }
    return SUCCESS;
}

int Message_Encode(char *message_string, Message message_to_encode) {
    if (message_to_encode.type == MESSAGE_CHA) {
        sprintf(encode_pl, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);
    } else if (message_to_encode.type == MESSAGE_ACC) {
        sprintf(encode_pl, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);
    } else if (message_to_encode.type == MESSAGE_REV) {
        sprintf(encode_pl, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);
    } else if (message_to_encode.type == MESSAGE_SHO) {
        sprintf(encode_pl, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, message_to_encode.param1);
    } else if (message_to_encode.type == MESSAGE_RES) {
        sprintf(encode_pl, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, message_to_encode.param1, message_to_encode.param2);
    }

    encode_cs = Message_CalculateChecksum(encode_pl);
    sprintf(message_string, MESSAGE_TEMPLATE, encode_pl, encode_cs);
    return strlen(message_string);
}

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event) {
    switch (mess_part) {
        case start:
            if (char_in == '$') { // Is start '$' for start of message?
                mess_part = pl;
            } else {
                decoded_message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR;
            }
            break;
        case pl:
            if ((char_in >= 48 && char_in <= 57) || (char_in >= 65 && char_in <= 90) || char_in == 44) { //Is Payload in either of these ranges?
                decode_pl[decode_count] = char_in;
                decode_count++;
            } else if (char_in == '*') { //Is Payload '*' for end?
                mess_part = cs;
                decode_count = 0;
            } else {
                decode_count = 0;
                decoded_message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR;
            }
            break;
        case cs:
            if ((char_in >= 48 && char_in <= 57) || (char_in >= 65 && char_in <= 70)) { //Is Checksum in these ranges?
                decode_cs[decode_count] = char_in;
                decode_count++;
            } else if (char_in == '\n') { //Checksum is newline
                decode_count = 0;
                mess_part = start;
                Message_ParseMessage(decode_pl, decode_cs, decoded_message_event);
            } else {
                decode_count = 0;
                decoded_message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR;
            }
            break;
    }
    return SUCCESS;
}
