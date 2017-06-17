#ifndef __DEFS_TYPES_H
#define __DEFS_TYPES_H

// TODO: remove and replace the if else macro with the platform correct types
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char BYTE; //1byte
typedef signed char SBYTE;
typedef unsigned short WORD; //2bytes
typedef signed short SWORD;
#if UINT_MAX == 4294967295
typedef unsigned int DWORD; //4bytes
typedef signed int SDWORD;
#else
typedef unsigned long DWORD; //4bytes
typedef signed long SDWORD;
#endif

typedef BYTE BOOL;




#ifdef __cplusplus
}
#endif

#endif // __DEFS_TYPES_H
