#include "../include/csds/deque.h"
#include <assert.h>

int main() {
	Deque* dq = deque_create(4);
	assert(dq->vec->capacity == 4);

	// Pushing items at the front
	deque_push_front(dq, (void*)0x1);
	deque_push_front(dq, (void*)0x2);
	deque_push_front(dq, (void*)0x3);
	assert(dq->vec->size == 3);

	// Assert that they are in the correct position
	assert(dq->vec->items[0] == (void*)0x3);
	assert(dq->vec->items[1] == (void*)0x2);
	assert(dq->vec->items[2] == (void*)0x1);

	// Pop items from the front
	assert(deque_pop_front(dq) == (void*)0x3);
	assert(deque_pop_front(dq) == (void*)0x2);
	assert(deque_pop_front(dq) == (void*)0x1);

	// Test Grow
	deque_push_front(dq, (void*)0x1);
	deque_push_front(dq, (void*)0x2);
	deque_push_front(dq, (void*)0x3);
	deque_push_front(dq, (void*)0x4);
	deque_push_front(dq, (void*)0x5);
	assert(dq->vec->capacity == 8);





	deque_destroy(dq);

	return 0;
}
