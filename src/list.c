#include "../include/csds/list.h"
#include <stdio.h>
#include <stdlib.h>

List* list_create() {
	List* list = (List*) malloc(sizeof(List));
	if (list == NULL) {
		perror("Error allocating memory for doubly linked list");
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}

void list_destroy(List* list) {
	if (list == NULL) {
		return;
	}

	Node* current = list->head;
	Node* next;

	while (current != NULL) {
		next = current->next;
		node_destroy(current);
		current = next;
	}

	free(list);
}

Node* list_insert_after(List* list, Node* node, Node* new_node) {
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

	list->size+=1;

	return new_node;
}

Node* list_insert_before(List* list, Node* node, Node* new_node) {
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

	list->size+=1;

	return new_node;
}

Node* list_insert_at_head(List* list, Node* node) {
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

	list->size+=1;

	return node;
}

Node* list_insert_at_tail(List* list, Node* node) {
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

	list->size+=1;

	return node;
}

Node* list_push_back(List* list, void* data) {
	if (list == NULL || data == NULL) {
		return NULL;
	}

	Node* new_node = node_create(data, NULL, list->tail);

	if (list->tail != NULL) {
		list->tail->next = new_node;
	}

	list->tail = new_node;

	if (list->head == NULL) {
		list->head = new_node;
	}

	list->size+=1;

	return new_node;
}

Node* list_push_front(List* list, void* data) {
	if (list == NULL || data == NULL) {
		return NULL;
	}

	Node* new_node = node_create(data, list->head, NULL);

	if (list->head != NULL) {
		list->head->prev = new_node;
	}

	list->head = new_node;

	if (list->tail == NULL) {
		list->tail = new_node;
	}

	list->size+=1;

	return new_node;
}

void* list_remove(List* list, Node* node) {
	if (list == NULL || node == NULL) {
		return NULL;
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

	void* data = node->data;

	node_destroy(node);

	list->size-=1;

	return data;
}