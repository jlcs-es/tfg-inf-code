#ifndef __ARITHMETIC_IMPLEMENTATION_V1_H
#define __ARITHMETIC_IMPLEMENTATION_V1_H

#include "smartcard_common/defs_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void shift_right(BYTE *arr, WORD length);
void shiftLeftbyN(BYTE *arr, WORD length, WORD N);
void fillZeros(BYTE *arr, WORD length);
void copyFromTo(BYTE *src, BYTE *dst, WORD length);

BOOL isZero(BYTE *arr, WORD length);
BOOL isEqual(BYTE *arr1, BYTE *arr2, WORD length);
BOOL isGreater(BYTE *arr1, BYTE *arr2, WORD length);

void division(BYTE *quotient, BYTE *dividend, BYTE *divisor, WORD length);
void module(BYTE *result, BYTE *base, BYTE *modulus, WORD modulusLength);
void subtract(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);
void add(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);
void modular_add(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length);
void product(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);
void modular_product(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length);
void modular_exponentiation(BYTE *result, BYTE *base, BYTE *exponent, BYTE *modulus, WORD modulusLength, WORD exponentLength);


#ifdef __cplusplus
}
#endif

#endif //__ARITHMETIC_IMPLEMENTATION_V1_H
