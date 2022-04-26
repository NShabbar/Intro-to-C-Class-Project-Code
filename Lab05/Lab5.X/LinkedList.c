
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "BOARD.h"

ListItem *LinkedListNew(char *data){
    ListItem *point;
    point = malloc(sizeof (ListItem));
    if (point == NULL) {
        return NULL;
    }
    point->previousItem = NULL;
    point->nextItem = NULL;
    point->data = data;
    return point;
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data){
    ListItem *newlist;
    newlist = LinkedListNew(data);
    if (newlist == NULL){
        return NULL;
    }
    if (item != NULL){
        if (item->nextItem != NULL){
            item->nextItem->previousItem = newlist;
            newlist->nextItem = item->nextItem;
            item->nextItem = newlist;
            newlist->previousItem = item;
        }
    }
    return newlist;
}

char *LinkedListRemove(ListItem *item){
    char *data = item->data;
    if (item == NULL){
        return NULL;
    }
    if (item->nextItem != NULL){
        item->nextItem->previousItem = item->previousItem;
        if (item->previousItem != NULL){
            item->previousItem->nextItem = item->nextItem;
            free(item);
        }
    }return data;
}