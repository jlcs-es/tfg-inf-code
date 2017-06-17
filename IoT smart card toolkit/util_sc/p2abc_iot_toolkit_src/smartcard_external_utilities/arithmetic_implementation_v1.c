#include <smartcard_external_utilities/arithmetic_implementation_v1.h>

#include "debug.h"



void shift_right(BYTE *arr, WORD length)
{

    WORD i;
    for (i = length-1;  i > 0;  --i)
    {
        arr[i] = (arr[i] >> 1) | ((arr[i-1] << 7) & 128);
    }
    arr[0] = arr[0] >> 1;

}

/**
 * Shift left n bits, with n < 8
 * @param arr
 * @param length
 * @param n
 */
void shiftLeftbyn(BYTE *arr, WORD length, WORD n){
    // Suppose n < 8
    WORD i;
    BYTE aux[8] = {0b00000000, 0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111 };
    for (i = 0;  i < length - 1;  ++i)
    {
        arr[i] = (arr[i] << n) | ((arr[i+1] >> (8-n)) & aux[n]);
    }
    arr[length-1] = arr[length-1] << n;
}


/**
 * Shift left N bits, N < length
 * @param arr
 * @param length
 * @param N
 */
void shiftLeftbyN(BYTE *arr, WORD length, WORD N){
    WORD n = N % 8;
    WORD M = N / 8;
    for(WORD i=0; i<length-M; ++i){
        arr[i] = arr[i+M];
    }
    for(WORD i=length-M; i<length; ++i){
        arr[i] = 0;
    }
    shiftLeftbyn(arr, length-M, n); // length-M: no need to shift the zeros
}

void fillZeros(BYTE *arr, WORD length)
{
    int i;
    for(i=0; i<length; i++)
    {
        arr[i]=0;
    }
}

void copyFromTo(BYTE *src, BYTE *dst, WORD length)
{
    for(WORD i=0; i<length; ++i){
        dst[i] = src[i];
    }
}



BOOL isZero(BYTE *arr, WORD length)
{
    int i;
    for(i=0; i<length; i++)
    {
        if(arr[i]!=0)
            return 0;
    }
    return 1;
}

BOOL isEqual(BYTE *arr1, BYTE *arr2, WORD length)
{
    WORD i;
    for(i=0; i<length; i++)
    {
        if(arr1[i]!=arr2[i])
            return 0;
    }
    return 1;
}

BOOL isGreater(BYTE *arr1, BYTE *arr2, WORD length)
{
    for(WORD i=0; i<length; ++i){ //Big endian
        if(arr1[i]>arr2[i])
            return 1;
        if(arr1[i]<arr2[i])
            return 0;
    }
}


void division(BYTE *quotient, BYTE *dividend, BYTE *divisor, WORD length){
    fillZeros(quotient, length);
    BYTE remainder[length]; copyFromTo(dividend, remainder, length);
    BYTE divisorAux[length]; copyFromTo(divisor, divisorAux, length);

    BYTE pls[1] = {0x00};

    while(!isZero(divisor, length)){
        if(isGreater(remainder, divisorAux, length)){
            shiftLeftbyn(quotient, length, 1); quotient[length-1] |= 0x01; // insert bit 1 in less sign. position to quotient
            subtract(remainder, remainder, divisorAux, length);
        }
        else{
            shiftLeftbyn(quotient, length, 1); // insert bit 0 in less sign. position to quotient
        }
        /*imprimirHexadecimal(pls, 1);
        imprimirHexadecimal(remainder, length);
        imprimirHexadecimal(divisorAux, length);
        imprimirHexadecimal(quotient, length);
        imprimirHexadecimal(pls, 1);*/
        shift_right(divisorAux, length);
    }
}

/**
 * Calculates result = base mod modulus
 * Allows superposition for buffers
 * @param result
 * @param base
 * @param modulus
 * @param modulusLength
 */
void module(BYTE *result, BYTE *base, BYTE *modulus, WORD length)
{
    //note: seguramente muy mejorable
//    copyFromTo(base, result, length);
//    while(isGreater(result, modulus, length)){
//        subtract(result, result, modulus, length);
//    }

    BYTE pls[2] = {0x00};

    BYTE quotient[length]; fillZeros(quotient, length);
    BYTE divisor[length]; copyFromTo(modulus, divisor, length);
    BYTE dividend[length]; copyFromTo(base, dividend, length);
    while(!isZero(divisor, length)){
        if(isGreater(dividend, divisor, length)){
            shiftLeftbyn(quotient, length, 1); quotient[length-1] |= 0x01; // insert bit 1 in less sign. position to quotient
            subtract(dividend, dividend, divisor, length);
        }
        else{
            shiftLeftbyn(quotient, length, 1); // insert bit 0 in less sign. position to quotient
        }
        imprimirHexadecimal(pls, 1);
        imprimirHexadecimal(dividend, length);
        imprimirHexadecimal(divisor, length);
        imprimirHexadecimal(quotient, length);
        imprimirHexadecimal(pls, 1);
        shift_right(divisor, length);
    }
    copyFromTo(dividend, result, length);
}

