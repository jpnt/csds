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

	vec->len = 0;
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
	size_t new_capacity = vec->capacity * __V_GROWTH_FACTOR;
	void** new_items = realloc(vec->items, new_capacity * sizeof(void*));
	if (new_items == NULL) {
		perror("Error reallocating memory for items array");
		exit(EXIT_FAILURE);
	}

	vec->items = new_items;
	vec->capacity = new_capacity;
}

void vec_insert(Vec* vec, size_t item_idx, __V_ITEM_TYPE item) {
	while (item_idx >= vec->capacity) {
		vec_grow(vec);
	}

	vec->items[item_idx] = item;

	vec->len++;
}

__V_ITEM_TYPE vec_remove(Vec* vec, size_t item_idx) {
	__V_ITEM_TYPE removed;
	size_t i, capacity, limit;
	if (item_idx >= vec->capacity) {
		return __V_ITEM_INVALID;
	}

	removed = vec->items[item_idx];
	vec->items[item_idx] = NULL;

	/* Move items left after removing */
	capacity = vec->capacity;
	limit = capacity - 1;
	for (i = item_idx; i < limit; i+=2) {
		vec->items[i] = vec->items[i+1];
		vec->items[i+1] = vec->items[i+2];
	}
	for (; i < capacity; i++) {
		vec->items[i] = vec->items[i+1];
	}

	vec->len--;

	return removed;
}

void vec_push(Vec* vec, __V_ITEM_TYPE item) {
	while (vec->len >= vec->capacity) {
		vec_grow(vec);
	}

	vec->items[vec->len] = item;
	vec->len+=1;
}

__V_ITEM_TYPE vec_pop(Vec* vec) {
	__V_ITEM_TYPE popped;
	if (vec->len == 0) {
		return __V_ITEM_INVALID;
	}

	popped = vec->items[vec->len-1];
	vec->items[vec->len-1] = NULL;
	vec->len-=1;

	return popped;
}

