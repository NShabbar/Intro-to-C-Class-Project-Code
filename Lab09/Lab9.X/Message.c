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
        if (strcmp(token, "CHA") == 0) {
            pl_part = 1;
            message_event -> type = BB_EVENT_CHA_RECEIVED;
        } else if (strcmp(token, "ACC") == 0) {
            pl_part = 1;
            message_event -> type = BB_EVENT_ACC_RECEIVED;
        } else if (strcmp(token, "REV") == 0) {
            pl_part = 1;
            message_event -> type = BB_EVENT_REV_RECEIVED;
        } else if (strcmp(token, "SHO") == 0) {
            pl_part = 1;
            message_event -> type = BB_EVENT_SHO_RECEIVED;
        } else if (strcmp(token, "RES") == 0) {
            pl_part = 1;
            message_event -> type = BB_EVENT_RES_RECEIVED;
        }
    }
}