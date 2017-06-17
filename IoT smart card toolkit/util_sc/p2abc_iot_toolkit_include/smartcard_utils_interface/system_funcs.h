#ifndef __SYSTEM_FUNCS_H
#define __SYSTEM_FUNCS_H

#include <smartcard_common/defs_types.h>

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************/
/********************** System std Functions ************************/
/********************************************************************/


/********************************************************************/
/** This a a simple adapter for some functions that can be HW       */
/* dependent and usually implemented in standard libraries.         */
/********************************************************************/
/** This version is implemented with std libraries, but with this   */
/* facade, it is easier for not std compatible systems to implement */
/* their own version (e.g. sensor based random), without having to  */
/* modify the core of this SC solution.                             */
/********************************************************************/




/**
 * Copies the values of num bytes from the location pointed by source to the memory block pointed by destination.
 * Copying takes place as if an intermediate buffer were used, allowing the destination and source to overlap.
 * @param destination   Pointer to the destination array where the content is to be copied.
 * @param source        Pointer to the source of data to be copied.
 * @param num           Number of bytes to copy.
 * @return              \param destination is returned.
 */
void * mem_move(BYTE * destination, BYTE * source, WORD num);



/**
 * Compares the first num bytes of the block of memory pointed by ptr1 to the first num bytes pointed by ptr2,
 * returning zero if they all match or a value different from zero representing which is greater if they do not.
 * @param ptr1  Pointer to block of memory.
 * @param ptr2  Pointer to block of memory.
 * @param num   Number of bytes to compare.
 * @return      Returns an integral value indicating the relationship between the content of the memory blocks.
 */
BYTE mem_cmp(const BYTE * ptr1, const BYTE * ptr2, WORD num);



/**
 * Copies the values of num bytes from the location pointed to by source directly to the memory block pointed to by destination.
 * @param destination   Pointer to the destination array where the content is to be copied.
 * @param source        Pointer to the source of data to be copied.
 * @param num           Number of bytes to copy.
 * @return              \param destination is returned.
 */
void * mem_cpy(BYTE * destination, const BYTE * source, WORD num);




/**
 * Sets the first num bytes of the block of memory pointed by ptr to the specified value.
 * @param ptr       Pointer to the block of memory to fill.
 * @param value     Value to be set.
 * @param num       Number of bytes to be set to the value.
 * @return          \param ptr is returned.
 */
void * mem_set(BYTE * ptr, BYTE value, WORD num);


#ifdef __cplusplus
}
#endif

#endif // __SYSTEM_FUNCS_H
