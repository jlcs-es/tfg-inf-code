#include "smartcard_utils_interface/system_funcs.h"

#include <stdlib.h>
#include <string.h>


void * mem_move(BYTE * destination, BYTE * source, WORD num){
    return memmove(destination, source, num);
}


BYTE mem_cmp(const BYTE * ptr1, const BYTE * ptr2, WORD num){
    return memcmp(ptr1, ptr2, num);
}


void * mem_cpy(BYTE * destination, const BYTE * source, WORD num){
    return memcpy(destination, source, num);
}


void * mem_set(BYTE * ptr, BYTE value, WORD num){
    return memset(ptr, value, num);
}