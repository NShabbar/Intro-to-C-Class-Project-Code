//Written by Nadia Shabbar

#include <stdio.h>
#include <stdlib.h>
#include "Negotiation.h"
#include "BOARD.h"

#define SIXTEEN 16
#define TWO 2
#define HEX 0x01

static NegotiationData result;

NegotiationData NegotiationHash(NegotiationData secret) {
    result = (secret * secret) % PUBLIC_KEY;
    return result;
}

int NegotiationVerify(NegotiationData secret, NegotiationData commitment) {
    if (NegotiationHash(secret) == commitment) {
        return TRUE;
    } else {
        return FALSE;
    }
}

NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B) {
    NegotiationData Result = A ^ B;
    uint8_t i = 0, count = 0;

    for (i = 0; i < SIXTEEN; i++) {
        count += ((Result >> i) & HEX);
    }
    if (count % TWO) {
        return HEADS;
    } else {
        return TAILS;
    }
}

NegotiationData NegotiateGenerateAGivenB(NegotiationData B) {
    int count = 1;
    int cheat_code = 0;
    while (1) {
        count++;
        cheat_code = NegotiationHash(count);
        if (NegotiateCoinFlip(count, B) == HEADS && cheat_code == result) {
            break;
        }
    }
    return count;
}