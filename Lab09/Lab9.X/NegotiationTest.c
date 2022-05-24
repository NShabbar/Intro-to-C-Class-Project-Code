/* 
 * File:   NegotiationTest.c
 * Author: Tristen Miller (trkmille@ucsc.edu)
 *
 * Created on May 23, 2022, 11:00 AM
 */
#include <stdio.h>
#include "BOARD.h"
#include "Negotiation.h"

int main()
{
    //Test NegotiationHash()
    {
        uint8_t hashTests=0;
        uint8_t totalHashTests=0;
        if (NegotiationHash(10) == 100) {
            hashTests++;
        } else {
            printf("NegotiationHash didn't produce expected result");
        }
        totalHashTests++;
        if (NegotiationHash(3) == 9) {
            hashTests++;
        } else {
            printf("NegotiationHash didn't produce expected result");
        }
        totalHashTests++;
        if (NegotiationHash(12345) == 43182) {
            hashTests++;
        } else {
            printf("NegotiationHash didn't produce expected result");
        }
        totalHashTests++;
        printf("NegotiationHash passed:(%d/%d)\n", hashTests, totalHashTests);
    }
    //Test NegotiationVerify()
    {
        uint8_t verifyTests=0;
        uint8_t totalVerifyTests=0;
        if(NegotiationVerify(12345,43182)){
            verifyTests++;
        }
        totalVerifyTests++;
        if(NegotiationVerify(3,9)){
            verifyTests++;
        }
        totalVerifyTests++;
        if(!NegotiationVerify(10,101)){
            verifyTests++;
        }else{
            printf("NegotiationVerify did not catch cheating!\n");
        }
        totalVerifyTests++;
        if(!NegotiationVerify(12345,43181)){
            verifyTests++;
        }else{
            printf("NegotiationVerify did not catch cheating!\n");
        }
        totalVerifyTests++;
        printf("NegotiationVerify() passed:(%d/%d)\n",verifyTests,totalVerifyTests);
    }
    //Tests NegotiateCoinFlip:
    {
        uint8_t coinTests=0;
        uint8_t totalCoinTests=0;
        if(NegotiateCoinFlip(0b0110,0b1001)==TAILS){
            coinTests++;
        }
        totalCoinTests++;
        if(NegotiateCoinFlip(0b1110,0b1111)==HEADS){
            coinTests++;
        }
        totalCoinTests++;
        printf("NegotiateCoinFlip() passed:(%d/%d)\n",coinTests,totalCoinTests);
    }
}
