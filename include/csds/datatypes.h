#ifndef CSDS_DATA_TYPES_H
#define CSDS_DATA_TYPES_H

/* #define __D_INCLUDE_SYS_TYPES */

#ifndef NULL
#ifdef __cplusplus
#define NULL 0 /* for C++ */
#else
#define NULL (void*)0 /* for C */
#endif /* !__cplusplus */
#endif /* !NULL */

/* more explicit types */
typedef unsigned int uint;
typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int int16;
typedef unsigned short int uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef float real32;
typedef double real64;
#ifndef __D_INCLUDE_SYS_TYPES
typedef signed long int int64;
typedef unsigned long int uint64;
#else
#include <sys/types.h>
typedef __int64_t int64;
typedef __uint64_t uint64;
#endif /* !__D_INCLUDE_SYS_TYPES */

#ifndef PI
#define PI 3.141592653
#endif /* !PI */

#endif /* !CSDS_DATA_TYPES_H */
