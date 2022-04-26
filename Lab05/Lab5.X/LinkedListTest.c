
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "BOARD.h"


int main() {

    BOARD_Init();
    printf("\nWelcome to nshabbar's LinkedListTest.c, compiled on %s %s.\n\n", 
            __DATE__, __TIME__);
    
    char *first = "2B";
    char *second = "CP30";
    char *third = "R2D2"";
    char *last = "8008";
    
    printf("Creating a new list.\n");
    struct ListItem = *a = LinkedListNew(first);
    if (a->previousItem == NULL && a->data == NULL){
        printf("Success.\n");
    }
    
    printf("Adding new items.\n");
    struct ListItem = *b = LinkedListCreateAfter(a, second);
    struct ListItem = *c = LinkedListCreateAfter(b, third);
    if (b->nextItem == c && b->previousItem == a){
        printf("Success.\n");
    }
    
    printf("Testing for list size.\n");
    struct ListItem = *d = LinkedListCreateAfter(c, last);
    int result = LinkedListSize(d);
    int expected = 4;
    if (result == expected){
        printf("Success. 1/2\n");
    }
    int result_1 = LinkedListSize(a);
    int expected_1 = 4;
    if (result_1 == expected_1){
        printf("Success. 2/2\n");
    }
    
    
}

