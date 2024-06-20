#include "../include/csds/list.h"
#include <assert.h>
#include <stdio.h>

int main() {
	void* data;
	ListNode* nodes[4];

	List* list = list_create();
	assert(list->len == 0);

	/* Insert at head a node */
	data = (void*)0x1;
	nodes[0] = node_create(data, NULL, NULL);
	list_insert_at_head(list, nodes[0]);
	assert(list->len == 1);
	assert(list->head == nodes[0]);
	assert(list->head == list->tail);


	/* Insert a new node after the previous one */
	nodes[1] = node_create((void*)0x2, NULL, NULL);
	list_insert_after(list, nodes[0], nodes[1]);
	assert(list->len == 2);
	assert(list->tail == nodes[1]);
	assert(list->head == nodes[0]);
	assert(nodes[0]->next == nodes[1]);
	assert(nodes[1]->prev == nodes[0]);

	/*            HEAD       TAIL */
	/* NULL <- nodes[0] <-> nodes[1] -> NULL */
	


	/* Insert a new node before node 2: */

	nodes[2] = node_create((void*)0x3, NULL, NULL);
	list_insert_before(list, nodes[1], nodes[2]);
	assert(list->len == 3);
	assert(list->head == nodes[0]);
	assert(list->tail == nodes[1]);
	assert(list->head->next == nodes[2]);
	assert(nodes[2]->next == list->tail);
	assert(nodes[2]->prev == list->head);

	/*           HEAD                     TAIL */
	/* NULL <- nodes[0] <-> nodes[2] <-> nodes[1] -> NULL */
	

	/* Insert a node at the tail */
	
	nodes[3] = node_create((void*)0x4, NULL, NULL);
	list_insert_at_tail(list, nodes[3]);
	assert(list->len == 4);
	assert(list->tail == nodes[3]);
	assert(nodes[3]->prev == nodes[1]);
	assert(nodes[1]->next == nodes[3]);
	assert(nodes[3]->next == NULL);

	/*          HEAD                                  TAIL */
	/* NULL <- nodes[0] <-> nodes[2] <-> nodes[1] <-> nodes[3] -> NULL */
	
	/* Removal of nodes */
	list_remove(list, nodes[0]);
	list_remove(list, nodes[1]);
	list_remove(list, nodes[2]);
	list_remove(list, nodes[3]);
	assert(list->len == 0);

	list_destroy(list);

	return 0;
}
