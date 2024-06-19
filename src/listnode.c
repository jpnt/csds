#include "../include/csds/listnode.h"
#include <stddef.h>
#include <stdlib.h>

ListNode* node_create(__L_DATA_TYPE data, ListNode* next, ListNode* prev) {
	ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
	if (new_node == NULL) {
		return NULL;
	}

	new_node->data = data;
	new_node->next = next;
	new_node->prev = prev;

	return new_node;
}

void node_destroy(ListNode* node) {
	if (node == NULL) {
		return;
	}

	/* free(node->data); */
	free(node);
}
