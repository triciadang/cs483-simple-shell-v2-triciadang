#include "historyList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Test program for CS 483 PEX 1 - Part 1
 * Compile and run this to test your implementation
 * of the functions defined in historyList.h
 */

int main(void) {
    HistoryNodeType* listHeadPtr = NULL;
    char* zero = "zero";
    char* one = "one";
    char* two = "two";
    char* three = "three";

    listHeadPtr = listInsertTail(listHeadPtr, one);
    listHeadPtr = listInsertTail(listHeadPtr, two);
    listHeadPtr = listInsertTail(listHeadPtr, three);
    printf("listInsertTail and listPrint test:\n");
    listPrint(listHeadPtr);
    /* expected output:
    one
    two
    three
    */

    listHeadPtr = listInsertHead(listHeadPtr, zero);
    printf("\nlist_insert_head and listPrint test:\n");
    listPrint(listHeadPtr);
    /* expected output:
    zero
    one
    two
    three
    */

    listHeadPtr = listRemove(listHeadPtr, "one");
    printf("\nlist_remove test (middle):\n");
    listPrint(listHeadPtr);
    /* expected output:
    zero
    two
    three
    */

    listHeadPtr = listRemove(listHeadPtr, "three");
    printf("\nlist_remove test (tail):\n");
    listPrint(listHeadPtr);
    /* expected output:
    zero
    two
    */

    listHeadPtr = listRemove(listHeadPtr, "zero");
    printf("\nlist_remove test (head):\n");
    listPrint(listHeadPtr);
    /* expected output:
    two
    */

    listHeadPtr = listInsertHead(listHeadPtr, zero);
    listHeadPtr = listInsertN(listHeadPtr, one, 2);
    listHeadPtr = listInsertN(listHeadPtr, three, 4);
    printf("\nlistInsertN test:\n");
    listPrint(listHeadPtr);
    /* expected output:
    zero
    one
    two
    three
    */

    printf("\nlistGet test:\n");
    int i;
    for(i = 1; i < 5; i++) {
        printf("%d: %s\n", i, listGet(listHeadPtr, i));
    }
    /* expected output:
    1: zero
    2: one
    3: two
    4: three
    */

    printf("\nlistRemoveN test:\n");
    listRemoveN(listHeadPtr,2);
    listPrint(listHeadPtr);
    /* expected output:
    zero
    two
    three
    */

    printf("\nlistPrintN test:\n");
    listPrintN(listHeadPtr,2);
    /* expected output:
    two
    */

    listDestroy(listHeadPtr);
}