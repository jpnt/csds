#ifndef CSDS_LISTNODE_H
#define CSDS_LISTNODE_H

#ifndef __L_DATA_TYPE
#define __L_DATA_TYPE void*
#endif // !__L_DATA_TYPE

/* what to return if the ListNode->data is invalid, has to be of type __L_DATA_TYPE */
#ifndef __L_DATA_INVALID
#define __L_DATA_INVALID NULL
#endif // !__L_DATA_INVALID

typedef struct ListNode {
	struct ListNode* next; /* pointer to the next node */
	struct ListNode* prev; /* pointer to the previous node */
	__L_DATA_TYPE data; /* data held by the node */
} ListNode;

/* creates a new node with specified data, next, and prev pointers */
extern ListNode* node_create(__L_DATA_TYPE data, ListNode* next, ListNode* prev);
/* frees memory allocated for the node */
extern void node_destroy(ListNode* node);

#endif // !CSDS_LISTNODE_H
