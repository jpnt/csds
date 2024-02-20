#ifndef CSDS_DEQUE_H
#define CSDS_DEQUE_H

#include "vector.h"
#include <stddef.h>

typedef struct {
	Vec* vec;
	size_t front;
	size_t back;
} Deque;

extern Deque* deque_create(size_t capacity);
extern void deque_destroy(Deque* deque);
extern void deque_grow(Deque* deque);

extern void deque_push_front(Deque* deque, void* item);
extern void deque_push_back(Deque* deque, void* item);

extern void* deque_pop_front(Deque* deque);
extern void* deque_pop_back(Deque* deque);

#endif // !CSDS_DEQUE_H