/**
 * Subtract arr1 - arr2 and store result in result. Allows superposition for buffers.
 * @param result
 * @param arr1
 * @param arr2
 * @param length
 */
void subtract(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length)
{

    SWORD carry = 0;
    BYTE borrow = 0;
    for(WORD i=length-1; i>0; --i){      // Big Endian
        carry = arr1[i] - arr2[i] - borrow;
        borrow = 0;
        if(carry<0) {
            carry += 256; // 0b100000000
            borrow = 1;
        }
        result[i] = carry & 0xFF;
    }
    // WORD is unsigned, so testing i>=0 in the for loop does not stop the loop
    carry = arr1[0] - arr2[0] - borrow;
    if(carry<0) {
        carry += 256; // 0b100000000
    }
    result[0] = carry & 0xFF;
}

void add(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length)
{
    // Suppose result's length as length+1

    WORD carry = 0;
    for(WORD i=length-1; i>0; --i){      // Big Endian
        carry = arr1[i] + arr2[i] + carry;
        result[i+1] = carry & 0xFF;
        carry = carry >> 8;
    }
    carry = arr1[0] + arr2[0] + carry; // WORD is unsigned, so testing i>=0 in the for loop does not stop the loop
    result[1] = carry & 0xFF;
    carry = carry >> 8;
    result[0] = carry & 0xFF;

}

void modular_add(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length)
{
    // Apply modulo to the operands
    module(arr1, arr1, modulus, length);
    module(arr2, arr2, modulus, length);

    WORD carry = 0;
    for(WORD i=length-1; i>0; --i){      // Big Endian
        carry = arr1[i] + arr2[i] + carry;
        result[i] = carry & 0xFF;
        carry = carry >> 8;
    }
    carry = arr1[0] + arr2[0] + carry; // WORD is unsigned, so testing i>=0 in the for loop does not stop the loop
    result[0] = carry & 0xFF;
    carry = carry >> 8;

    //  if carry is != 0 after the loop, it means that result can't store the addition initialy and the module will fail
    if(carry!=0){
        // avoid overflows
        BYTE auxArr[length+1];
        copyFromTo(result, auxArr+1, length); //copy result to the last positions of auxArr
        auxArr[0] = carry & 0xFF;
        BYTE auxMod[length+1];
        copyFromTo(modulus, auxMod+1, length);
        auxMod[0] = 0x00;

        module(auxArr, auxArr, auxMod, length+1);
        copyFromTo(auxArr+1, result, length);
    }
    else {
        module(result, result, modulus, length);
    }
}

