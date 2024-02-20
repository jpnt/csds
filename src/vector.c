#include "../include/csds/vector.h"
#include <stdio.h>
#include <stdlib.h>

Vec* vec_create(size_t capacity) {
	Vec* v = (Vec*) malloc(sizeof(Vec));
	if (v == NULL) {
		perror("Error allocating memory for vector");
		exit(EXIT_FAILURE);
	}

	v->items = (void**) calloc(capacity, sizeof(void*));
	if (v->items == NULL) {
		perror("Error allocating memory for items array");
		free(v);
		exit(EXIT_FAILURE);
	}

	v->size = 0;
	v->capacity = capacity;
	return v;
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

	for (int i = item_idx; i < vec->capacity; i++) {
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


//
// TESTING
//
#include <stdio.h>

int main() {
	//Vec* test_vec = vec_create(10);
	//printf("items[0]: %p\n", test_vec->items[0]);
	//printf("size: %zu\n", test_vec->size);
	//printf("capacity: %zu\n", test_vec->capacity);


	//int data = 69;
	//void* vdata = (void*)&data;

	//vec_push(test_vec, vdata);
	//printf("items[0]: %p\n", test_vec->items[0]);
	//printf("*(int*)items[0]: %d\n", *(int*)test_vec->items[0]);
	


	//vec_push(test_vec, (void*)0x69);
	//vec_push(test_vec, (void*)0x420);
	//
	//void* firstpop = vec_pop(test_vec);
	//void* secondpop = vec_pop(test_vec);

	//printf("push: 0x69\n");
	//printf("push: 0x420\n");

	//printf("pop: %p\n", firstpop);
	//printf("pop: %p\n", secondpop);
	
	Vec* v = vec_create(4);

	vec_push(v, (void*)0x1);
	vec_push(v, (void*)0x2);
	vec_push(v, (void*)0x3);
	vec_push(v, (void*)0x4);

	printf("%p\t%p\t%p\t%p", v->items[0],v->items[1],v->items[2],v->items[3]);

	vec_remove(v, 0);

	printf("%p\t%p\t%p\t%p", v->items[0],v->items[1],v->items[2],v->items[3]);

	vec_destroy(v);
}
