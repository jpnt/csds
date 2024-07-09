#ifndef CSDS_LIST_H
#define CSDS_LIST_H

#include "listnode.h"
#include <stddef.h>

typedef struct {
	struct ListNode* head; /* pointer to the first node */
	struct ListNode* tail; /* pointer to the last node */
	size_t len; /* number of nodes in the list */
} List;

/* allocates memory in the heap for the linked list */
extern List* list_alloc();
/* frees linked list memory and optioonal node data */
extern void list_dealloc(List* list);
/* inserts a new node after the specified node */
extern ListNode* list_insert_after(List* list, ListNode* node, ListNode* new_node);
/* inserts a new node before the specified node */
extern ListNode* list_insert_before(List* list, ListNode* node, ListNode* new_node);
/* inserts a new node at the head of the list */
extern ListNode* list_insert_at_head(List* list, ListNode* node);
/* inserts a new node at the tail of the list */
extern ListNode* list_insert_at_tail(List* list, ListNode* node);
/* creates a new node from data and inserts it at tail */
extern ListNode* list_push_back(List* list, __L_DATA_TYPE data);
/* creates a new node from data and inserts it at head */
extern ListNode* list_push_front(List* list, __L_DATA_TYPE data);
/* removes a node from the list and returns it */
extern __L_DATA_TYPE list_remove(List* list, ListNode* node);

#endif /* !CSDS_LIST_H */
