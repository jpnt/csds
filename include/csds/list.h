#ifndef CSDS_LIST_H
#define CSDS_LIST_H

#include "node.h"
#include <stddef.h>

typedef struct {
	struct Node* head;
	struct Node* tail;
	size_t size;
} List;

List* list_create();
void list_destroy(List* list);

Node* list_insert_after(List* list, Node* node, Node* new_node);
Node* list_insert_before(List* list, Node* node, Node* new_node);

Node* list_insert_at_head(List* list, Node* node);
Node* list_insert_at_tail(List* list, Node* node);

Node* list_push_back(List* list, void* data);
Node* list_push_front(List* list, void* data);

void* list_remove(List* list, Node* node);

#endif // !CSDS_LIST_H
