#include "../include/csds/list.h"
#include "../include/csds/gde.h"
#include <assert.h>
#include <stdio.h>

int main() {

	List* list = list_create();
	assert(list->size == 0);


	// Insert at head a node
	
	void* data = (void*)0x1;
	Node* node = node_create(data, NULL, NULL);
	list_insert_at_head(list, node);
	assert(list->size == 1);
	assert(list->head == node);
	assert(list->head == list->tail);


	// Insert a new node after the previous one
	Node* node2 = node_create((void*)0x2, NULL, NULL);
	list_insert_after(list, node, node2);
	assert(list->size == 2);
	assert(list->tail == node2);
	assert(list->head == node);
	assert(node->next == node2);
	assert(node2->prev == node);

	//         HEAD     TAIL
	// NULL <- node <-> node2 -> NULL
	


	// Insert a new node before node 2:

	Node* node3 = node_create((void*)0x3, NULL, NULL);
	list_insert_before(list, node2, node3);
	assert(list->size == 3);
	assert(list->head == node);
	assert(list->tail == node2);
	assert(list->head->next == node3);
	assert(node3->next == list->tail);
	assert(node3->prev == list->head);

	//         HEAD               TAIL
	// NULL <- node <-> node3 <-> node2 -> NULL
	

	// Insert a node at the tail
	
	Node* node4 = node_create((void*)0x4, NULL, NULL);
	list_insert_at_tail(list, node4);
	assert(list->size == 4);
	assert(list->tail == node4);
	assert(node4->prev == node2);
	assert(node2->next == node4);
	assert(node4->next == NULL);

	//         HEAD                         TAIL
	// NULL <- node <-> node3 <-> node2 <-> node4 -> NULL

	
	// Removal of nodes
	list_remove(list, node);
	list_remove(list, node2);
	list_remove(list, node3);
	list_remove(list, node4);
	assert(list->size == 0);


	// Generic data example test
	Gde* gde1 = gde_create();
	Gde* gde2 = gde_create();
	gde2->a = 10;
	gde2->b = 20;
	gde2->c = 30;
	gde2->d = 40;

	list_push_back(list, gde1);
	list_push_back(list, gde2);
	assert(list->size == 2);
	assert(list->head->data == gde1);
	assert(list->head->next == list->tail);
	assert(list->tail->prev == list->head);
	assert(list->tail->data == gde2);

	//         HEAD           TAIL
	// NULL <- NODE(gde1) <-> NODE(gde2) -> NULL

	// Get some values
	int value = *(int*)list->tail->data;
	short value2 = ((Gde*)list->tail->data)->b;
	char value3 = ((Gde*)list->tail->data)->c;
	char value4 = ((Gde*)list->tail->data)->d;
	assert(value == 10);
	assert(value2 == 20);
	assert(value3 == 30);
	assert(value4 == '(');



	// Free memory
	gde_destroy(gde1);
	gde_destroy(gde2);

	list_destroy(list);

	return 0;
}
