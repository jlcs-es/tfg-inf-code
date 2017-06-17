#ifndef __ARITHMETIC_UTIL_H
#define __ARITHMETIC_UTIL_H

#include "smartcard_common/defs_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/


/********************************************************************/
/** This a a simple adapter for the needed Big Integer Arithmetic in*/
/* the virtual smartcard. It can be implemented as desired, with    */
/* optimized code code depending on the platform.                   */
/********************************************************************/
/** A software generic BYTE array implementation is provided so it  */
/* works in any platform, prioritizing memory usage. Of course, this*/
/* implementation will be slower than any platform specific code.   */
/********************************************************************/




/**
 * Calculates result = arr1 + arr2
 * Note that result is the same size as the addends
 * @param result    Array of size length. Can overlap arr1 or arr2.
 * @param arr1      Array of size length.
 * @param arr2      Array of size length.
 * @param length
 */
void addition(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);



/**
 * Calculates result = arr1 - arr2
 * @param result    Array of size length. Can overlap arr1 or arr2.
 * @param arr1      Array of size length.
 * @param arr2      Array of size length.
 * @param length
 */
void subtraction(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);


/**
 * Calculates result = arr1 * arr2
 * @param result Array of size 2*length. Stores the solution. Can overlap arr1 or arr2.
 * @param arr1 Array of size length. First factor.
 * @param arr2 Array of size length. Second factor.
 * @param length
 */
void multiplication(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);


/**
 * Calculates result = ( arr1 * arr2 ) mod modulus
 * @param result Array of size length. Stores the solution. Can overlap arr1 or arr2.
 * @param arr1 Array of size length. First factor. Does not need to be reduced modulus.
 * @param arr2 Array of size length. Second factor. Does not need to be reduced modulus.
 * @param modulus Array of size length. Stores the modulus value.
 * @param length
 */
void modularMultiplication(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length);


/**
 * Calculates result = ( base ^ exponent ) mod modulus
 * @param result Array of size modulusLength. Stores the solution.  Can overlap base.
 * @param base Array of size modulusLength. Base of the exponentiation.
 * @param exponent Array of size exponentLength. Power of the exponentiation.
 * @param modulus Array of size modulusLength. Stores the modulus value.
 * @param modulusLength
 * @param exponentLength
 */
void modularExponentiation(BYTE *result, BYTE *base, BYTE *exponent, BYTE *modulus, WORD modulusLength, WORD exponentLength);


/**
 * Calculates result = operand mod modulus
 * @param result Array of size modulusLength. Can overlap operand.
 * @param operand Array of size operandLength.
 * @param modulus Array of size modulusLength.
 * @param operandLength
 * @param modulusLength
 */
void modularReduction(BYTE *result, BYTE *operand, BYTE *modulus, WORD operandLength, WORD modulusLength);



#ifdef __cplusplus
}
#endif

#endif //__ARITHMETIC_UTIL_H
