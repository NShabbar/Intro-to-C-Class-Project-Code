
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "BOARD.h"

ListItem *LinkedListNew(char *data) {
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

ListItem *LinkedListCreateAfter(ListItem *item, char *data) {
    struct ListItem *added_item = (struct ListItem*) malloc(sizeof (ListItem));
    if (added_item == NULL) {
        return NULL;
    }
    added_item ->data = data;
    added_item ->previousItem = item;
    added_item ->nextItem = item->nextItem;
    item->nextItem = added_item;
    return added_item;
}

char *LinkedListRemove(ListItem *item) {
    char *data = item->data;
    if (item == NULL) {
        return NULL;
    }
    if (item->nextItem != NULL) {
        item->nextItem->previousItem = item->previousItem;
    }
    if (item->previousItem != NULL) {
        item->previousItem->nextItem = item->nextItem;
        free(item);
    }

    return data;
}

int LinkedListSize(ListItem *list) {
    int count = 0;
    ListItem *head = LinkedListGetFirst(list);
    while (head != NULL) {
        count++;
        head = head->nextItem;
    }
    return count;
}

ListItem *LinkedListGetFirst(ListItem *list) {
    if (list == NULL) {
        return NULL;
    }
    while (list->previousItem != NULL) {
        list = list->previousItem;
    }
    return list;
}

ListItem *LinkedListGetLast(ListItem *list) {
    if (list == NULL) {
        return NULL;
    }
    while (list->nextItem != NULL) {
        list = list ->nextItem;
    }
    return list;
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem) {
    if (firstItem != NULL || secondItem != NULL) {
        char *swap = firstItem->data;
        firstItem->data = secondItem->data;
        secondItem->data = swap;
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int LinkedListPrint(ListItem *list) {
    ListItem *head;
    if (list == NULL) {
        return STANDARD_ERROR;
    }
    printf("[ ");
    for (head = LinkedListGetFirst(list); head != NULL;
            head = head->nextItem) {
        printf("%s ", (head->data));
    }
    printf("]");
    return SUCCESS;
}
