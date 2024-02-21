#ifndef CSDS_DOUBLYLINKEDLIST_H
#define CSDS_DOUBLYLINKEDLIST_H

typedef struct Node {
	void* data;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct {
	struct Node* head;
	struct Node* tail;
} DLList;

DLList* dllist_create();
void dllist_destroy(DLList* dll);

void dllist_insert_after(DLList* dll, Node* node, Node* new_node);
void dllist_insert_before(DLList* dll, Node* node, Node* new_node);
void dllist_insert_at_head(DLList* dll, Node* node);
void dllist_insert_at_tail(DLList* dll, Node* node);

void dllist_remove(DLList* dll, const Node* node);

#endif // !CSDS_DOUBLYLINKEDLIST_H
