#include "../include/csds/doublylinkedlist.h"
#include "../include/csds/gde.h"
#include <assert.h>
#include <stdio.h>

int main() {

	DLList* dll = dllist_create();
	assert(dll->size == 0);


	// Insert at head a node
	
	void* data = (void*)0x1;
	Node* node = node_create(data, NULL, NULL);
	dllist_insert_at_head(dll, node);
	assert(dll->size == 1);
	assert(dll->head == node);
	assert(dll->head == dll->tail);


	// Insert a new node after the previous one
	Node* node2 = node_create((void*)0x2, NULL, NULL);
	dllist_insert_after(dll, node, node2);
	assert(dll->size == 2);
	assert(dll->tail == node2);
	assert(dll->head == node);
	assert(node->next == node2);
	assert(node2->prev == node);

	//         HEAD     TAIL
	// NULL <- node <-> node2 -> NULL
	


	// Insert a new node before node 2:

	Node* node3 = node_create((void*)0x3, NULL, NULL);
	dllist_insert_before(dll, node2, node3);
	assert(dll->size == 3);
	assert(dll->head == node);
	assert(dll->tail == node2);
	assert(dll->head->next == node3);
	assert(node3->next == dll->tail);
	assert(node3->prev == dll->head);

	//         HEAD               TAIL
	// NULL <- node <-> node3 <-> node2 -> NULL
	

	// Insert a node at the tail
	
	Node* node4 = node_create((void*)0x4, NULL, NULL);
	dllist_insert_at_tail(dll, node4);
	assert(dll->size == 4);
	assert(dll->tail == node4);
	assert(node4->prev == node2);
	assert(node2->next == node4);
	assert(node4->next == NULL);

	//         HEAD                         TAIL
	// NULL <- node <-> node3 <-> node2 <-> node4 -> NULL

	
	// Removal of nodes
	dllist_remove(dll, node);
	dllist_remove(dll, node2);
	dllist_remove(dll, node3);
	dllist_remove(dll, node4);
	assert(dll->size == 0);


	// Generic data example test
	Gde* gde1 = gde_create();
	Gde* gde2 = gde_create();
	gde2->a = 10;
	gde2->b = 20;
	gde2->c = 30;
	gde2->d = 40;

	dllist_push_back(dll, gde1);
	dllist_push_back(dll, gde2);
	assert(dll->size == 2);
	assert(dll->head->data == gde1);
	assert(dll->head->next == dll->tail);
	assert(dll->tail->prev == dll->head);
	assert(dll->tail->data == gde2);

	//         HEAD           TAIL
	// NULL <- NODE(gde1) <-> NODE(gde2) -> NULL

	// Get some values
	int value = *(int*)dll->tail->data;
	short value2 = ((Gde*)dll->tail->data)->b;
	char value3 = ((Gde*)dll->tail->data)->c;
	char value4 = ((Gde*)dll->tail->data)->d;
	assert(value == 10);
	assert(value2 == 20);
	assert(value3 == 30);
	assert(value4 == '(');



	// Free memory
	gde_destroy(gde1);
	gde_destroy(gde2);

	dllist_destroy(dll);

	return 0;
}
