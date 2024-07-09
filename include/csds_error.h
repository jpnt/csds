#ifndef CSDS_ERROR_H
#define CSDS_ERROR_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define CSDS_ERROR_VEC_HEADER_NULL	-11
#define CSDS_ERROR_VEC_ARR_NULL		-12
#define CSDS_ERROR_VEC_MALLOC_FAILED	-13
#define CSDS_ERROR_VEC_REALLOC_FAILED	-14
#define CSDS_ERROR_VEC_OUT_OF_BOUNDS	-15
#define CSDS_ERROR_VEC_EMPTY		-16
/* Add more errors as needed */

#define HANDLE_ERROR(error_code) handle_error((error_code), __FILE__, __LINE__)

extern void handle_error(int error_code, const char* file, int line);

#endif /* !CSDS_ERROR_H */
