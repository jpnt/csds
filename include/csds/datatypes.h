#ifndef CSDS_DATATYPES_H
#define CSDS_DATATYPES_H

/* #define __DT_INCLUDE_SYS_TYPES */

#ifndef NULL
#ifdef __cplusplus
#define NULL 0 /* for C++ */
#else
#define NULL (void*)0 /* for C */
#endif /* !__cplusplus */
#endif /* !NULL */

/* type definitions */
typedef unsigned int uint;
typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int int16;
typedef unsigned short int uint16;
typedef signed int int32;
typedef unsigned int uint32;
#ifndef __DT_INCLUDE_SYS_TYPES
typedef signed long int int64;
typedef unsigned long int uint64;
#else
#include <sys/types.h>
typedef __int64_t int64;
typedef __uint64_t uint64;
#endif /* !__DT_INCLUDE_SYS_TYPES */

/* constants defined as macros */
#ifndef PI
#define PI 3.141592653
#endif /* !PI */

#endif /* !CSDS_DATATYPES_H */
