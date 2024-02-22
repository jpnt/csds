#include "../include/csds/doublylinkedlist.h"
#include <stdio.h>
#include <stdlib.h>

DLList* dllist_create() {
	DLList* dll = (DLList*) malloc(sizeof(DLList));
	if (dll == NULL) {
		perror("Error allocating memory for doubly linked list");
		exit(EXIT_FAILURE);
	}
	dll->head = NULL;
	dll->tail = NULL;
	dll->size = 0;

	return dll;
}

void dllist_destroy(DLList* dll) {
	if (dll == NULL) {
		return;
	}

	Node* current = dll->head;
	Node* next;

	while (current != NULL) {
		next = current->next;
		node_destroy(current);
		current = next;
	}

	free(dll);
}

Node* dllist_insert_after(DLList* dll, Node* node, Node* new_node) {
	// Invalid arguments
	if (dll == NULL || new_node == NULL) {
		return NULL;
	}

	if (dll->head == NULL || node == NULL) {
		dllist_insert_at_head(dll, new_node);
		return new_node;
	}

	// Update links
	new_node->prev = node;
	new_node->next = node->next;

	// Update links for adjacent nodes
	if (node->next != NULL) {
		node->next->prev = new_node;
	}
	node->next = new_node;

	// Update tail if necessary
	if (node == dll->tail) {
		dll->tail = new_node;
	}

	dll->size+=1;

	return new_node;
}

Node* dllist_insert_before(DLList* dll, Node* node, Node* new_node) {
	// Invalid arguments
	if (dll == NULL || new_node == NULL) {
		return NULL;
	}

	if (dll->head == NULL || node == NULL) {
		dllist_insert_at_head(dll, new_node);
		return new_node;
	}

	// Update links
	new_node->next = node;
	new_node->prev = node->prev;

	// Update links for adjacent nodes
	if (node->prev != NULL) {
		node->prev->next = new_node;
	}
	node->prev = new_node;

	// Update head if necessary
	if (node == dll->head) {
		dll->head = new_node;
	}

	dll->size+=1;

	return new_node;
}

Node* dllist_insert_at_head(DLList* dll, Node* node) {
	if (dll == NULL || node == NULL) {
		return NULL;
	}

	if (dll->head == NULL) {
		dll->head = node;
		dll->tail = node;
		node->next = NULL;
		node->prev = NULL;
	} else {
		node->next = dll->head;
		node->prev = NULL;
		dll->head->prev = node;
		dll->head = node;
	}

	dll->size+=1;

	return node;
}

Node* dllist_insert_at_tail(DLList* dll, Node* node) {
	if (dll == NULL || node == NULL) {
		return NULL;
	}

	if (dll->tail == NULL) {
		dll->head = node;
		dll->tail = node;
		node->next = NULL;
		node->prev = NULL;
	} else {
		node->next = NULL;
		node->prev = dll->tail;
		dll->tail->next = node;
		dll->tail = node;
	}

	dll->size+=1;

	return node;
}

Node* dllist_push_back(DLList* dll, void* data) {
	if (dll == NULL || data == NULL) {
		return NULL;
	}

	Node* new_node = node_create(data, NULL, dll->tail);

	if (dll->tail != NULL) {
		dll->tail->next = new_node;
	}

	dll->tail = new_node;

	if (dll->head == NULL) {
		dll->head = new_node;
	}

	dll->size+=1;

	return new_node;
}

Node* dllist_push_front(DLList* dll, void* data) {
	if (dll == NULL || data == NULL) {
		return NULL;
	}

	Node* new_node = node_create(data, dll->head, NULL);

	if (dll->head != NULL) {
		dll->head->prev = new_node;
	}

	dll->head = new_node;

	if (dll->tail == NULL) {
		dll->tail = new_node;
	}

	dll->size+=1;

	return new_node;
}

void dllist_remove(DLList* dll, Node* node) {
	if (dll == NULL || node == NULL) {
		return;
	}

	if (dll->head == node) {
		dll->head = node->next;
	}

	if (dll->tail == node) {
		dll->tail = node->prev;
	}

	if (node->prev != NULL) {
		node->prev->next = node->next;
	}

	if (node->next != NULL) {
		node->next->prev = node->prev;
	}

	node_destroy(node);
	dll->size-=1;
}