void product(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length)
{

    // Suppose result's length as double the length argument

//      http://www.geeksforgeeks.org/divide-and-conquer-set-2-karatsuba-algorithm-for-fast-multiplication/
//    https://en.wikipedia.org/wiki/Karatsuba_algorithm#Pseudocode
//    procedure karatsuba(num1, num2)
//        if (num1 < 10) or (num2 < 10)
//        return num1*num2
//        /* calculates the size of the numbers */
//        m = max(size_base10(num1), size_base10(num2))
//        m2 = m/2
//        /* split the digit sequences about the middle */
//        high1, low1 = split_at(num1, m2)
//        high2, low2 = split_at(num2, m2)
//        /* 3 calls made to numbers approximately half the size */
//        z0 = karatsuba(low1,low2)
//        z1 = karatsuba((low1+high1),(low2+high2))
//        z2 = karatsuba(high1,high2)
//        return (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)


    //   Karatsuba with base case a WORD (2 bytes) storing result in a DWORD (4 bytes)

    // Base case
    if(length <= 2){
        BYTE aux[2*length];
        WORD num1 = 0;
        WORD num2 = 0;
        for(WORD i=0; i<length; ++i){
            num1 += ((WORD)arr1[i]) << (8*(length-i-1));
            num2 += ((WORD)arr2[i]) << (8*(length-i-1));
        }
        // in a 4 bytes DWORD the product won't overflow
        DWORD mult = num1*num2;
        for(WORD i = 0; i < length*2; i++){    // Store the solution
            result[i] = mult >> (8*(length*2-i-1));
        }
        return;
    }
    if(length == 3){ // result of 6 bytes, arr1 and arr2 of 3 bytes, we know there won't be overflow, but add expects 1 more byte in the result
        BYTE m[length*2]; fillZeros(m, length*2); copyFromTo(arr1, m+length, length);
        BYTE n[length*2]; fillZeros(n, length*2); copyFromTo(arr2, n+length, length);
        BYTE temp[length*2+1];
        while(!isZero(n, length*2)){
            if(n[length*2-1] & 0x01){
                add(temp, result, m, length*2);
                copyFromTo(temp+1, result, length*2);
            }
            shiftLeftbyn(m, length*2, 1);
            shift_right(n, length*2);
        }
        return;
    }

    // Divide and conquer

    WORD m2 = length/2;
    WORD h; // Max between m2 or length-m2
    BYTE offset = 0; // When copying the halves, the upper half may need an offset if m2<length-m2
    if(m2 == length-m2){
        h = m2;
    } else { // m2 = length/2, so length-m2 is the highest
        h = length-m2;
        offset = 1;
    }

    BYTE high1[h], low1[h];
    BYTE high2[h], low2[h];
    //TODO: can be improved for low and high to point directly without copyfromto

    copyFromTo(arr1, high1+offset, m2);
    copyFromTo(arr2, high2+offset, m2);
    if(offset){
        high1[0] = 0;
        high2[0] = 0;
    }
    copyFromTo(arr1+m2, low1, length-m2);
    copyFromTo(arr2+m2, low2, length-m2);

    // end division of arrays

    // arrays high1, low1, high2, low2 of length h

    // We will end up with 4h length arrays, and an auxiliar 4h+1 array
    // finally we have to truncate to 2*length, the result arrays length.
    // 4h ~>= 2length

    BYTE z0[4*h]; fillZeros(z0, 4*h); WORD z0Offset1 = 2*h; WORD z0Offset2 = 2*h-2;
    BYTE z2[4*h]; fillZeros(z2, 4*h); WORD z2Offset1 = 2*h; WORD z2Offset2 = 2*h-2;
    BYTE aux1[h+1], aux2[h+2]; // TODO: this can be combined and reused for memory optimization
    BYTE z1[4*h]; fillZeros(z1, 4*h); WORD z1Offset1 = 2*h-2;
    BYTE aux3[4*h+1]; fillZeros(aux3, 4*h+1);
    BYTE aux4[4*h]; fillZeros(aux4, 4*h);


    // z0 = karatsuba(low1,low2)
    product(z0+z0Offset1, low1, low2, h);
    // z2 = karatsuba(high1,high2)
    product(z2+z2Offset1, high1, high2, h);
    // z1 = karatsuba((low1+high1),(low2+high2))
    add(aux1, low1, high1, h);
    add(aux2, low2, high2, h);
    product(z1+z1Offset1, aux1, aux2, h+1);


    // return (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)

    // z1 = (z1-z2-z0)
    subtract(z1+z1Offset1, z1+z1Offset1, z2+z2Offset2, 2*h+2);
    subtract(z1+z1Offset1, z1+z1Offset1, z0+z0Offset2, 2*h+2);


    //   z2 << 2*h
    shiftLeftbyN(z2, 4*h, 8*2*h); // N bits
    // + z1 << h
    shiftLeftbyN(z1, 4*h, 8*h); // N bits
    // + z0

    add(aux3, z0, z1, 4*h);
    copyFromTo(aux3+1, aux4, 4*h);
    fillZeros(aux3, 4*h+1);
    add(aux3, aux4, z2, 4*h);

    // Truncate from 4h+1 to 2*length
    WORD diff = 4*h+1 - 2*length;
    copyFromTo(aux3+diff, result, 2*length);


}

/**
 * Stores in result the value of (arr1*arr2) mod modulus
 * @param arr1
 * @param arr2
 * @param modulus
 * @param length
 */
void modular_product(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length)
{
    //Module
    BYTE aux1[length], aux2[length]; fillZeros(aux1, length); fillZeros(aux2, length);
    module(aux1, arr1, modulus, length);
    module(aux2, arr2, modulus, length);
    //Product
    BYTE temp[2*length]; fillZeros(temp, 2*length);
    product(temp, aux1, aux2, length);
    //Module
    BYTE auxMod[2*length]; fillZeros(auxMod, 2*length); copyFromTo(modulus, auxMod+length, length);
    module(temp, temp, auxMod, 2*length);
    copyFromTo(temp+length, result, length);
}


void modular_exponentiation(BYTE *result, BYTE *base, BYTE *exponent, BYTE *modulus,
                            WORD modulusLength, WORD exponentLength)
{
    fillZeros(result, modulusLength);
    if(isZero(modulus, modulusLength))
    {
        return;     // if modulus = 1 then return 0
    }

    result[modulusLength-1]=1; // result := 1   // Multos is big endian

    module(base, base, modulus, modulusLength);  // base := base mod modulus

    while(!isZero(exponent, exponentLength))    // while exponent > 0
    {
        if(exponent[exponentLength-1] & 0x01)   // if (exponent mod 2 == 1):
        {
            modular_product(result, base, result, modulus, modulusLength);  // result := (result * base) mod modulus
        }

        shift_right(exponent, exponentLength);  // exponent := exponent >> 1

        modular_product(base, base, base, modulus, modulusLength);    // base := (base * base) mod modulus

    }

    // return result

}