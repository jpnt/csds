#include "../include/csds/list.h"
#include "../csds_femtotest.h"

/* TODO: Test is too big, separate into specific tests for each operation */
void test_list1() {
	void* data;
	ListNode* nodes[4];

	List* list = list_alloc();
	ASSERT_EQUALS(list->len, 0);

	/* Insert at head a node */
	data = (void*)0x1;
	nodes[0] = list_node_alloc(data, NULL, NULL);
	list_insert_at_head(list, nodes[0]);
	ASSERT_EQUALS(list->len, 1);
	ASSERT_EQUALS(list->head, nodes[0]);
	ASSERT_EQUALS(list->head, list->tail);


	/* Insert a new node after the previous one */
	nodes[1] = list_node_alloc((void*)0x2, NULL, NULL);
	list_insert_after(list, nodes[0], nodes[1]);
	ASSERT_EQUALS(list->len, 2);
	ASSERT_EQUALS(list->tail, nodes[1]);
	ASSERT_EQUALS(list->head, nodes[0]);
	ASSERT_EQUALS(nodes[0]->next, nodes[1]);
	ASSERT_EQUALS(nodes[1]->prev, nodes[0]);

	/*            HEAD       TAIL */
	/* NULL <- nodes[0] <-> nodes[1] -> NULL */
	


	/* Insert a new node before node 2: */

	nodes[2] = list_node_alloc((void*)0x3, NULL, NULL);
	list_insert_before(list, nodes[1], nodes[2]);
	ASSERT_EQUALS(list->len, 3);
	ASSERT_EQUALS(list->head, nodes[0]);
	ASSERT_EQUALS(list->tail, nodes[1]);
	ASSERT_EQUALS(list->head->next, nodes[2]);
	ASSERT_EQUALS(nodes[2]->next, list->tail);
	ASSERT_EQUALS(nodes[2]->prev, list->head);

	/*           HEAD                     TAIL */
	/* NULL <- nodes[0] <-> nodes[2] <-> nodes[1] -> NULL */
	

	/* Insert a node at the tail */
	
	nodes[3] = list_node_alloc((void*)0x4, NULL, NULL);
	list_insert_at_tail(list, nodes[3]);
	ASSERT_EQUALS(list->len, 4);
	ASSERT_EQUALS(list->tail, nodes[3]);
	ASSERT_EQUALS(nodes[3]->prev, nodes[1]);
	ASSERT_EQUALS(nodes[1]->next, nodes[3]);
	ASSERT_EQUALS(nodes[3]->next, NULL);

	/*          HEAD                                   TAIL */
	/* NULL <- nodes[0] <-> nodes[2] <-> nodes[1] <-> nodes[3] -> NULL */
	
	/* Removal of nodes */
	list_remove(list, nodes[0]);
	list_remove(list, nodes[1]);
	list_remove(list, nodes[2]);
	list_remove(list, nodes[3]);
	ASSERT_EQUALS(list->len, 0);

	list_dealloc(list);
}

int main()
{
	TEST_RUN(test_list1, "test_list1");

	TEST_REPORT();
}
