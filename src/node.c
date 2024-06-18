#include "../include/csds/node.h"
#include <stddef.h>
#include <stdlib.h>

Node* node_create(void* data, Node* next, Node* prev) {
	Node* new_node = (Node*) malloc(sizeof(Node));
	if (new_node == NULL) {
		return NULL;
	}

	new_node->data = data;
	new_node->next = next;
	new_node->prev = prev;

	return new_node;
}

void node_destroy(Node* node) {
	if (node == NULL) {
		return;
	}

	/* free(node->data); */
	free(node);
}
