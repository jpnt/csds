#include "../include/csds_error.h"
#include <stdio.h>

void handle_error(int error_code, const char* file, int line)
{
	const char* errmsg = NULL;

	switch(error_code) {
	case 0: /* 0 == SUCCESS */
		return;

	case CSDS_ERROR_VEC_HEADER_NULL:
		errmsg = "Vector header pointer is NULL.";
		break;
	case CSDS_ERROR_VEC_ARR_NULL:
		errmsg = "Vector arr pointer is NULL.";
		break;
	case CSDS_ERROR_VEC_MALLOC_FAILED:
		errmsg = "Failed to allocate memory.";
		break;
	case CSDS_ERROR_VEC_REALLOC_FAILED:
		errmsg = "Failed to reallocate memory.";
		break;
	case CSDS_ERROR_VEC_OUT_OF_BOUNDS:
		errmsg = "Vector out of bounds.";
		break;
	case CSDS_ERROR_VEC_EMPTY:
		errmsg = "Vector is empty.";
		break;

	default:
		errmsg = "Unknown error code.";
	}

	fprintf(stderr, "ERROR: %s: %d: %s\n", file, line, errmsg);

	if (errno != 0) {
		fprintf(stderr, "errno: %d\n", errno);
	}

	exit(error_code);
}
