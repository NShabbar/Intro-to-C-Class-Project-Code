
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
    char *third = "R2D2";
    char *fourth = "8B";
    
    printf("Creating a new list.\n");
    struct ListItem *a = LinkedListNew(first);
    if (a->previousItem == NULL && a->data == first){
        printf("Success.\n");
    }
    
    printf("Adding new items.\n");
    struct ListItem *b = LinkedListCreateAfter(a, second);
    struct ListItem *c = LinkedListCreateAfter(b, third);
    if (b->nextItem == c && b->previousItem == a){
        printf("Success.\n");
    }
    else{
        printf("Failed.\n");
    }
    
    printf("Testing for list size.\n");
    struct ListItem *d = LinkedListCreateAfter(c, fourth);
    int result = LinkedListSize(d);
    int expected = 4;
    if (result == expected){
        printf("Success. 1/2\n");
    }
    else{
        printf("Failed.\n");
    }
    int result_1 = LinkedListSize(a);
    int expected_1 = 4;
    if (result_1 == expected_1){
        printf("Success. 2/2\n");
    }
    else{
        printf("Failed.\n");
    }
    
    printf("Testing for first item.\n");
    struct ListItem  *start = LinkedListGetFirst(a);
    if (start == a){
        printf("Success. 1/2\n");
    }
    else{
        printf("Failed.\n");
    }
    struct ListItem *two = LinkedListGetFirst(b);
    if (two == a){
        printf("Success. 2/2\n");
    }
    else{
        printf("Failed.\n");
    }
    
    printf("Testing for last item.\n");
    struct ListItem *end = LinkedListGetLast(c);
    if (end == d){
        printf("Success. 1/2\n");
    }
    else{
        printf("Failed.\n");
    }
    struct ListItem *end_2 = LinkedListGetLast(a);
    if (end_2 == d){
        printf("Success. 2/2\n");
    }
    else{
        printf("Failed.\n");
    }
    
    printf("Testing for printed list.\n");
    printf("Expected: [ %s, %s, %s, %s]\n", first, second, third, fourth);
    printf("Result: \n");
    LinkedListPrint(a);
    
    printf("\nTesting for swapped items. Swapping second and third items.\n");
    LinkedListSwapData(b, c);
    printf("Expected: [ %s, %s, %s, %s]\n", first, third, second, fourth);
    printf("Result: \n");
    LinkedListPrint(a);
    
    printf("\nTesting for removed items. Removing last item.\n");
    LinkedListRemove(d);
    printf("Expected: [ %s, %s, %s]\n", first, third, second);
    printf("Result: \n");
    LinkedListPrint(a);
    printf("\nRemoving item two in list.\n");
    LinkedListRemove(c);
    printf("Expected: [ %s, %s]\n", first, third);
    printf("Result: \n");
    LinkedListPrint(a);
}

