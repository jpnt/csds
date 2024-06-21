#include "../include/csds/list.h"
#include <stdio.h>
#include <stdlib.h>

List* list_alloc() {
	List* list = (List*) malloc(sizeof(List));
	if (list == NULL) {
		perror("Error allocating memory for doubly linked list");
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;

	return list;
}

void list_dealloc(List* list) {
	ListNode* current;
	ListNode* next;

	if (list == NULL) {
		return;
	}

	current = list->head;

	while (current != NULL) {
		next = current->next;
		list_node_dealloc(current);
		current = next;
	}

	free(list);
}

ListNode* list_insert_after(List* list, ListNode* node, ListNode* new_node) {
	/* Invalid arguments */
	if (list == NULL || new_node == NULL) {
		return NULL;
	}

	if (list->head == NULL || node == NULL) {
		list_insert_at_head(list, new_node);
		return new_node;
	}

	/* Update links */
	new_node->prev = node;
	new_node->next = node->next;

	/* Update links for adjacent nodes */
	if (node->next != NULL) {
		node->next->prev = new_node;
	}
	node->next = new_node;

	/* Update tail if necessary */
	if (node == list->tail) {
		list->tail = new_node;
	}

	list->len+=1;

	return new_node;
}

ListNode* list_insert_before(List* list, ListNode* node, ListNode* new_node) {
	/* Invalid arguments */
	if (list == NULL || new_node == NULL) {
		return NULL;
	}

	if (list->head == NULL || node == NULL) {
		list_insert_at_head(list, new_node);
		return new_node;
	}

	/* Update links */
	new_node->next = node;
	new_node->prev = node->prev;

	/* Update links for adjacent nodes */
	if (node->prev != NULL) {
		node->prev->next = new_node;
	}
	node->prev = new_node;

	/* Update head if necessary */
	if (node == list->head) {
		list->head = new_node;
	}

	list->len+=1;

	return new_node;
}

ListNode* list_insert_at_head(List* list, ListNode* node) {
	if (list == NULL || node == NULL) {
		return NULL;
	}

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
		node->next = NULL;
		node->prev = NULL;
	} else {
		node->next = list->head;
		node->prev = NULL;
		list->head->prev = node;
		list->head = node;
	}

	list->len+=1;

	return node;
}

ListNode* list_insert_at_tail(List* list, ListNode* node) {
	if (list == NULL || node == NULL) {
		return NULL;
	}

	if (list->tail == NULL) {
		list->head = node;
		list->tail = node;
		node->next = NULL;
		node->prev = NULL;
	} else {
		node->next = NULL;
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}

	list->len+=1;

	return node;
}

ListNode* list_push_back(List* list, __L_DATA_TYPE data) {
	ListNode* new_node;

	if (list == NULL || data == NULL) {
		return NULL;
	}

	new_node = list_node_alloc(data, NULL, list->tail);

	if (list->tail != NULL) {
		list->tail->next = new_node;
	}

	list->tail = new_node;

	if (list->head == NULL) {
		list->head = new_node;
	}

	list->len+=1;

	return new_node;
}

ListNode* list_push_front(List* list, __L_DATA_TYPE data) {
	ListNode* new_node;

	if (list == NULL || data == NULL) {
		return NULL;
	}

	new_node = list_node_alloc(data, list->head, NULL);

	if (list->head != NULL) {
		list->head->prev = new_node;
	}

	list->head = new_node;

	if (list->tail == NULL) {
		list->tail = new_node;
	}

	list->len+=1;

	return new_node;
}

__L_DATA_TYPE list_remove(List* list, ListNode* node) {
	__L_DATA_TYPE data;

	if (list == NULL || node == NULL) {
		return __L_DATA_INVALID;
	}

	if (list->head == node) {
		list->head = node->next;
	}

	if (list->tail == node) {
		list->tail = node->prev;
	}

	if (node->prev != NULL) {
		node->prev->next = node->next;
	}

	if (node->next != NULL) {
		node->next->prev = node->prev;
	}

	data = node->data;

	list_node_dealloc(node);

	list->len-=1;

	return data;
}
