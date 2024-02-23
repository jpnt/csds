#ifndef CSDS_DOUBLYLINKEDLIST_H
#define CSDS_DOUBLYLINKEDLIST_H

#include "node.h"
#include <stddef.h>

typedef struct {
	struct Node* head;
	struct Node* tail;
	size_t size;
} DLList;

DLList* dllist_create();
void dllist_destroy(DLList* dll);

Node* dllist_insert_after(DLList* dll, Node* node, Node* new_node);
Node* dllist_insert_before(DLList* dll, Node* node, Node* new_node);

Node* dllist_insert_at_head(DLList* dll, Node* node);
Node* dllist_insert_at_tail(DLList* dll, Node* node);

Node* dllist_push_back(DLList* dll, void* data);
Node* dllist_push_front(DLList* dll, void* data);

void* dllist_remove(DLList* dll, Node* node);

#endif // !CSDS_DOUBLYLINKEDLIST_H
