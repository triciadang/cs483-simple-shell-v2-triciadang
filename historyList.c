// Your implementation of the functions defined in historyList.h goes here
#include <malloc.h>
#include "historyList.h"

/* listInsertTail: create a new node at the end of the linked list
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data to be stored in the new node
   Return: a pointer to the head of the linked list */
HistoryNodeType* listInsertTail(HistoryNodeType* headNode, char* data){
    HistoryNodeType* temp_ptr = headNode;
    HistoryNodeType* new_node = malloc(sizeof(HistoryNodeType));
    new_node->data = data;
    HistoryNodeType* prev_ptr = NULL;

    //if empty list
    if (headNode == NULL){
        headNode = new_node;
    }

    else {
        while (temp_ptr != NULL) {
            prev_ptr = temp_ptr;
            temp_ptr = temp_ptr->next;
        }

        prev_ptr->next = new_node;
    }

    return headNode;

}

/* listInsertHead: create a new node and insert it at the head of the linked
    list
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data to be stored in the new node
   Return: a pointer to the new head of the linked list */
HistoryNodeType* listInsertHead(HistoryNodeType* headNode, char* data){
    HistoryNodeType* new_node = malloc(sizeof(HistoryNodeType));
    new_node->data = data;

    //if empty list
    if (headNode->data == NULL){
        headNode = new_node;
        return headNode;
    }

    else{
        new_node->next = headNode;
        return new_node;
    }
}

/* listInsertN: create a new node and insert it at the <n>th position,
    where the head is at position 1
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data to be stored in the new node
   - int: the position in which to insert the new node
   Return: a pointer to the head of the linked list */
HistoryNodeType* listInsertN(HistoryNodeType* headNode, char* data, int position){
    HistoryNodeType* temp_ptr = headNode;
    HistoryNodeType* new_node = malloc(sizeof(HistoryNodeType));
    new_node->data = data;
    HistoryNodeType* prev_ptr = NULL;

    int curPos = 1;

    //if want to insert into head
    if (position == 1){
        return listInsertHead(headNode, data);
    }

        //insert inside list
    else {

        while (temp_ptr != NULL && curPos < position) {
            prev_ptr = temp_ptr;
            temp_ptr = temp_ptr->next;
            curPos++;
        }

        prev_ptr->next = new_node;
        new_node->next = temp_ptr;
    }

    return headNode;


}

/* listRemove: remove the node containing specific data; if multiple nodes
    contain the data, remove the node nearest to the head
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data that, if found in one of the nodes in the list, indicates
      the node to remove (in the case of multiple nodes containing the data,
	  remove the node nearest to the head)
   Return: a pointer to the head of the linked list */
HistoryNodeType* listRemove(HistoryNodeType* headNode, char* data){

    int removedNode = 0;
    HistoryNodeType* temp_ptr = headNode;
    HistoryNodeType* prev_ptr = NULL;
    int curPos = 1;

    while (removedNode == 0){
        if (temp_ptr->data == data){


            //if removing the head
            if (curPos == 1){
                prev_ptr = headNode;
                temp_ptr = prev_ptr->next;

                free(prev_ptr);
                return  temp_ptr;
            }
            else {
                prev_ptr->next = temp_ptr->next;
                free(temp_ptr);
                removedNode = 1;
            }

        }
        else{
            prev_ptr = temp_ptr;
            temp_ptr = temp_ptr->next;
            curPos++;
        }
    }

    return headNode;
}

/* listRemoveN: remove the <n>th node in the list
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node to remove, where the head is at position 1
   Return: a pointer to the head of the linked list */
HistoryNodeType* listRemoveN(HistoryNodeType* headNode, int position){

    HistoryNodeType* temp_ptr = headNode;
    HistoryNodeType* prev_ptr = headNode;
    int curPos = 1;

    //if want to remove head
    if (position == 1) {
        prev_ptr = headNode;
        temp_ptr = temp_ptr->next;

        free(prev_ptr);
        return  temp_ptr;
    }

    while (temp_ptr != NULL && curPos < position) {
        prev_ptr = temp_ptr;
        temp_ptr = temp_ptr->next;
        curPos++;
    }

    prev_ptr->next = temp_ptr->next;
    free(temp_ptr);

    return headNode;

}


/* listPrint: print the data contained in each node in the linked list,
    starting with the head, where each node's data is printed on a separate
    line
   Parameter: node*: a pointer to the head of a linked list */
void listPrint(HistoryNodeType* headNode){

    HistoryNodeType* temp_ptr = headNode;

    while (temp_ptr != NULL){
        printf("%s\n", temp_ptr->data);
        temp_ptr = temp_ptr->next;

    }

}

/* listprintN: print the data contained in the <n>th node of the list
   Parameters:
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node with the data to print, where the head is
       at position 1 */
void listPrintN(HistoryNodeType* headNode, int position){
    int curPos = 1;
    HistoryNodeType* temp_ptr = headNode;

    while (curPos < position){
        temp_ptr = temp_ptr->next;
        curPos++;
    }
    printf("%s", temp_ptr->data);

}

/* listGet: retrieve the data stored in the <n>th node in the list
   Parameters:
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node with the data to retrieve, where the head is
       at position 1
   Return: the data */
char* listGet(HistoryNodeType* headNode, int position){
    int curPos = 1;
    HistoryNodeType* temp_ptr = headNode;

    while (curPos < position){
        temp_ptr = temp_ptr->next;
        curPos++;
    }
    return temp_ptr->data;

}

/* listDestroy: free all malloc'd memory used in the linked list,
    including char*'s and HistoryNodeType*'s
   Parameter: HistoryNodeType*: a pointer to the head of a linked list */
void listDestroy(HistoryNodeType* headNode){
    HistoryNodeType* free_ptr = NULL;
    HistoryNodeType* temp_ptr = headNode;

    while(temp_ptr!= NULL){
        free_ptr = temp_ptr;
        temp_ptr = temp_ptr->next;
        free(free_ptr);
    }
}
