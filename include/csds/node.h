#ifndef CSDS_NODE_H
#define CSDS_NODE_H

typedef struct Node {
	void* data;
	struct Node* next;
	struct Node* prev;
} Node;

Node* node_create(void* data, Node* next, Node* prev);
void node_destroy(Node* node);

#endif // !CSDS_NODE_H
