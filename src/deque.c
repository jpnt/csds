#include "../include/csds/deque.h"
#include <stdio.h>
#include <stdlib.h>

Deque* deque_create(size_t capacity) {
	Deque* deque = (Deque*) malloc(sizeof(Deque));
	if (deque == NULL) {
		perror("Error allocating memory for deque");
		exit(EXIT_FAILURE);
	}

	Vec* vec = vec_create(capacity);

	deque->vec = vec;
	deque->front = 0;
	deque->back = 0;

	return deque;
}

void deque_destroy(Deque* deque) {
	vec_destroy(deque->vec);
	free(deque);
}

void deque_grow(Deque* deque) {
	vec_grow(deque->vec);
}

void deque_push_front(Deque* deque, void* item) {
	while (deque->vec->size >= deque->vec->capacity) {
		vec_grow(deque->vec);
	}

	if (deque->front == 0) {
		for (size_t i = deque->vec->size; i > 0; i--) {
			deque->vec->items[i] = deque->vec->items[i-1];
		}
	}

	vec_insert(deque->vec, deque->front, item);

	deque->back+=1;
}

void deque_push_back(Deque* deque, void* item) {
	while (deque->vec->size >= deque->vec->capacity) {
		vec_grow(deque->vec);
	}

	vec_insert(deque->vec, deque->back, item);

	deque->back+=1;
}

void* deque_pop_front(Deque* deque) {
	void* popped = deque->vec->items[deque->front];

	deque->vec->items[deque->front] = NULL; // <-- TODO

	if (deque->front < deque->vec->capacity - 1) {
		deque->front+=1;
	}

	return popped;
}

void* deque_pop_back(Deque* deque) {
	void* popped = deque->vec->items[deque->back];

	deque->vec->items[deque->front] = NULL; // <-- TODO

	if (deque->back > 0) {
		deque->back-=1;
	}

	return popped;
}
