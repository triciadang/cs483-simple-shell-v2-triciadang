#ifndef PEX1_LIST_H
#define PEX1_LIST_H

typedef struct node {
    char* data;
    struct node* next;
} HistoryNodeType;

/* listInsertTail: create a new node at the end of the linked list
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data to be stored in the new node
   Return: a pointer to the head of the linked list */
HistoryNodeType* listInsertTail(HistoryNodeType*, char*);

/* listInsertHead: create a new node and insert it at the head of the linked
    list
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data to be stored in the new node
   Return: a pointer to the new head of the linked list */
HistoryNodeType* listInsertHead(HistoryNodeType*, char*);

/* listInsertN: create a new node and insert it at the <n>th position,
    where the head is at position 1
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data to be stored in the new node
   - int: the position in which to insert the new node
   Return: a pointer to the head of the linked list */
HistoryNodeType* listInsertN(HistoryNodeType*, char*, int);

/* listRemove: remove the node containing specific data; if multiple nodes
    contain the data, remove the node nearest to the head
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data that, if found in one of the nodes in the list, indicates
      the node to remove (in the case of multiple nodes containing the data,
	  remove the node nearest to the head)
   Return: a pointer to the head of the linked list */
HistoryNodeType* listRemove(HistoryNodeType*, char*);

/* listRemoveN: remove the <n>th node in the list
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node to remove, where the head is at position 1
   Return: a pointer to the head of the linked list */
HistoryNodeType* listRemoveN(HistoryNodeType*, int);

/* listPrint: print the data contained in each node in the linked list,
    starting with the head, where each node's data is printed on a separate
    line
   Parameter: node*: a pointer to the head of a linked list */
void listPrint(HistoryNodeType*);

/* listprintN: print the data contained in the <n>th node of the list
   Parameters:
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node with the data to print, where the head is
       at position 1 */
void listPrintN(HistoryNodeType*, int);

/* listGet: retrieve the data stored in the <n>th node in the list
   Parameters:
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node with the data to retrieve, where the head is
       at position 1
   Return: the data */
char* listGet(HistoryNodeType*, int);

/* listDestroy: free all malloc'd memory used in the linked list,
    including char*'s and HistoryNodeType*'s
   Parameter: HistoryNodeType*: a pointer to the head of a linked list */
void listDestroy(HistoryNodeType*);

#endif //PEX1_LIST_H
