#ifndef CSDS_LIST_H
#define CSDS_LIST_H

#include "csds_error.h"

#define LIST_HEADER_OF(data) (struct csds_list_header*)data-1

typedef struct csds_list_header ListHeader;

struct csds_list_header {
	struct csds_list_header *prev, *next;
	/* T* data */
};

/* TODO */
/* if using embedded linked list there wont be any allocs/deallocs */

/* Allocates memory in for the linked list header and data */
extern int list_alloc(void** data, size_t size);
/* Frees all linked list header memory and data */
extern int list_dealloc(void* data);
/* Free one specific linked list header and data */
extern int list_dealloc_single(void* data);
/* Inserts new data after the current specified data */
extern int list_push_next(void* data_curr, void* data_next);
/* Inserts new data before the current specified data */
extern int list_push_prev(void* data_curr, void* data_next);

#endif /* !CSDS_LIST_H */
