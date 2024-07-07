/**
 * @file	csds_array.h
 * @brief	Header file for dynamic array implementation.
 */
#ifndef CSDS_ARRAY_H
#define CSDS_ARRAY_H

#include <stddef.h>
#include <stdio.h>

#ifndef CSDS_ARRAY_INITIAL_CAP
#define CSDS_ARRAY_INITIAL_CAP 4
#endif /* !CSDS_ARRAY_INITIAL_CAP */

typedef struct {
	size_t len;
	size_t cap;
} ArrayHeader;

#endif /* !CSDS_ARRAY_H */

/* Define ONCE in one of your C files */
#define CSDS_ARRAY_IMPL
#ifdef CSDS_ARRAY_IMPL

/* Get the array header from the array pointer */
#define CSDS_ARRAYHEADER_OF(arr) ((ArrayHeader*)((char*)(arr)-sizeof(ArrayHeader)))

/* Get the length of the array by the array pointer */
#define array_len(arr) ((arr) ? CSDS_ARRAYHEADER_OF(arr)->len : 0)

/* Get the capacity of the array by the array pointer */
#define array_cap(arr) ((arr) ? CSDS_ARRAYHEADER_OF(arr)->cap : 0)

/* Allocate an array in the heap */
/* TODO */
/* #define array_alloc(arr, cap) do{\ */
/* 	ArrayHeader* header = NULL;\ */
/* 	if ((cap) <= 0) {\ */
/* 		(cap) = CSDS_ARRAY_INITIAL_CAP;\ */
/* 	header = (ArrayHeader*)malloc(sizeof(ArrayHeader)+(cap)*sizeof((arr)[0]));\ */
/* 	if (header == NULL) {\ */
/* 		fprintf(stderr, "Error: array_alloc: Could not allocate memory")\ */
/* 		exit(1);\ */
/* 	}\ */
/* 	header->cap = (cap);\ */
/* 	header->len = 0;\ */
/* 	(arr) = (typeof(arr))header+1;\ */
/* 	return header;\ */
/* } while(0) */

/* #define array_alloc(arr, cap) do { \ */
/*     ArrayHeader* header = NULL; \ */
/* 	int cap = (cap);\ */
/*     if ((cap) <= 0) { \ */
/*         cap = CSDS_ARRAY_INITIAL_CAP; \ */
/*     } \ */
/*     header = (ArrayHeader*)malloc(sizeof(ArrayHeader) + (cap) * sizeof((arr)[0])); \ */
/*     if (header == NULL) { \ */
/*         fprintf(stderr, "Error: array_alloc: Could not allocate memory\n"); \ */
/*         exit(1); \ */
/*     } \ */
/*     header->cap = cap; \ */
/*     header->len = 0; \ */
/*     (arr) = (typeof(arr))(header + 1); \ */
/* } while(0) */

/* Deallocate/Free array header memory and corresponding data */
#define array_dealloc(arr) do{\
	if (arr) {\
		free(CSDS_ARRAYHEADER_OF(arr));\
		(arr) = NULL;\
	}\
} while(0)

#endif /* CSDS_ARRAY_IMPL */
