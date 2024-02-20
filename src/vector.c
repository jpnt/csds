#include "../include/csds/vector.h"
#include <stdio.h>
#include <stdlib.h>

Vec* vec_create(size_t capacity) {
	Vec* vec = (Vec*) malloc(sizeof(Vec));
	if (vec == NULL) {
		perror("Error allocating memory for vector");
		exit(EXIT_FAILURE);
	}

	vec->items = (void**) calloc(capacity, sizeof(void*));
	if (vec->items == NULL) {
		perror("Error allocating memory for items array");
		free(vec);
		exit(EXIT_FAILURE);
	}

	vec->size = 0;
	vec->capacity = capacity;
	return vec;
}

void vec_destroy(Vec* vec) {
	if (vec != NULL) {
		free(vec->items);
		free(vec);
	}
}

void vec_grow(Vec* vec) {
	size_t new_capacity = vec->capacity * 2;
	void** new_items = realloc(vec->items, new_capacity * sizeof(void*));
	if (new_items == NULL) {
		perror("Error reallocating memory for items array");
		exit(EXIT_FAILURE);
	}

	vec->items = new_items;
	vec->capacity = new_capacity;
}

void vec_insert(Vec* vec, size_t item_idx, void* item) {
	while (item_idx >= vec->capacity) {
		vec_grow(vec);
	}

	vec->items[item_idx] = item;

	vec->size++;
}

void* vec_remove(Vec* vec, size_t item_idx) {
	if (item_idx >= vec->capacity) {
		return NULL;
	}

	void* removed = vec->items[item_idx];
	vec->items[item_idx] = NULL;

	// Move items left after removing
	size_t i;
	size_t capacity = vec->capacity;
	size_t limit = capacity - 1;
	for (i = item_idx; i < limit; i+=2) {
		vec->items[i] = vec->items[i+1];
		vec->items[i+1] = vec->items[i+2];
	}
	for (; i < capacity; i++) {
		vec->items[i] = vec->items[i+1];
	}

	vec->size--;

	return removed;
}

void vec_push(Vec* vec, void* item) {
	while (vec->size >= vec->capacity) {
		vec_grow(vec);
	}

	vec->items[vec->size] = item;
	vec->size+=1;
}

void* vec_pop(Vec* vec) {
	if (vec->size == 0) {
		return NULL;
	}

	void* popped = vec->items[vec->size-1];
	vec->items[vec->size-1] = NULL;
	vec->size-=1;

	return popped;
}

