#ifndef CSDS_DEQUE_H
#define CSDS_DEQUE_H

#include "vector.h"
#include <stddef.h>

typedef struct {
	Vec* vec;
	size_t front;
	size_t rear;
} Deque;

#endif // !CSDS_DEQUE_H
